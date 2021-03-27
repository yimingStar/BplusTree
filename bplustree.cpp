#include "bplustree.h"
#include <iostream>
using namespace std;

/**
 * Build treeNode class
 * ====================
*/
treeNode::treeNode(int key, double value) {
  // add new key-value pairs into leaf node
  keyPairs.insert({key, value});
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
  /**
   * No need to search the tree first (the insert key value has no duplication)
  */
  try {
    treeNode *targetNode = root;
    if(targetNode == NULL) {
      targetNode = new treeNode(key, value);
      return 0;
    }

    while(targetNode != NULL) {
      
    }
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
 * @brief 
 * 
 * @param arr 
 * @return int - {0} = success, {-1} = failed
 */
int bPlusTree::search(int arr[]) {
  // insert into ouput.txt
  return 0;
}