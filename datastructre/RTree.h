
#pragma once
#include <vector>
#include "Box.h"
using namespace std;




struct RNode{
    bool is_leaf;
    bool is_dummy;
    size_t idx;
    Box box;
    std::vector<RNode> childrens;
    RNode(const Box& box,const size_t idx);
    virtual ~RNode() = default;
};

class RTree{
public:
    /**
     * @brief build r - tree
    */
    RTree();

    /**
     * @brief add a box to the r-tree
    */
    void AddBox(const Box& box ,const size_t idx);

    /**
     * @brief return the idx of closest
     * box
    */
    size_t getCloseBox(const double& lat,const double& lon);

private:

   
    void AddNode(RNode& node,RNode& new_node);

    /**
     * @brief return the child that can contain
     * new_node that the area will remain small
    */
    RNode& ChoseChild(RNode& node, RNode& new_node);

    /**
     * @brief return the closest node on the tree
    */
    RNode& getClosestNode( RNode& node,const double& lat,const double lon);

    /**
     * @brief return the diff area
    */
    double getDiffArea(const Box& b1,const Box& b2)const;

    RNode root;

};