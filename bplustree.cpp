#include "bplustree.h"

#include <iostream>
#include <assert.h> 
using namespace std;

const string nullStr = "Null";

/**
 * Build treeNode class
 * ====================
*/
treeNode::treeNode(bool isLeaf, int treeDegree) {
  isLeaf = isLeaf;
  degree = treeDegree;
  maxPairSize = treeDegree - 1;
}

treeNode::treeNode(int treeDegree, int key) {
  // add new key-value pairs into leaf node
  isLeaf = false;
  degree = treeDegree;
  maxPairSize = treeDegree - 1;
  keyPairs.insert({key, 0}); // set value = 0 for INDEX node. 
}

/**
 * @brief Construct a new Leaf Node
 * 
 * @param key 
 * @param value 
 */
treeNode::treeNode(int treeDegree, int key, double value) {
  // add new key-value pairs into leaf node
  isLeaf = true;
  degree = treeDegree;
  maxPairSize = treeDegree - 1;
  keyPairs.insert({key, value});
}

treeNode* treeNode::searchIndexNode(int key) { 
  assert(!isLeaf);
  treeNode* targetChild;

  map<int,double>::iterator targetkey = keyPairs.upper_bound(key);
  int k = distance(keyPairs.begin(), keyPairs.upper_bound(key));
  
  cout << "[treeNode::searchIndexNode] distance - k:"  << endl;
  vector<treeNode*>::iterator childIdx = childPointers.begin(); 
  childIdx = childIdx + k;
  return *childIdx;
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
pair<bool, int> treeNode::insertIndexNode(treeNode* targetNode, pair<int, double> insertPair) {
  // check key size
  if(targetNode->keyPairs.size() == maxPairSize) {
    // OVERFULL
    cout << "[treeNode::insert] target insertion INSERT node is OVERFULL";

    // push middle key to parent
    return {true, 0};
  }

  targetNode->keyPairs.insert(insertPair);
  return {false, 0};
}

pair<bool, int> treeNode::insertLeafNode(
  treeNode* targetNode, pair<int, double> insertPair, list<treeNode*>& leafList) {
  // check keyPair size
  if(targetNode->keyPairs.size() == maxPairSize) {
    targetNode->keyPairs.insert(insertPair);
    // OVERFULL
    cout << "[treeNode::insertLeafNode] after insertion, LEAF node is OVERFULL" << endl;

    int midkey = -INT_MAX;
    map<int, double>::iterator midKey = targetNode->splitByMiddleKey();
    cout << "[treeNode::insertLeafNode] split leaf node by key: " << midKey->first << endl;

    /**
     * @brief Create new leaf and insert into leafList
     */
    list<treeNode*>::iterator leafInsertPoint;
    for(auto it=leafList.begin(); it!=leafList.end(); it++)  {
      if(targetNode == *it) {
        leafInsertPoint = it;
        cout << "[treeNode::insertLeafNode] get LEAF node in LeafList" << endl;
      }
    }
    treeNode *newLeaf = new treeNode(true, targetNode->degree);
    leafList.insert(next(leafInsertPoint), newLeaf);
    
    copyAndDeleteKeys(newLeaf, midKey, keyPairs.end());
    return {true, midkey};
  }

  targetNode->keyPairs.insert(insertPair);
  return {false, 0};
}

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


void treeNode::printNodeKeyValue() {
  for(auto it=keyPairs.begin(); it != keyPairs.end(); it++) {
    cout << "(" << it->first << "," << it->second << ")";
  }
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
      root = new treeNode(degree, key, value);
      leafList.push_back(root);
      return 0;
    }
    // search the leaf to insert
    targetLeaf->insertLeafNode(targetLeaf, make_pair(key, value), leafList);
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