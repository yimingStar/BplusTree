#include "bplustree.h"
#include <iostream>
using namespace std;

/**
 * Build treeNode class
 * ====================
*/
treeNode::treeNode(int key) {
  // add new key-value pairs into leaf node
  isLeaf = false;
  pair<int, double> newKeyValue = make_pair(key, NULL); // set value = NULL for index node.
  keyPairs.push_back(newKeyValue); 
}

/**
 * @brief Construct a new Leaf Node
 * 
 * @param key 
 * @param value 
 */
treeNode::treeNode(int key, double value) {
  // add new key-value pairs into leaf node
  isLeaf = true;
  pair<int, double> newKeyValue = make_pair(key, value);
  keyPairs.push_back(newKeyValue); 
}

treeNode* treeNode::searchIndexNode(int key) { 
  if(isLeaf) {
    cout << "throw exception - leaf node calling search index function"  << endl;
    return NULL;
  }
  treeNode* targetChild;
  vector<treeNode*>::iterator childIdx = childPointers.begin(); 
  for (auto &p: keyPairs) {
    if(p.first >= key) {
      // find the key
      break;
    }
    childIdx++;
  }
  return *childIdx;
}

double treeNode::searchLeafNode(int key) {
  if(!isLeaf) {
    cout << "throw exception - unleaf node calling search leaf function"  << endl;
    return NULL;
  }
  double value = NULL;
  for (auto &p: keyPairs) {
    if(key == p.first) {
      cout << "[treeNode::search] hit in leaf, key: " << key << endl;
      value = p.second; 
      break;
    }
  }
  return value;
}

int treeNode::insert(treeNode* insertNode, pair<int, double> insertPair) {
  // TODO
}

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
      root = new treeNode(key, value);
      return 0;
    }

    targetLeaf.
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
 * 1. if node = leaf --> just try to find the value
 * 2. if node = index --> push node stack tracepath; 
 *    then goes to the correct children to keep on the traversal
 * @param int = key
 * @return treeNode = the target leaf node
 */
treeNode* bPlusTree::searchLeaf(int key) {
  cout << "[bPlusTree::search] search key: " << key << endl;
  tracePath.clear();
  treeNode *targetNode = root;
  
  try {  
    while(targetNode != NULL) {
      cout << targetNode->getIsLeaf() << endl;
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
 * @return double 
 */
double bPlusTree::search(int key) {
  treeNode *targetLeaf = searchLeaf(key);
  if(targetLeaf == NULL) return NULL;

  return targetLeaf->searchLeafNode(key);
}