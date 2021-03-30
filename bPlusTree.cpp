#include <iostream>
#include <assert.h> 
#include <iomanip>
#include <math.h>
using namespace std;

#include "bPlusTree.hpp"
#include "constant.hpp"
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
  minPairsSize = (m+1)/2 - 1;
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
  treeNode *targetLeaf = searchLeaf(key);
  if(targetLeaf == NULL) {
    // tree is empty
    root = new treeNode(degree, key, value, true);
    leafList.push_back(root);
    return 0;
  }
  // search the target leaf to insert
  pair<int, treeNode*> isOverfull = targetLeaf->insertLeafNode(targetLeaf, make_pair(key, value), leafList);
  
  if(isOverfull.second == NULL) {
    cout << "[bPlusTree::insertion] overfull did not occurs" << endl;
    return 0;
  }

  treeNode* tIndexNode = NULL;
  /**
   * @brief Overfull occurs, dealing bottom up key and new node
   */
  while(isOverfull.second != NULL) {
    if(tracePath.size() == 0) {
      /**
      * @brief No index node parent
      * 1. New a new index parent
      * 2. Assign left, right child (new node)
      */
      tIndexNode = new treeNode(degree, isOverfull.first, true);
      vector<treeNode*>& childPointer = tIndexNode->getChildPointers(); 
      childPointer.push_back(root); // left split child
      childPointer.push_back(isOverfull.second); // right split child
      root = tIndexNode;
      break;
    }

    /**
     * @brief Exist index node parent -> insert key and assign child to index node
     * 1. Assign new node to the proper location (lowest bound < new node smallest key)
     * 2. Insert new index into parent
     *    -> might need continue splitting by checking overfull
     */
    tIndexNode = tracePath.back();
    vector<treeNode*>& childPointer = tIndexNode->getChildPointers(); 
    treeNode *newLeaf = isOverfull.second;
    int newLeafMinKey = prev(newLeaf->getKeyPairs().end())->first;
    
    int k = distance(tIndexNode->getKeyPairs().begin(), tIndexNode->getKeyPairs().lower_bound(newLeafMinKey));
    vector<treeNode*>::iterator childit = childPointer.begin(); 
    childPointer.insert(next(childit+k), newLeaf);
    tracePath.pop_back();
    
    cout << "[bPlusTree::insertion] traceback parent indexNode: " << tIndexNode << endl;
    int bottomUpkey = isOverfull.first;
    isOverfull = tIndexNode->insertIndexNode(tIndexNode, make_pair(bottomUpkey, defaultIndexValue));
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
  cout << "[bPlusTree::deletion] delete key: " << key <<", minPairsSize: " << minPairsSize << endl; 
  treeNode *targetNode = searchLeaf(key);
  if(targetNode == NULL) {
    return -1;
  }

  // search the target leaf to insert
  bool isDeficient = targetNode->deleteLeafNode(key);
  // check key
  /**
   * @brief 
   * 1. borrow() -> look into right, left sibling
   * 2. combine()
   */
  treeNode* parent = NULL;
  bool hasBorrow = false;
  bool hasCombine = false;
  
  // 1. LEAF borrow from siblings
  if(isDeficient) {
    cout << "[bPlusTree::deletion] target LEAF deficient" <<  endl; 
    if(tracePath.size() == 0) {
      // deficient node is root 
      return 0;
    }

    parent = tracePath.back();
    hasBorrow = borrow(parent, targetNode);
    if(hasBorrow) isDeficient = false;
  }

  // 2. combine with siblings
  while(isDeficient) {
    hasCombine = combine(parent, targetNode);
    if(hasCombine) {

    }

    break;
  }

  return 0;
}

bool bPlusTree::borrow(treeNode* parent, treeNode* deficient) {
  cout << "[bPlusTree::borrow] check if we can borrow" << endl; 
  treeNode *rightSib = NULL;
  treeNode *leftSib = NULL;

  bool rightBorrow = false;
  bool leftBorrow = false;

  auto childIt = parent->getChildPointers().begin(); 
  for(; childIt!=parent->getChildPointers().end(); childIt++) {
    if(*childIt == deficient) {
      if(childIt != prev(parent->getChildPointers().end())) {
        rightSib = *next(childIt);
      }
      if(childIt != parent->getChildPointers().begin()) {
        leftSib = *prev(childIt);
      }
      break;
    }
  } 
  
  cout << "[bPlusTree::borrow] right sibling size: " << rightSib->getKeyPairs().size() << endl; 
  if(rightSib != NULL && rightSib->getKeyPairs().size() - 1 >= minPairsSize) {
    cout << "[bPlusTree::borrow] eligible borrow from right sibling" << endl; 
    // eligible borrow from right sibling
    auto minValue = rightSib->getKeyPairs().begin();
    deficient->getKeyPairs().insert({minValue->first, minValue->second});
    rightSib->getKeyPairs().erase(minValue);
    rightBorrow = true;
  }
  else if(leftSib != NULL && leftSib->getKeyPairs().size() - 1 >= minPairsSize) {
    // eligible borrow from left sibling
    cout << "[bPlusTree::borrow] eligible borrow from left sibling" << endl; 
    auto maxValue = prev(leftSib->getKeyPairs().end());
    deficient->getKeyPairs().insert({maxValue->first, maxValue->second});
    leftSib->getKeyPairs().erase(maxValue);
    leftBorrow = true;
  }
  
  bool hasBorrow = (rightBorrow|leftBorrow);
  /**
   * @brief Borrow occurs
   * Adjust the key in parent by cheking the node with the newMin value
   * 1. Rightborrow -> the right sibling has newMin value
   * 2. Leftborrow -> the deficient node itself get a newMin value 
   */
  if(hasBorrow) {
    int keyIndex = 0;
    auto adjustKey = parent->getKeyPairs().begin();
    
    treeNode *targetNode = rightSib;
    auto targetNodeIt = next(childIt);
    if(leftBorrow) {
      targetNode = deficient;
      targetNodeIt = childIt;
    }

    keyIndex = distance(parent->getChildPointers().begin(), targetNodeIt) - 1;
    adjustKey = next(adjustKey, keyIndex);
    parent->getKeyPairs().erase(adjustKey->first);
    pair<int, double> newKey = {targetNode->getKeyPairs().begin()->first, targetNode->getKeyPairs().begin()->second};
    parent->getKeyPairs().insert(newKey);
  }

  return hasBorrow;
} 


