#include "bvh_tree.h"
#include <iostream>
#include <set>

bvh_tree_::~bvh_tree_(){
    if(root_){
        delete root_;
        root_ = nullptr;
    }
}

int bvh_tree_::set_object(const std::vector<float>& vertices, const std::vector<int>& facets){
    geom_vertices_.resize(vertices.size());
    min_xyz_.set_vector(vector_c(vertices[0], vertices[1], vertices[2]));
    max_xyz_.set_vector(vector_c(vertices[0], vertices[1], vertices[2]));
    for(int i = 0; i < vertices.size() / 3; i++){
        if(vertices[3*i] < min_xyz_.get_x())
            min_xyz_.set_x(vertices[3*i]);
        if(vertices[3*i] > max_xyz_.get_x())
            max_xyz_.set_x(vertices[3*i]);
        geom_vertices_[3*i] = vertices[3*i];    

        if(vertices[3*i + 1] < min_xyz_.get_y())
            min_xyz_.set_y(vertices[3*i + 1]);
        if(vertices[3*i + 1] > max_xyz_.get_y())
            max_xyz_.set_y(vertices[3*i + 1]);
        geom_vertices_[3*i + 1] = vertices[3*i + 1];

        if(vertices[3*i + 2] < min_xyz_.get_z())
            min_xyz_.set_z(vertices[3*i + 2]);
        if(vertices[3*i + 2] > max_xyz_.get_z())
            max_xyz_.set_z(vertices[3*i + 2]);
        geom_vertices_[3*i + 2] = vertices[3*i + 2];
    }

    topo_facets_.resize(facets.size());
    for(int i = 0; i < facets.size() / 3; i++){
        topo_facets_[3*i] = facets[3*i];
        topo_facets_[3*i + 1] = facets[3*i + 1];
        topo_facets_[3*i + 2] = facets[3*i + 2];
    }
    max_xyz_ += 0.001;
    min_xyz_ -= 0.001;

    build_facets_centers();

    return 1;
}

int bvh_tree_::set_max_depth(const int& max_depth){
    max_depth_ = max_depth;
    return 1;
}

int bvh_tree_::set_max_items_num(const int& max_items_num){
    max_items_num_each_node_ = max_items_num;
    return 1;
}

bvh_node_* bvh_tree_::get_root() const{
    return root_;
}

int bvh_tree_::get_depth() const{
    return depth_;
}

int bvh_tree_::get_max_depth() const{
    return max_depth_;
}

int bvh_tree_::get_max_items_num() const{
    return max_items_num_each_node_;
}

int bvh_tree_::build_facets_centers(){
    if(geom_vertices_.empty() || topo_facets_.empty()){
        std::cout << "No object!" << std::endl;
        return 0;
    }

    topo_facets_centers_.resize(topo_facets_.size());
    for(int i = 0; i < topo_facets_.size() / 3; i++){
        vector_c pa(geom_vertices_[3*topo_facets_[3*i]], geom_vertices_[3*topo_facets_[3*i] + 1], geom_vertices_[3*topo_facets_[3*i] + 2]);
        vector_c pb(geom_vertices_[3*topo_facets_[3*i + 1]], geom_vertices_[3*topo_facets_[3*i + 1] + 1], geom_vertices_[3*topo_facets_[3*i + 1] + 2]);
        vector_c pc(geom_vertices_[3*topo_facets_[3*i + 2]], geom_vertices_[3*topo_facets_[3*i + 2] + 1], geom_vertices_[3*topo_facets_[3*i + 2] + 2]);
        vector_c center = pa + pb + pc;
        center /= 3.0;
        topo_facets_centers_[3*i] = center.get_x();
        topo_facets_centers_[3*i + 1] = center.get_y();
        topo_facets_centers_[3*i + 2] = center.get_z();
    }

    return 1;
}

int bvh_tree_::build_root(){
    if(root_){
        std::cout << "Root has been existing." << std::endl;
        return 0;
    }

    if(geom_vertices_.empty() || topo_facets_.empty()){
        std::cout << "No object!" << std::endl;
        return 0;
    }

    root_ = new bvh_node_;
    root_->set_min_xyz(min_xyz_);
    root_->set_max_xyz(max_xyz_);
    root_->set_depth_in_tree(0);
    std::vector<int> root_facets;
    for(int i = 0; i < topo_facets_.size() / 3; i++)
        root_facets.push_back(i);
    root_->set_facets(root_facets);
    
    return 1;
}

int bvh_tree_::grow_tree(){
    if(root_ == nullptr){
        std::cout << "No root!" << std::endl;
        return 0;
    }
    if(max_depth_ <= 0){
        std::cout << "Invalid max depth!" << std::endl;
        return 0;
    }
    if(max_items_num_each_node_ <= 0){
        std::cout << "Invalid max items!" << std::endl;
        return 0;
    }

    divide_continuely(root_, 0);

    return 1;
}

