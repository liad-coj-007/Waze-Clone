#include "KDTree.h"
#include <cmath>
KDNode::KDNode(const double& lat,const double& lon,const size_t& idx){
    this->lat = lat;
    this->lon = lon;
    this->idx = idx;
    this->left = nullptr;
    this->right = nullptr;
}


KDTree::KDTree(){
    root = nullptr;
}


void KDTree::AddPoint(const  double& lat,const  double& lon,
const size_t idx){
    KDNode* node = new KDNode(lat,lon,idx);
    AddNode(root,node,0);
}







void KDTree::AddNode(KDNode*& node,KDNode*& new_node,
    const bool depth){

    if(node == nullptr){
        node = new_node;
        return;
    }
    KDNode*& child = getChild(node,new_node,depth);
    AddNode(child,new_node,!depth);
   
}

KDNode*& KDTree::getChild(KDNode*& node,
    KDNode*& new_node,const bool depth){

    if(depth == 0){
       return node->lat < new_node->lat ? 
       node->right : node->left;
    }

    return node->lon < new_node->lon ? 
       node->right : node->left;

}


KDNode* KDTree::find_closest(KDNode*& target,
    KDNode*& node,KDNode* best,const bool depth){

    if(node == nullptr){
        return best;
    }

    long double dist = getDistance(target,node);
    long double min_dist = getDistance(target,best);
   
    if(dist <= min_dist ){
        best = node;
        min_dist = dist;
    }


    KDNode*& child = getChild(node,target,depth);
    best = find_closest(target,child,best,!depth);
    long double delta = 0;
    if(!depth){
        delta = std::abs(node->lat - target->lat);
    }else{
        delta = std::abs(node->lon - target->lon);
    }

    if(delta < min_dist){
        KDNode*& other_node = (child == node->left) ?
        node->right : node->left;
        best = find_closest(target,other_node,best,!depth);
    }
    return best;
}


long double KDTree::getDistance( KDNode*& p1, KDNode*& p2)const{
    long double dx = p1->lat - p2->lat;
    long double dy = p1->lon - p2->lon;
    return std::sqrt(dx*dx + dy*dy);
}

size_t KDTree::getClosestIdx(const double& lat,const double& lon){
    KDNode node(lat,lon,0);
    KDNode* tmp = &node;
    return find_closest(tmp,root,root,0)->idx;
}


void KDTree::DeleteNode(KDNode*& node){
    if(node == nullptr){
        return;
    }
    DeleteNode(node->left);
    DeleteNode(node->right);
    
    delete node;
    node = nullptr;  

}

KDTree::~KDTree(){
    DeleteNode(root);
}

