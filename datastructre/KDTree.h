#pragma once
#include <cstddef>
struct KDNode {
    size_t idx;
    long double lat,lon;
    KDNode* left;
    KDNode* right;

    KDNode(const double& lat,const double& lon,const size_t& idx);
};

class KDTree{

public:
    /**
     * @brief build kd-tree
    */
    KDTree();

    /**
     * @brief add a new point to the tree
    */
    void AddPoint(const  double& lat,const  double& lon,
    const size_t idx);

    /**
     * @brief return the idx of the
     * closest point 
    */
    size_t getClosestIdx(const  double& lat,const  double& lon);

    ~KDTree();

private:

    /**
     * @brief delete the node from the tree
    */
    void DeleteNode(KDNode*& node);
    /**
     * @brief add the new_node to the tree
     * @param node - the subtree we add the 
     * new_node
     * @param new_node - the new node
     * @param depth - depth%2 of the tree for save mem
    */
    void AddNode(KDNode*& node,KDNode*& new_node,
    const bool depth);

    /**
     * @brief get the child base on depth
     * 
     * @details
     *  depth == 0 => equal by lon
     *  depth == 1 => equal by lat
    */
    KDNode*& getChild(KDNode*& node,
    KDNode*& new_node,const bool depth);



    KDNode* find_closest(KDNode*& target,
    KDNode*& node,KDNode* best,const bool depth);

    /**
     * @brief return the distance between 
     * two points
    */
    long double getDistance( KDNode*& p1, KDNode*& p2)const;


    KDNode* root;

};