int bvh_tree_::divide_continuely(bvh_node_* root, const int& divide_axis){
    if(root == nullptr){
        std::cout << "No dividing node!" << std::endl;
        return 0;
    }

    if(divide_axis < 0 || divide_axis > 2){
        std::cout << "Invalid divide axis!" << std::endl;
        return 0;
    }

    std::vector<int> root_facets = root->get_facets();
    int root_depth = root->get_depth_in_tree();
    if(root_facets.empty()){
        std::cout << "No object in dividing starting node!"<< std::endl;
        return 0;
    }
    if(root_facets.size() <= max_items_num_each_node_ || root_depth >= max_depth_){
        //std::cout << "Dividing end." << std::endl;
        depth_ = std::max(depth_, root->get_depth_in_tree());
        return 1;
    }

    vector_c left_min_xyz, right_min_xyz;
    vector_c left_max_xyz, right_max_xyz;
    std::vector<int> left_facets, right_facets;
    std::vector< std::pair<double, int> > root_facets_ordered_by_coordinate;
    if(divide_axis == 0){
        for(int i = 0; i < root_facets.size(); i++){
            int& facet_id = root_facets[i];
            root_facets_ordered_by_coordinate.push_back(
                std::pair<double, int>(topo_facets_centers_[3*facet_id], facet_id)
            );
        }
    }
    else if(divide_axis == 1){
        for(int i = 0; i < root_facets.size(); i++){
            int& facet_id = root_facets[i];
            root_facets_ordered_by_coordinate.push_back(
                std::pair<double, int>(topo_facets_centers_[3*facet_id + 1], facet_id)
            );
        }
    }
    else{
        for(int i = 0; i < root_facets.size(); i++){
            int& facet_id = root_facets[i];
            root_facets_ordered_by_coordinate.push_back(
                std::pair<double, int>(topo_facets_centers_[3*facet_id + 2], facet_id)
            );
        }
    }

    std::sort(root_facets_ordered_by_coordinate.begin(), root_facets_ordered_by_coordinate.end());

    // left
    for(int i = 0; i < root_facets_ordered_by_coordinate.size()/2; i++){
        int facet_id = root_facets_ordered_by_coordinate[i].second;
        left_facets.push_back(facet_id);
        if(facet_id == 3){
            int a = 0;
        }
        int pa_id = topo_facets_[3*facet_id], pb_id = topo_facets_[3*facet_id + 1], pc_id = topo_facets_[3*facet_id + 2];
        vector_c pa(geom_vertices_[3*pa_id], geom_vertices_[3*pa_id + 1], geom_vertices_[3*pa_id + 2]);
        vector_c pb(geom_vertices_[3*pb_id], geom_vertices_[3*pb_id + 1], geom_vertices_[3*pb_id + 2]);
        vector_c pc(geom_vertices_[3*pc_id], geom_vertices_[3*pc_id + 1], geom_vertices_[3*pc_id + 2]);

        if(left_facets.size() == 1){
            left_min_xyz.set_x(std::min(std::min(pa.get_x(), pb.get_x()), pc.get_x()));
            left_min_xyz.set_y(std::min(std::min(pa.get_y(), pb.get_y()), pc.get_y()));
            left_min_xyz.set_z(std::min(std::min(pa.get_z(), pb.get_z()), pc.get_z()));

            left_max_xyz.set_x(std::max(std::max(pa.get_x(), pb.get_x()), pc.get_x()));
            left_max_xyz.set_y(std::max(std::max(pa.get_y(), pb.get_y()), pc.get_y()));
            left_max_xyz.set_z(std::max(std::max(pa.get_z(), pb.get_z()), pc.get_z()));
        }
        else{
            left_min_xyz.set_x(std::min(left_min_xyz.get_x(), std::min(std::min(pa.get_x(), pb.get_x()), pc.get_x())));
            left_min_xyz.set_y(std::min(left_min_xyz.get_y(), std::min(std::min(pa.get_y(), pb.get_y()), pc.get_y())));
            left_min_xyz.set_z(std::min(left_min_xyz.get_z(), std::min(std::min(pa.get_z(), pb.get_z()), pc.get_z())));

            left_max_xyz.set_x(std::max(left_max_xyz.get_x(), std::max(std::max(pa.get_x(), pb.get_x()), pc.get_x())));
            left_max_xyz.set_y(std::max(left_max_xyz.get_y(), std::max(std::max(pa.get_y(), pb.get_y()), pc.get_y())));
            left_max_xyz.set_z(std::max(left_max_xyz.get_z(), std::max(std::max(pa.get_z(), pb.get_z()), pc.get_z())));
        }
    }

    // right
    for(int i = root_facets_ordered_by_coordinate.size()/2; i < root_facets_ordered_by_coordinate.size(); i++){
        int facet_id = root_facets_ordered_by_coordinate[i].second;
        right_facets.push_back(facet_id);
        if(facet_id == 3){
            int a = 0;
        }

        int pa_id = topo_facets_[3*facet_id], pb_id = topo_facets_[3*facet_id + 1], pc_id = topo_facets_[3*facet_id + 2];
        vector_c pa(geom_vertices_[3*pa_id], geom_vertices_[3*pa_id + 1], geom_vertices_[3*pa_id + 2]);
        vector_c pb(geom_vertices_[3*pb_id], geom_vertices_[3*pb_id + 1], geom_vertices_[3*pb_id + 2]);
        vector_c pc(geom_vertices_[3*pc_id], geom_vertices_[3*pc_id + 1], geom_vertices_[3*pc_id + 2]);

        if(right_facets.size() == 1){
            right_min_xyz.set_x(std::min(std::min(pa.get_x(), pb.get_x()), pc.get_x()));
            right_min_xyz.set_y(std::min(std::min(pa.get_y(), pb.get_y()), pc.get_y()));
            right_min_xyz.set_z(std::min(std::min(pa.get_z(), pb.get_z()), pc.get_z()));

            right_max_xyz.set_x(std::max(std::max(pa.get_x(), pb.get_x()), pc.get_x()));
            right_max_xyz.set_y(std::max(std::max(pa.get_y(), pb.get_y()), pc.get_y()));
            right_max_xyz.set_z(std::max(std::max(pa.get_z(), pb.get_z()), pc.get_z()));
        }
        else{
            right_min_xyz.set_x(std::min(right_min_xyz.get_x(), std::min(std::min(pa.get_x(), pb.get_x()), pc.get_x())));
            right_min_xyz.set_y(std::min(right_min_xyz.get_y(), std::min(std::min(pa.get_y(), pb.get_y()), pc.get_y())));
            right_min_xyz.set_z(std::min(right_min_xyz.get_z(), std::min(std::min(pa.get_z(), pb.get_z()), pc.get_z())));

            right_max_xyz.set_x(std::max(right_max_xyz.get_x(), std::max(std::max(pa.get_x(), pb.get_x()), pc.get_x())));
            right_max_xyz.set_y(std::max(right_max_xyz.get_y(), std::max(std::max(pa.get_y(), pb.get_y()), pc.get_y())));
            right_max_xyz.set_z(std::max(right_max_xyz.get_z(), std::max(std::max(pa.get_z(), pb.get_z()), pc.get_z())));
        }
    }

    left_max_xyz += 0.0001;
    left_min_xyz -= 0.0001;
    right_max_xyz += 0.0001;
    right_min_xyz -= 0.0001;
    root->divide(divide_axis, left_min_xyz, left_max_xyz, right_min_xyz, right_max_xyz, left_facets, right_facets);

    int left_axis;
    double left_diff_x = (left_max_xyz - left_min_xyz).get_x();
    double left_diff_y = (left_max_xyz - left_min_xyz).get_y();
    double left_diff_z = (left_max_xyz - left_min_xyz).get_z();
    if(left_diff_x >= left_diff_y && left_diff_x >= left_diff_z)
        left_axis = 0;
    else if(left_diff_y >= left_diff_x && left_diff_y >= left_diff_z)
        left_axis = 1;
    else 
        left_axis = 2;
    divide_continuely(root->get_left_child(), left_axis);

    int right_axis;
    double right_diff_x = (right_max_xyz - right_min_xyz).get_x();
    double right_diff_y = (right_max_xyz - right_min_xyz).get_y();
    double right_diff_z = (right_max_xyz - right_min_xyz).get_z();
    if(right_diff_x >= right_diff_y && right_diff_x >= right_diff_z)
        right_axis = 0;
    else if(right_diff_y >= right_diff_x && right_diff_y >= right_diff_z)
        right_axis = 1;
    else 
        right_axis = 2;
    divide_continuely(root->get_right_child(), right_axis);

    return 1;
}

std::vector<int> bvh_tree_::intersection_detection_with_a_ray(
    const vector_c& ray_starting, const vector_c& ray_direction
) const{
    return intersection_detection_with_a_ray_continuely(
        get_root(),
        ray_starting, ray_direction
    );
}

std::vector<int> bvh_tree_::intersection_detection_with_a_ray_continuely(
    bvh_node_* node,
    const vector_c& ray_starting, const vector_c& ray_direction
) const{
    std::vector<int> result;

    // if no intersection
    if(!node->intersection_detection_with_a_ray(ray_starting, ray_direction))
        return result;

    // if intersection exists and node is leaf node
    if(node->is_leaf()){
        result = node->get_facets();
        return result;
    }

    // if intersection exists while node is internal node, iteratively detecting node's child
    std::vector<int> left_result = intersection_detection_with_a_ray_continuely(
        node->get_left_child(), 
        ray_starting, ray_direction
    );
    std::vector<int> right_result = intersection_detection_with_a_ray_continuely(
        node->get_right_child(),
        ray_starting, ray_direction
    );
    for(int i : left_result)
        result.push_back(i);
    for(int i : right_result)
        result.push_back(i);
    return result;
}