#include <iostream>
#include <bplustree.h>
using namespace std;

/**
 * 1. The input line read from the file in same directory
 * 2. [Important] Output the result into output.txt
*/
int main() {
  bPlusTree tree(3);
  cout << tree.getTreeDegree() << endl;
  return 0;
}