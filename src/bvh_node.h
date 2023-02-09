#pragma once
#include "vector.h"
#include <vector>

enum axis_ {na_ = -1, x_ = 0, y_, z_};

/**
 * @brief 3d bvh tree's node, to accelerate intersection detecting
 * @author Liu Zhixing, liuzhixing0525@163.com
 * @date 2022-10-05
 * 
 */
class bvh_node_{
public:
    bvh_node_() {}
    ~bvh_node_();
    bvh_node_(const bvh_node_& node);

    int set_max_xyz(const vector_c& vct);
    int set_min_xyz(const vector_c& vct);
    int set_leaf_node();
    int set_internal_node();
    int set_left_child(bvh_node_* node);
    int set_right_child(bvh_node_* node);
    int set_divide_axis(const int& axis);
    int set_depth_in_tree(const int& depth);
    int set_facets(const std::vector<int>& facets);

    vector_c get_max_xyz() const;
    vector_c get_min_xyz() const;
    bool is_leaf() const;
    bvh_node_* get_left_child() const;
    bvh_node_* get_right_child() const;
    int get_divide_axis() const;
    int get_depth_in_tree() const;
    std::vector<int>& get_facets();

    /**
     * @brief divide a leaf node and convert it into internal node
     * 
     * @param axis 
     * @param left_min_xyz 
     * @param left_max_xyz 
     * @param right_min_xyz 
     * @param right_max_xyz 
     * @param left_facets 
     * @param right_facets 
     * @return int 1: success, 0: fail
     */
    int divide(
        const int& axis,
        const vector_c& left_min_xyz, const vector_c& left_max_xyz,
        const vector_c& right_min_xyz, const vector_c& right_max_xyz,
        const std::vector<int>& left_facets, const std::vector<int>& right_facets
    );

    /**
     * @brief intersection detection between a ray and a node(axis aligned bounding box)
     * 
     * @param ray_starting starting point of the ray
     * @param ray_direction direction of the ray
     * @return true intersection exists
     * @return false no intersection
     */
    bool intersection_detection_with_a_ray(
        const vector_c& ray_starting, const vector_c& ray_direction
    ) const;

private:
    // bounding box
    vector_c max_xyz_;
    vector_c min_xyz_;

    bool is_leaf_node_{ true };

    // internal node
    bvh_node_* left_child_{ nullptr };
    bvh_node_* right_child_{ nullptr };
    int divide_axis_{ axis_::na_ };
    int depth_in_tree_{ -1 };

    // leaf node
    std::vector<int> facet_ids_;
};