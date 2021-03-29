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
    treeNode *root;
    std::vector<treeNode*> tracePath;
    std::list<treeNode*> leafList;
  public:
  /**
   * project description functions
   */
  bPlusTree(int m);
  int insertion(int key, double value);
  int deletion(int key);

  int search(int key);
  int searchRange(int start, int finish);
  treeNode* searchLeaf(int key);
  /**
   * test functions
   */
  int getTreeDegree();
  void printLeafList();
  void printTree(treeNode* root);
  treeNode* getRoot();
};

#endif  // BPLUSTREE_H_
