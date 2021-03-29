#include <iostream>
#include "bPlusTree.hpp"
#include "test.hpp"

using namespace std;

void test::testInsertion(bPlusTree &tree) {
  tree.insertion(10,1.0);
  cout << endl;
  tree.insertion(30,3.0);
  cout << endl;
  tree.insertion(20,2.0);
  cout << endl;

  tree.insertion(40,4.0);
  cout << endl;

  tree.insertion(50,5.0);
  cout << endl;

  tree.insertion(60,6.0);
  cout << endl;
  
  tree.insertion(70,7.0);
  cout << endl;

  tree.insertion(31,3.1);
  cout << endl;
  
  tree.insertion(32,3.2);
  cout << endl;

  tree.insertion(33,3.3);
  cout << endl;
  tree.insertion(-10,-0.35837);
  cout << endl;
  tree.printTree(tree.getRoot());
  cout << endl;
  tree.printLeafList();
}

void test::testRangeSearch(bPlusTree &tree) {
  tree.searchRange(-100, 50);
}