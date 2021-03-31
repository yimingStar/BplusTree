#include <iostream>
#include "bPlusTree.hpp"
#include "test.hpp"

using namespace std;

void test::testInsertion(bPlusTree &tree, int version) {
  if(version == 0) {
    tree.insertion(10,1.0);
    tree.insertion(30,3.0);
    tree.insertion(20,2.0);
    tree.insertion(40,4.0);
    tree.insertion(50,5.0);
    tree.insertion(60,6.0);
    
    tree.insertion(70,7.0);
    tree.insertion(31,3.1);
    
    tree.insertion(32,3.2);

    tree.insertion(33,3.3);
    tree.insertion(-10,-0.35837);
  }
  else if(version == 1) {
    tree.insertion(10,1.0);
    tree.insertion(30,3.0);
    tree.insertion(20,2.0);
    tree.insertion(40,4.0);
  }
  else if(version == 2) {
    tree.insertion(10,1.0);
    tree.insertion(30,3.0);
    tree.insertion(20,2.0);
  }
  else if(version == 3) {
    for(int i=1; i<=5; i++) {
      tree.insertion(i*10, i);
      tree.printTree(tree.getRoot());
    }
  }
  
}

void test::testRangeSearch(bPlusTree &tree) {
  tree.searchRange(-100, 50);
  tree.searchRange(0, 1);
  tree.searchRange(5, 100);
  tree.searchRange(20, 50);
}