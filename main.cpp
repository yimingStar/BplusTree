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
  doTest.testInsertion(tree1, 4);
  cout << endl;
  tree1.deletion(20);
  tree1.deletion(30);
  cout << endl;
  tree1.printTree(tree1.getRoot());
  return 0;
}


// test 6 delete
  // bPlusTree tree1(3);
  // test doTest;
  // doTest.testInsertion(tree1, 1);
  // cout << endl;
  // tree1.printTree(tree1.getRoot());
  // cout << endl;
  // tree1.deletion(20);
  // cout << endl;
  // tree1.printTree(tree1.getRoot());
  // tree1.deletion(40);
  // tree1.printTree(tree1.getRoot());
  // tree1.deletion(10);
  // tree1.printTree(tree1.getRoot());
  // return 0;

// test delete index borrow
  // bPlusTree tree1(3);
  // test doTest;
  // doTest.testInsertion(tree1, 3);
  // cout << endl;
  // tree1.printTree(tree1.getRoot());
  // tree1.deletion(20);
  // cout << endl;
  // tree1.printTree(tree1.getRoot());
  // return 0;

// test delete index combine
  // bPlusTree tree1(3);
  // test doTest;
  // doTest.testInsertion(tree1, 4);
  // cout << endl;
  // tree1.deletion(20);
  // tree1.deletion(30);
  // cout << endl;
  // tree1.printTree(tree1.getRoot());
  // return 0;