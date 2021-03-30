#include <iostream>
#include <assert.h> 
#include <math.h>

#include "treeNode.hpp"
#include "constant.hpp"
using namespace std;

/**
 * Build treeNode class
 * ====================
*/

/**
 * @brief Construct a new INDEX node
 */
treeNode::treeNode(int treeDegree, int key, bool insert) {
  // add new key-value pairs into leaf node
  isLeaf = false;
  degree = treeDegree;
  maxPairsSize = treeDegree - 1;
  minPairsSize = (treeDegree+1)/2 - 1;
  if(insert) keyPairs.insert({key, defaultIndexValue}); // set value = 0 for INDEX node. 
}

/**
 * @brief Construct a new LEAF node
 */
treeNode::treeNode(int treeDegree, int key, double value, bool insert) {
  // add new key-value pairs into leaf node
  isLeaf = true;
  degree = treeDegree;
  maxPairsSize = treeDegree - 1;
  minPairsSize = (treeDegree+1)/2 - 1;
  if(insert) keyPairs.insert({key, value});
}

treeNode* treeNode::searchIndexNode(int key) { 
  assert(!isLeaf);
  cout << "[treeNode::searchIndexNode] Number of childs: " << childPointers.size() << endl;
  assert(childPointers.size() > 0); // failed if childPointers = 0
  
  map<int,double>::iterator targetkey = keyPairs.upper_bound(key);
  int k = distance(keyPairs.begin(), keyPairs.upper_bound(key));
  
  cout << "[treeNode::searchIndexNode] distance - k:" << k << endl;
  vector<treeNode*>::iterator childIdx = childPointers.begin(); 
  childIdx = childIdx + k;
  treeNode* targetChild = *childIdx;
  targetChild->printNodeKeyValue();
  cout << endl;
  return targetChild;
}

/**
 * @brief return key
 *        if bool = true --> hit, return value
 *        if bool = false --> miss, return Null
 * 
 * @param key 
 * @return pair<bool, double> 
 */
pair<bool, double> treeNode::searchLeafNode(int key) {
  assert(isLeaf);

  map<int,double>::iterator targetElement;
  targetElement = keyPairs.find(key);
  if(targetElement != keyPairs.end()) {
    return {true, targetElement->second};
  }

  return {false, 0};
}

/**
 * @brief 
 * 
 * @param targetNode 
 * @param insertPair 
 * @return pair<bool, int> 
 */
pair<int, treeNode*> treeNode::insertIndexNode(treeNode* targetNode, pair<int, double> insertPair) {
  targetNode->keyPairs.insert(insertPair);
  if(targetNode->keyPairs.size() < degree) {
    return {false, NULL};
  }
  cout << "[treeNode::insertIndexNode] target insertion INSERT node is OVERFULL" << endl;
  
  /**
   * @brief Create new indexNode
   *        this new node also will be return as the right child of middle key
   */
  treeNode *newIndexNode = new treeNode(targetNode->degree, 0, false);
  map<int, double>::iterator midKey = targetNode->getMiddleKey();
  vector<treeNode*>::iterator midChild = targetNode -> getMiddleChild();
  cout << "[treeNode::insertIndexNode] SPLIT INDEX node by key: " << midKey->first << endl;
  
  copyAndDeleteKeys(newIndexNode, midKey, targetNode->keyPairs.end());
  copyAndDeleteChilds(newIndexNode, midChild, targetNode->childPointers.end());
  return {midKey->first, newIndexNode};
}

/**
 * @brief 
 * 1. if not overfull, no split occurs -> insert data
 * 2. if overfull, split occurs 
 * 
 * @param targetNode 
 * @param insertPair 
 * @param leafList 
 * @return pair<int, treeNode*> 
 *         - int is the split middle key
 *         - treeNode will be the new SplitNode, right child of the key    
 */
