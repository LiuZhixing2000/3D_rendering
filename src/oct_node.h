#pragma once
#include "vector.h"
#include <vector>

class oct_node_{
public:
    oct_node_() {}
    ~oct_node_();

    int set_max_xyz(const vector_c& vct);
    int set_min_xyz(const vector_c& vct);

    int set_leaf();
    int set_internal();

    int set_childs(const oct_node_* childs_);
    int set_divide_x(const double& x);
    int set_divide_y(const double& y);
    int set_divide_z(const double& z);
    int set_depth(const int& d);
    int set_vertices(const std::vector<int>& vertices);

    vector_c get_max_xyz() const;
    vector_c get_min_xyz() const;

    bool is_leaf() const;
    oct_node_* get_childs() const;
    double get_divide_x() const;
    double get_divide_y() const;
    double get_divide_z() const;
    int get_depth() const;
    std::vector<int> get_vertices() const;

    int divide(
        const double& divide_x,
        const double& divide_y,
        const double& divide_z
    );
protected:
    // bounding box
    vector_c max_xyz_;
    vector_c min_xyz_;

    bool is_leaf_node_{ true };

    // for internal node
    oct_node_* childs_{ nullptr };
    double divide_x_, divide_y_, divide_z;
    int depth_in_tree_{ -1 };

    // for leaf_node_
    std::vector<int> vertices_ids_;
};