#include "treeNode.h"

#include <iostream>
#include <assert.h> 
#include <limits.h>
using namespace std;

/**
 * Build treeNode class
 * ====================
*/
treeNode::treeNode(int treeDegree, int key, bool insert) {
  // add new key-value pairs into leaf node
  isLeaf = false;
  degree = treeDegree;
  if(insert) keyPairs.insert({key, 0}); // set value = 0 for INDEX node. 
}

/**
 * @brief Construct a new Leaf Node
 * 
 * @param key 
 * @param value 
 */
treeNode::treeNode(int treeDegree, int key, double value, bool insert) {
  // add new key-value pairs into leaf node
  isLeaf = true;
  degree = treeDegree;
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
    return {false, 0};
  }
  cout << "[treeNode::insert] target insertion INSERT node is OVERFULL";
  // push middle key to parent
  return {true, 0};
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
   * @brief Create new leaf and insert into leafList, this new node will be the RightSide of middle key
   */
  list<treeNode*>::iterator leafInsertPoint;
  for(auto it=leafList.begin(); it!=leafList.end(); it++)  {
    if(targetNode == *it) {
      leafInsertPoint = it;
      cout << "[treeNode::insertLeafNode] get LEAF node in LeafList" << endl;
    }
  }
  treeNode *newLeaf = new treeNode(targetNode->degree, 0, 0, false);
  leafList.insert(next(leafInsertPoint), newLeaf);
  
  map<int, double>::iterator midKey = targetNode->splitByMiddleKey();
  cout << "[treeNode::insertLeafNode] SPLIT LEAF node by key: " << midKey->first << endl;
  copyAndDeleteKeys(newLeaf, midKey, keyPairs.end());
  return {midKey->first, newLeaf};
}

/**
 * @brief get keyPairs middle iterator
 * 
 * @return map<int, double>::iterator 
 */
map<int, double>::iterator treeNode::splitByMiddleKey() {
  // create new node for the begin to middle keys
  int mid;
  map<int, double>::iterator midKey = keyPairs.begin();
  for (mid=0; mid < keyPairs.size()/2; mid++) {
    midKey++;
  }
  // push target key
  return midKey;
}

/**
 * @brief 
 * 
 * @param newNode 
 * @param start 
 * @param end 
 * @return int - {0} = success, {-1} = failed 
 */
int treeNode::copyAndDeleteKeys(
  treeNode *newNode, map<int, double>::iterator start, map<int, double>::iterator end) {
  cout << "[treeNode::copyAndDeleteKeys] start copy at key: " << start->first << endl;
  try {
    for(auto it=start; it != end; it++) {
      newNode->keyPairs.insert({it->first, it->second});
    }
    keyPairs.erase(start, end);
  }
  catch(exception& e) {
    cerr << "exception caught: " << e.what() << '\n';
  }
  return 0;
}

bool treeNode::getIsLeaf() {
  return isLeaf;
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