#include "RTree.h"
#include "Box.h"
#include <cmath>

const size_t max_child = 16;


RNode::RNode(const Box& box,const size_t idx):box(box){
    is_leaf = true;
    this->idx = idx;
    is_dummy = false;
}

RTree::RTree():root(Box(0,0,0,0),0){
    root.is_dummy = true;
}

void RTree::AddNode(RNode& node,RNode& new_node){
    if(node.childrens.size() < max_child){
        node.childrens.push_back(new_node);
    }

    if(node.is_leaf){
       node.is_leaf = false;
    }else{
        RNode& bestchild = ChoseChild(node,new_node);
        AddNode(bestchild,new_node);
    }

    node.box.Union(new_node.box);
}


RNode& RTree::ChoseChild( RNode& node, RNode& new_node){
    RNode* best_child = &node.childrens[0];
    double min_diff_area = getDiffArea(best_child->box,
    new_node.box);
    for(auto& it: node.childrens){
        double diff = getDiffArea(it.box,new_node.box);
        if(diff < min_diff_area){
            min_diff_area = diff;
            best_child = &it;
        }else if(diff == min_diff_area){
            best_child = best_child->box.getArea() > it.box.getArea() 
            ? best_child : &it;
        }
    }
    return *best_child;
}

double RTree::getDiffArea(const Box& b1,const Box& b2)const{
    double area2 = b2.getArea();
    double area1 = b1.getArea();
    if(area2 <= area1){
        return 0;
    }
    Box temp = b1;
    temp.Union(b2);
    return temp.getArea() - area1;
}

void RTree::AddBox(const Box& box,const size_t idx){
    RNode node(box,idx);
    if(root.is_dummy){
        root = node;
        return;
    }
    AddNode(root,node);
}


 RNode& RTree::getClosestNode(RNode& node,const double& lat,
const double lon) {
    if(node.is_leaf){
        return node;
    }

    RNode* best_child = &node.childrens[0];
    double min_dist = best_child->box.getDistance(lat,lon);
    for(auto& it : node.childrens){
        double dist = it.box.getDistance(lat,lon);
        if(dist < min_dist){
            min_dist = dist;
            best_child = &it;
        }
    }
    
    return getClosestNode(*best_child,lat,lon);
}

size_t RTree::getCloseBox(const double &lat,const double& lon){
    RNode& node = getClosestNode(root,lat,lon);
    return node.idx;
}






