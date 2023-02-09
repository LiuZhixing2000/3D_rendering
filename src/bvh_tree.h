#pragma once
#include "bvh_node.h"

/**
 * @brief 3d bvh tree, to accelerate intersection detecting
 * @author Liu Zhixing, liuzhixing0525@163.com
 * @date 2022-10-05
 * 
 */
class bvh_tree_{
public:
    bvh_tree_() {}
    ~bvh_tree_();

    int set_object(const std::vector<float>& vertices, const std::vector<int>& facets);
    int set_max_depth(const int& max_depth);
    int set_max_items_num(const int& max_items_num);

    bvh_node_* get_root() const;
    int get_depth() const;
    int get_max_depth() const;
    int get_max_items_num() const;

    /**
     * @brief calculate every facet(triangle)'s center of gravity, saved in member topo_facets_centers_
     * 
     * @return int 1: success, 0 error
     */
    int build_facets_centers();

    /**
     * @brief build tree's root(when tree is empty)
     * @note set_object() should be called before to be sure there is an object
     * @note build_root() should not be called to be sure this root is not initialized
     * 
     * @return int 1: success, 0: error
     */
    int build_root();

    /**
     * @brief grow a tree basing on root
     * @note set_object() and build_root() should be call before to be sure there is an object and a root
     * 
     * @return int 1: success, 0: error
     */
    int grow_tree();

    /**
     * @brief divide a node iteratively until nothing to do
     * @note dividing rule: 1. two children has the same number of facets,
     *                      2. x, y and z axis in turn
     * 
     * @param root starting of dividing
     * @return int 1: success, 0 error
     */
    int divide_continuely(bvh_node_* root, const int& divide_axis);

    /**
     * @brief intersection detection between a ray and this tree
     * 
     * @param ray_starting starting point of the ray
     * @param ray_direction direction of the ray
     * @return std::vector<int> possibly intersecting facets
     */
    std::vector<int> intersection_detection_with_a_ray(
        const vector_c& ray_starting, const vector_c& ray_direction
    ) const;

    std::vector<int> intersection_detection_with_a_ray_continuely(
        bvh_node_* node,
        const vector_c& ray_starting, const vector_c& ray_direction
    ) const;

private:
    // bvh tree's root
    bvh_node_* root_{ nullptr };
    // bvh tree's depth
    int depth_{ 0 };

    // object in bvh tree
    std::vector<float> geom_vertices_;
    std::vector<int> topo_facets_;
    std::vector<float> topo_facets_centers_;
    vector_c min_xyz_;
    vector_c max_xyz_;

    // conditions when bvh tree stops growing
    int max_depth_{ 15 };
    int max_items_num_each_node_{ 1 };
};