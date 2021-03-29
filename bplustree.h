#include<list>
#include<vector>
#include<map>
#include<utility>

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
    int degree;
    int maxPairSize;  
    std::map<int,double> keyPairs;
    std::vector<treeNode*> childPointers;
  public:
    
    treeNode(int degree, int key, bool insert); // create index node
    treeNode(int degree, int key, double value, bool insert); // create leaf node

    treeNode* searchIndexNode(int key);
    std::pair<bool, double> searchLeafNode(int key);

    std::pair<int, treeNode*> insertIndexNode(
      treeNode* target, 
      std::pair<int,double>
    ); // insert new key-value into 'index' node

    std::pair<int, treeNode*> insertLeafNode(
      treeNode* target, 
      std::pair<int,double>,
      std::list<treeNode*> &leafList
    ); // insert new key-value into 'leaf' node

    std::map<int, double>::iterator splitByMiddleKey();
    int copyAndDeleteKeys(treeNode *newNode, std::map<int, double>::iterator start, std::map<int, double>::iterator end);
    
    // get variable functions
    bool getIsLeaf();
    std::vector<treeNode*>& getChildPointers();

    // debug functions
    int getNodeNumOfPairs();
    void printNodeKeyValue();
};

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

  int search(int);
  treeNode* searchLeaf(int);
  /**
   * test functions
   */
  int getTreeDegree();
  void traversal(); 
  void printLeafList();
};

#endif  // BPLUSTREE_H_
