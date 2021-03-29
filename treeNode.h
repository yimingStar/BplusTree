#include<list>
#include<vector>
#include<map>
#include<utility>

// <PROJECT>_<PATH>_<FILE>_H_.
#ifndef TREENODE_H_
#define TREENODE_H_

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

    std::map<int, double>::iterator getMiddleKey();
    std::vector<treeNode*>::iterator getMiddleChild();
    int copyAndDeleteKeys(
      treeNode *newNode,
      std::map<int, double>::iterator start,
      std::map<int, double>::iterator end
    );
    int copyAndDeleteChilds(
      treeNode *newNode,
      std::vector<treeNode*>::iterator start,
      std::vector<treeNode*>::iterator end
    );

    // get variable functions
    bool getIsLeaf();
    std::map<int,double>& getKeyPairs();
    std::vector<treeNode*>& getChildPointers();

    // debug functions
    int getNodeNumOfPairs();
    void printNodeKeyValue();
};

#endif