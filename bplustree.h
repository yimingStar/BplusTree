#include<list>
#include<vector>
#include<map>
#include<stack>

// <PROJECT>_<PATH>_<FILE>_H_.
#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_


class treeNode {
  private:
    /**
     * Size of this map will be degree-1
     * Which will be the maximum key pairs in one node. 
    */
    bool isLeaf;  
    std::map<int,double> keyPairs; 
  public:
    treeNode(int key); // create index node
    treeNode(int key, double value); // create leaf node
    int getNodeNumOfPairs();
    int getIsLeaf();
};

class bPlusTree {
  private: 
    int degree;
    treeNode *root;
    std::stack<treeNode> tracepath;
    std::list<treeNode> leafs;
  public:
  /**
   * project description functions
   */
  bPlusTree(int m);
  int insertion(int key, double value);
  int deletion(int key);
  int search(int arr[]);

  /**
   * test functions
   */
  int getTreeDegree();
  void traversal(); 
};

#endif  // BPLUSTREE_H_