bool bPlusTree::combine(treeNode* parent, treeNode* deficient) {
  cout << "[bPlusTree::combine] check if we can combine" << endl; 
  treeNode *rightSib = NULL;
  treeNode *leftSib = NULL;

  bool rightCombine = false;
  bool leftCombine = false;

  auto childIt = parent->getChildPointers().begin(); 
  for(; childIt!=parent->getChildPointers().end(); childIt++) {
    if(*childIt == deficient) {
      if(childIt != prev(parent->getChildPointers().end())) {
        rightSib = *next(childIt);
      }
      if(childIt != parent->getChildPointers().begin()) {
        leftSib = *prev(childIt);
      }
      break;
    }
  }

  if(rightSib != NULL) {
    // merge with right
    rightSib->getKeyPairs().insert(deficient->getKeyPairs().begin(), deficient->getKeyPairs().end());
    deficient->getKeyPairs().clear();
    rightCombine = true;
  }
  else if(leftSib != NULL) {
    // merge with left
    leftCombine = true;
  }

  /**
   * @brief Conbine occurs
   * Adjust the key in parent.
   */
  bool hasCombine = (rightCombine|leftCombine);
  if(hasCombine) {
    int keyIndex = 0;
    auto adjustKey = parent->getKeyPairs().begin();
    
    treeNode *targetNode = rightSib;
    auto targetNodeIt = next(childIt);
    if(leftCombine) {
      targetNode = deficient;
      targetNodeIt = childIt;
    }

    keyIndex = distance(parent->getChildPointers().begin(), targetNodeIt) - 1;
    adjustKey = next(adjustKey, keyIndex);

    // 
    parent->getKeyPairs().erase(adjustKey->first);
    
    // Remove LEAF in childPairsList
    parent->getChildPointers().erase(childIt);

    // Remove LEAF in leafList
    if(targetNode->getIsLeaf()) {
      for(auto itLeaf=leafList.begin(); itLeaf != leafList.end(); itLeaf++) {
        if(*itLeaf == deficient) {
          leafList.erase(itLeaf);
        }
      }
    }

    // Free space from pointer
    delete deficient;
    deficient = NULL; 
  }

  return hasCombine;
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
        /**
         * @brief Push the index node into path stack, keep on the top down searching
         */
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
  if(targetLeaf == NULL) {
    // the tree is empty
    cout << nullStr << endl;
    return -1;
  }
  
  pair<bool, double> result = targetLeaf->searchLeafNode(key);
  cout << "[projectResult][bPlusTree::search] key: " << key << ", result = ";
  if(result.first) {
    cout << result.second << endl;
  }
  else {
    cout << nullStr << endl;
  }
  return 0;
}

int bPlusTree::searchRange(int start, int finish) {
  cout << "[bPlusTree::searchRange] start: " << start << ", finish: " << finish << endl;
  treeNode *startLeaf = searchLeaf(start);
  if(startLeaf == NULL) {
    // the tree is empty
    cout << nullStr << endl;
    return -1;
  }

  vector<double> resultKeys;

  bool isInRange = false;
  bool stopSearching = false;
  
  for(auto itLeaf=leafList.begin(); itLeaf != leafList.end(); itLeaf++) {
    if(*itLeaf == startLeaf || isInRange) {
      // get starting leaf, or leaf is in range
      isInRange = true;
      for(auto itKey=(*itLeaf)->getKeyPairs().begin(); itKey != (*itLeaf)->getKeyPairs().end(); itKey++) {
        if(itKey->first < start || itKey->first > finish) {
          // Out of range
          stopSearching = true;
          break;
        }
        resultKeys.push_back(itKey->second);
      }
    }
    if(stopSearching) break;
  }

  if(resultKeys.empty()) {
    cout << nullStr << endl;
    return 0;
  }

  cout << "[projectResult][bPlusTree::searchRange] ";
  for(int i=0; i<resultKeys.size(); i++) {
    cout << resultKeys[i];
    if(i == resultKeys.size() - 1) {
      break;
    }
    cout << ",";
  }
  cout << endl;
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
  cout << "[bPlusTree::printTree] ";
  if(!root->getIsLeaf()) {
    cout << "INDEX: ";
  }
  else {
    cout << "LEAF: ";
  }
  root->printNodeKeyValue();
  cout << endl;
  // vector<treeNode*>& childPointer = root->getChildPointers(); 
  // cout << childPointer.size() << endl;
  // cout << endl;
  if(!root->getIsLeaf()) {
    for(auto it=root->getChildPointers().begin(); it != root->getChildPointers().end(); it++) {
      printTree(*it);
    }
  }
}

treeNode* bPlusTree::getRoot(){
  return root;
}