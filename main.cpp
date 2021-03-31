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
  doTest.testInsertion(tree1, 1);
  cout << endl;
  tree1.deletion(20);
  tree1.deletion(40);
  tree1.deletion(10);
  tree1.printTree(tree1.getRoot());
  return 0;
}

// test 1 delete
  // bPlusTree tree1(3);
  // test doTest;
  // doTest.testInsertion(tree1, 2);
  // cout << endl;
  // tree1.printTree(tree1.getRoot());
  // cout << endl;
  // tree1.deletion(30);
  // cout << endl;
  // tree1.printTree(tree1.getRoot());

// test 2 delete
  // bPlusTree tree1(3);
  // test doTest;
  // doTest.testInsertion(tree1, 2);
  // cout << endl;
  // tree1.printTree(tree1.getRoot());
  // cout << endl;
  // tree1.deletion(20);
  // cout << endl;
  // tree1.printTree(tree1.getRoot());

// test 3 delete
  // bPlusTree tree1(3);
  // test doTest;
  // doTest.testInsertion(tree1, 1);
  // cout << endl;
  // tree1.printTree(tree1.getRoot());
  // cout << endl;
  // tree1.deletion(20);
  // cout << endl;
  // tree1.printTree(tree1.getRoot());

// test 4 delete
  // bPlusTree tree1(3);
  // test doTest;
  // doTest.testInsertion(tree1, 1);
  // cout << endl;
  // tree1.printTree(tree1.getRoot());
  // cout << endl;
  // tree1.deletion(20);
  // cout << endl;
  // tree1.printTree(tree1.getRoot());
  // tree1.deletion(10);
  // return 0;

// test 4 delete
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
  // return 0;