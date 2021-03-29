#include <iostream>
#include "bPlusTree.hpp"
#include "test.hpp"
using namespace std;
 
/**
 * 1. The input line read from the file in same directory
 * 2. [Important] Output the result into output.txt
*/
int main() {
  bPlusTree tree1(3);
  test doTest;
  doTest.testInsertion(tree1);
  doTest.testRangeSearch(tree1);

  return 0;
}