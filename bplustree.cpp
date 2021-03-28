#include "bplustree.h"
#include <iostream>
using namespace std;

const string nullStr = "Null";

/**
 * Build treeNode class
 * ====================
*/
treeNode::treeNode(int treeDegree, int key) {
  // add new key-value pairs into leaf node
  isLeaf = false;

  degree = treeDegree;
  maxPairSize = treeDegree - 1;

  pair<int, double> newKeyValue = make_pair(key, 0); // set value = 0 for INDEX node.
  keyPairs.push_back(newKeyValue); 
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

  pair<int, double> newKeyValue = make_pair(key, value);
  keyPairs.push_back(newKeyValue); 
}

treeNode* treeNode::searchIndexNode(int key) { 
  if(isLeaf) {
    cout << "throw exception - leaf node calling search INDEX function"  << endl;
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


pair<bool, double> treeNode::searchLeafNode(int key) {
  if(!isLeaf) {
    cout << "throw exception - unleaf node calling search LEAF function"  << endl;
    return make_pair(false, 0);
  }

  for (auto &p: keyPairs) {
    if(key == p.first) {
      cout << "[treeNode::search] hit in LEAF, key: " << key << endl;
      return make_pair(true, p.second);
    }
  }

  return make_pair(false, 0);;
}

int treeNode::insertLeafNode(treeNode* targetNode, pair<int, double> insertPair) {
  // check keyPair size
  if(targetNode->keyPairs.size() == maxPairSize) {
    // over full
    cout << "[treeNode::insert] target insertion LEAF node is overFull";
    return 0;
  }

  int key = insertPair.first;
  vector<pair<int, double>>::iterator insertPoint = targetNode->keyPairs.begin(); 
  
  for (auto &p: targetNode->keyPairs) {
    if(p.first >= key) {
      // find the key
      break;
    }
    insertPoint++;
  }

  targetNode->keyPairs.insert(insertPoint, insertPair);
  return 0;
}

bool treeNode::getIsLeaf() {
  return isLeaf;
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
      return 0;
    }

    // search the leaf to insert
    targetLeaf->insertLeafNode(targetLeaf, make_pair(key, value));
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