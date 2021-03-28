#include <iostream>
#include "bplustree.h"
using namespace std;

/**
 * 1. The input line read from the file in same directory
 * 2. [Important] Output the result into output.txt
*/
int main() {
  bPlusTree tree(3);
  tree.insertion(21, 0.3534);
  tree.search(21);
  tree.search(22);
  return 0;
}