pair<int, treeNode*> treeNode::insertLeafNode(
  treeNode* targetNode, pair<int, double> insertPair, list<treeNode*>& leafList) {
  
  targetNode->keyPairs.insert(insertPair);
  if(targetNode->keyPairs.size() < degree) {
    return {0, NULL};
  }

  cout << "[treeNode::insertLeafNode] after insertion, LEAF node is OVERFULL" << endl;
  /**
   * @brief Create new leaf and insert into leafList
   *        this new node also will be return as the right child of middle key
   */
  treeNode *newLeaf = new treeNode(targetNode->degree, 0, 0, false);
  
  // insert in 
  list<treeNode*>::iterator leafInsertPoint;
  for(auto it=leafList.begin(); it!=leafList.end(); it++)  {
    if(targetNode == *it) {
      leafInsertPoint = it;
      cout << "[treeNode::insertLeafNode] get LEAF node in LeafList" << endl;
    }
  }
  leafList.insert(next(leafInsertPoint), newLeaf);
  
  map<int, double>::iterator midKey = targetNode->getMiddleKey();
  cout << "[treeNode::insertLeafNode] SPLIT LEAF node by key: " << midKey->first << endl;
  copyAndDeleteKeys(newLeaf, midKey, keyPairs.end());
  return {midKey->first, newLeaf};
}

/**
 * @brief get keyPairs middle iterator
 * 
 * @return map<int, double>::iterator 
 */
map<int, double>::iterator treeNode::getMiddleKey() {
  // create new node for the begin to middle keys
  map<int, double>::iterator midKey = keyPairs.begin();
  for (int mid=0; mid < keyPairs.size()/2; mid++) {
    midKey++;
  }
  // push middle key
  return midKey;
}

vector<treeNode*>::iterator treeNode::getMiddleChild() {
  vector<treeNode*>::iterator midChild = childPointers.begin();
  for (int mid=0; mid < childPointers.size()/2; mid++) {
    midChild++;
  }
  // push middle key
  return midChild;
}

/**
 * @brief if Node is LEAF -> middle nodes value must also stay in the right new leaf
 *        No need to consider child list
 * @param newNode 
 * @param start 
 * @param end 
 * @return int - {0} = success, {-1} = failed 
 */
int treeNode::copyAndDeleteKeys(
  treeNode *newNode, map<int, double>::iterator start, map<int, double>::iterator end) {
  cout << "[treeNode::copyAndDeleteKeys] start at key: " << start->first << endl;
  
  map<int, double>::iterator targetCopy = start;
  if(!isLeaf) {
    targetCopy = next(start);
  }

  try {
    for(; targetCopy != end; targetCopy++) {
      newNode->keyPairs.insert({targetCopy->first, targetCopy->second});
    }
    keyPairs.erase(start, end);
  }
  catch(exception& e) {
    cerr << "exception caught: " << e.what() << '\n';
  }
  return 0;
}

int treeNode::copyAndDeleteChilds(
  treeNode *newNode, vector<treeNode*>::iterator start, vector<treeNode*>::iterator end) {
  cout << "[treeNode::copyAndDeleteChilds] start copy and delete childs" << endl;
  
  vector<treeNode*>& newChildPointer = newNode->getChildPointers(); 
  try {
    for(auto targetCopy = start; targetCopy != end; targetCopy++) {
      newChildPointer.push_back(*targetCopy);
    }
    childPointers.erase(start, end);
  }
  catch(exception& e) {
    cerr << "exception caught: " << e.what() << '\n';
  }
  return 0;
}

/**
 * @brief delete key, value in leaf node.
 *        if node become deficient; return the broken node
 *        
 * 
 * @param target 
 * @param key 
 * @param leafList 
 * @return treeNode* deficient node or NULL
 */
bool treeNode::deleteLeafNode(int key) {
  cout << "[treeNode::deleteLeafNode] delete in leaf, key: " << key << endl;
  for(auto it=keyPairs.begin(); it!=keyPairs.end(); it++) {
    if(it->first == key) {
      // find key -> erase
      keyPairs.erase(it);
      break;
    }
  }

  if(keyPairs.size() >= minPairsSize) {
    return false;
  }

  cout << "[treeNode::deleteLeafNode] after deletion, LEAF node is DEFICIENT" << endl;
  return true;
}

bool treeNode::getIsLeaf() {
  return isLeaf;
}

map<int, double>& treeNode::getKeyPairs() {
  return keyPairs;
}

vector<treeNode*>& treeNode::getChildPointers() {
  return childPointers;
}

/**
 * @brief [Test] print Nodes KeyPairs
 */
void treeNode::printNodeKeyValue() {
  for(auto it=keyPairs.begin(); it != keyPairs.end(); it++) {
    cout << "(" << it->first << "," << it->second << ")";
  }
}