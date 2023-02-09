#include "bvh_node.h"
#include <iostream>

bvh_node_::~bvh_node_(){
    if(left_child_){
        delete left_child_;
        left_child_ = nullptr;
    }   
    if(right_child_){
        delete right_child_;
        right_child_ = nullptr;
    }
}

bvh_node_::bvh_node_(const bvh_node_& node){
    max_xyz_ = node.max_xyz_;
    min_xyz_ = node.min_xyz_;
    is_leaf_node_ = node.is_leaf_node_;
    left_child_ = node.left_child_;
    right_child_ = node.right_child_;
    divide_axis_ = node.divide_axis_;
    depth_in_tree_ = node.depth_in_tree_;
    facet_ids_ = node.facet_ids_;
}

int bvh_node_::set_max_xyz(const vector_c& vct){
    max_xyz_ = vct;
    return 1;
}

int bvh_node_::set_min_xyz(const vector_c& vct){
    min_xyz_ = vct;
    return 1;
}

int bvh_node_::set_leaf_node(){
    is_leaf_node_ = true;
    return 1;
}

int bvh_node_::set_internal_node(){
    is_leaf_node_ = false;
    return 1;
}

int bvh_node_::set_left_child(bvh_node_* node){
    left_child_ = node;
    return 1;
}

int bvh_node_::set_right_child(bvh_node_* node){
    right_child_ = node;
    return 1;
}

int bvh_node_::set_divide_axis(const int& axis){
    if(axis == axis_::x_ || axis == axis_::y_ || axis == axis_::z_)
        divide_axis_ = axis;
    else
        divide_axis_ = axis_::na_;
    return 1;
}

int bvh_node_::set_depth_in_tree(const int& depth){
    if(depth >= 0)
        depth_in_tree_ = depth;
    return 1;
}

int bvh_node_::set_facets(const std::vector<int>& facets){
    facet_ids_ = facets;
    return 1;
}

int bvh_node_::divide(
    const int& axis,
    const vector_c& left_min_xyz, const vector_c& left_max_xyz,
    const vector_c& right_min_xyz, const vector_c& right_max_xyz,
    const std::vector<int>& left_facets, const std::vector<int>& right_facets
){
    if(!is_leaf_node_){
        std::cout << "error: Internal node dividing!" << std::endl;
        return 0;
    }

    bvh_node_* left_child = new bvh_node_;
    left_child->set_min_xyz(left_min_xyz);
    left_child->set_max_xyz(left_max_xyz);
    left_child->set_depth_in_tree(get_depth_in_tree() + 1);
    left_child->set_facets(left_facets);

    bvh_node_* right_child = new bvh_node_;
    right_child->set_min_xyz(right_min_xyz);
    right_child->set_max_xyz(right_max_xyz);
    right_child->set_depth_in_tree(get_depth_in_tree() + 1);
    right_child->set_facets(right_facets);

    set_internal_node();
    set_left_child(left_child);
    set_right_child(right_child);
    set_divide_axis(axis);

    std::vector<int>().swap(facet_ids_);
    
    return 1;
}

vector_c bvh_node_::get_max_xyz() const{
    return max_xyz_;
}

vector_c bvh_node_::get_min_xyz() const{
    return min_xyz_;
}

bool bvh_node_::is_leaf() const{
    return is_leaf_node_;
}

bvh_node_* bvh_node_::get_left_child() const{
    return left_child_;
}

bvh_node_* bvh_node_::get_right_child() const{
    return right_child_;
}

int bvh_node_::get_divide_axis() const{
    return divide_axis_;
}

int bvh_node_::get_depth_in_tree() const{
    return depth_in_tree_;
}

std::vector<int>& bvh_node_::get_facets(){
    return facet_ids_;
}

bool bvh_node_::intersection_detection_with_a_ray(const vector_c& ray_starting, const vector_c& ray_direction) const{
    vector_c node_min_xyz = get_min_xyz(), node_max_xyz = get_max_xyz();
    double t1, t2;

    t1 = (node_min_xyz.get_x() - ray_starting.get_x()) / ray_direction.get_x();
    t2 = (node_max_xyz.get_x() - ray_starting.get_x()) / ray_direction.get_x();
    double t_in_x = std::min(t1, t2);
    double t_out_x = std::max(t1, t2);

    t1 = (node_min_xyz.get_y() - ray_starting.get_y()) / ray_direction.get_y();
    t2 = (node_max_xyz.get_y() - ray_starting.get_y()) / ray_direction.get_y();    
    double t_in_y = std::min(t1, t2);
    double t_out_y = std::max(t1, t2);

    t1 = (node_min_xyz.get_z() - ray_starting.get_z()) / ray_direction.get_z();
    t2 = (node_max_xyz.get_z() - ray_starting.get_z()) / ray_direction.get_z();    
    double t_in_z = std::min(t1, t2);
    double t_out_z = std::max(t1, t2);    

    double t_in = std::max(t_in_x, t_in_y);
    t_in = std::max(t_in, t_in_z);
    double t_out = std::min(t_out_x, t_out_y);
    t_out = std::min(t_out, t_out_z);

    if(t_out >= 0. && t_out - t_in > 0.)
        return true;

    return false;
}