#include<list>
#include<vector>
#include<map>
#include<utility>

#include"treeNode.hpp"
// <PROJECT>_<PATH>_<FILE>_H_.
#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

class bPlusTree {
  private: 
    int degree;
    int minPairsSize;
    treeNode *root;
    std::vector<treeNode*> tracePath;
    std::list<treeNode*> leafList;
  public:
    bPlusTree();
    bPlusTree(int m);
    void init(int m);

    int search(int key);
    int searchRange(int start, int finish);
    treeNode* searchLeaf(int key);

    int insertion(int key, double value);
    
    int deletion(int key);
    bool borrowFromLeaf(treeNode* parent, treeNode *deficient);
    bool borrowFromIndex(treeNode* parent, treeNode *deficient);
    bool combineWithLeaf(treeNode* parent, treeNode *deficient);
    bool combineWithIndex(treeNode* parent, treeNode *deficient);
    int getInvalidParentKeyIdx(treeNode* parent, std::vector<treeNode*>::iterator changNodeIt);

    /**
     * test functions
     */
    int getTreeDegree();
    void printLeafList();
    void printTree(treeNode* root);
    treeNode* getRoot();
};

#endif  // BPLUSTREE_H_
