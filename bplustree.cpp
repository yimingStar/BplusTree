#include "bplustree.h"

#include <iostream>
#include <assert.h> 
#include <limits.h>
using namespace std;

const string nullStr = "Null";
/**
 * Build bPlusTree class
 * =====================
*/
/**
 * @brief Construct a new b Plus Tree::b Plus Tree object
 * 
 * @param m 
 */
bPlusTree::bPlusTree(int m) {
  degree = m;
  root = NULL;
}

/**
 * @brief 
 * 
 * @return int = tree degree
 */
int bPlusTree::getTreeDegree() {
 return degree;
}

/**
 * @brief 
 * @return int - {0} = success, {-1} = failed
 */
int bPlusTree::insertion(int key, double value) {
  cout << "[bPlusTree::insertion] insert (key, value) = (" << key << "," << value  << ")" << endl;
  /**
   * No need to search the tree first (the insert key value has no duplication) 
  */

  try {
    treeNode *targetLeaf = searchLeaf(key);
    if(targetLeaf == NULL) {
      // tree is empty
      root = new treeNode(degree, key, value, true);
      leafList.push_back(root);
      return 0;
    }
    // search the leaf to insert
    pair<int, treeNode*> overfull = targetLeaf->insertLeafNode(targetLeaf, make_pair(key, value), leafList);
    
    if(overfull.second == NULL) {
      cout << "[bPlusTree::insertion] overfull did not occurs" << endl;
      return 0;
    }

    treeNode* tIndexNode = NULL;
    while(overfull.second != NULL) {
      if(tracePath.size() == 0) {
        // missing index node -> still split -> need new index node
        // level change -> new root
        tIndexNode = new treeNode(degree, overfull.first, true);
        vector<treeNode*>& childPointer = tIndexNode->getChildPointers(); 
        childPointer.push_back(root); // mid key left
        childPointer.push_back(overfull.second); // mid key right
        root = tIndexNode;
      }
      else {
        tIndexNode = tracePath.back();
        tracePath.pop_back();
      }

      cout << "[bPlusTree::insertion] traceback parent indexNode: " << tIndexNode << endl;
      int bottomUpkey = overfull.first;
      overfull = tIndexNode->insertIndexNode(tIndexNode, make_pair(bottomUpkey, value));
    }

    return 0;
  }
  catch(exception& e) {
    cerr << "exception caught: " << e.what() << '\n';
  }
  return 0;
}

/**
 * @brief 
 * 
 * @param key 
 * @return int 
 */
int bPlusTree::deletion(int key) {
  return 0;
}

/**
 * @brief Search target leaf node with integer, reuse in insert
 * 1. if node = LEAF --> just try to find the value
 * 2. if node = INDEX --> push node stack tracepath; 
 *    then goes to the correct children to keep on the traversal
 * @param int = key
 * @return treeNode = the target leaf node
 */
treeNode* bPlusTree::searchLeaf(int key) {
  cout << "[bPlusTree::searchLeaf] key: " << key << endl;
  tracePath.clear();
  treeNode *targetNode = root;
  
  try {  
    while(targetNode != NULL) {
      if(!targetNode->getIsLeaf()) {
        // indexNode
        // pick the correct child and keep the traversal
        tracePath.push_back(targetNode);
        targetNode = targetNode->searchIndexNode(key);
      }
      else {
        // leafNode
        return targetNode;
      }
    }
  }
  catch(exception& e) {
    cerr << "exception caught: " << e.what() << '\n';
  }
  return targetNode;
}

/**
 * @brief Traverse to the target leaf where fits the key range
 * 
 * @param key 
 * @return int - {0} = success, {-1} = failed 
 */
int bPlusTree::search(int key) {
  cout << "[bPlusTree::search] key: " << key << endl;
  treeNode *targetLeaf = searchLeaf(key);
  if(targetLeaf == NULL) return -1;
  
  pair<bool, double> result = targetLeaf->searchLeafNode(key);
  cout << "[project_result][bPlusTree::search] key: " << key << ", result = ";
  if(result.first) {
    cout << result.second << endl;
  }
  else {
    cout << nullStr << endl;
  }
  return 0;
}

/**
 * @brief [Test]
 * 
 */
void bPlusTree::printLeafList() {
  cout << "[bPlusTree::printLeafList]" << endl;
  treeNode *node = NULL;
  int idx = 0;
  for(auto it=leafList.begin(); it != leafList.end(); it++, idx++) {
    cout << "Leaf Index: (" << idx << ") - ";
    (*it)->printNodeKeyValue();
    cout << endl;
  }
}

/**
 * @brief [Test]
 * 
 */
void bPlusTree::printTree(treeNode* root) {
  root->printNodeKeyValue();
  cout << endl;
  if(!root->getIsLeaf()) {
    for(auto it=root->getChildPointers().begin(); it != root->getChildPointers().end(); it++) {
      printTree(*it);
      cout << endl;
    }
  }
}

treeNode* bPlusTree::getRoot(){
  return root;
}