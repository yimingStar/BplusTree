#include <iostream>
#include <fstream>
#include "bPlusTree.hpp"
#include "test.hpp"
using namespace std;
 
/**
 * 1. The input line read from the file in same directory
 * 2. [Important] Output the result into output.txt
*/
int main() {
  
  streambuf *psbuf, *backup; 
  ofstream result;
  result.open("output_file.txt");
  // backup = std::cout.rdbuf();   
  psbuf = result.rdbuf();
  // assign streambuf to // cout
  cout.rdbuf(psbuf);  

  bPlusTree tree(3);
  // insertion
  for(int i=1; i<=9; i++) {
    tree.insertion(i*10, i);
    // tree.printTree(tree.getRoot());
  }
  // cout<< endl;
  // tree.printTree(tree.getRoot());
  // tree.printLeafList();
  // cout<< endl;

  // search 
  tree.search(10);
  tree.search(100);
  // searchRange
  tree.searchRange(10, 50);
  tree.searchRange(0, 20);
  // delete right leaf borrow
  // tree.deletion(70);
  
  //tree.printTree(tree.getRoot());
  //tree.printLeafList();

  // delete left leaf borrow
  
  // delete right leaf combine
  
  // delete left leaf combine
  
  // delete right index borrow

  // delete left index borrow 
  
  // delete right index combine

  // delete left index combine 

  result.close();
  return 0;
}

// test m = 3


// test 6 delete
  // bPlusTree tree1(3);
  // test doTest;
  // doTest.testInsertion(tree1, 1);
  // // cout<< endl;
  // tree1.printTree(tree1.getRoot());
  // // cout<< endl;
  // tree1.deletion(20);
  // // cout<< endl;
  // tree1.printTree(tree1.getRoot());
  // tree1.deletion(40);
  // tree1.printTree(tree1.getRoot());
  // tree1.deletion(10);
  // tree1.printTree(tree1.getRoot());
  // return 0;

// test delete - right index borrow
  // bPlusTree tree1(3);
  // test doTest;
  // doTest.testInsertion(tree1, 3);
  // // cout<< endl;
  // tree1.printTree(tree1.getRoot());
  // tree1.deletion(20);
  // // cout<< endl;
  // tree1.printTree(tree1.getRoot());
  // return 0;

// test delete - right index combine
  // bPlusTree tree1(3);
  // test doTest;
  // doTest.testInsertion(tree1, 4);
  // // cout<< endl;
  // tree1.deletion(20);
  // tree1.deletion(30);
  // // cout<< endl;
  // tree1.printTree(tree1.getRoot());
  // return 0;