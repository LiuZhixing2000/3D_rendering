#include "oct_node.h"

int oct_node_::divide(
    const double& divide_x,
    const double& divide_y,
    const double& divide_z
){
    if(!is_leaf())
        return 0;

    childs_ = new oct_node_[8];
    
}