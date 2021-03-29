#include <iostream>
#include "bPlusTree.hpp"
using namespace std;
 
/**
 * 1. The input line read from the file in same directory
 * 2. [Important] Output the result into output.txt
*/
int main() {
  // bPlusTree T(3);
  // T.insertion(20,0.1);
  // T.insertion(21,0.1);
  // T.insertion(22,0.1);
  // cout << endl;
  // T.printTree(T.getRoot());
  // cout << endl;

  // T.insertion(18,0.1);
  // cout << endl;
  // T.printTree(T.getRoot());
  // cout << endl;
  // T.insertion(19,0.1);
  // cout << endl;
  // T.printTree(T.getRoot());
  // cout << endl;

  bPlusTree T(3);
  T.insertion(10,0.1);
  cout << endl;
  T.insertion(30,0.3);
  cout << endl;
  T.insertion(20,0.2);
  cout << endl;
  T.printTree(T.getRoot());
  cout << endl;

  T.insertion(40,0.2);
  cout << endl;
  T.printTree(T.getRoot());
  cout << endl;

  T.insertion(50,0.2);
  cout << endl;
  T.printTree(T.getRoot());
  cout << endl;

  T.insertion(60,0.2);
  cout << endl;
  T.printTree(T.getRoot());
  cout << endl;
  
  T.insertion(70,0.2);
  cout << endl;
  T.printTree(T.getRoot());
  cout << endl;

  T.insertion(31,0.2);
  cout << endl;
  T.printTree(T.getRoot());
  cout << endl;
  
  T.insertion(32,0.2);
  cout << endl;
  T.printTree(T.getRoot());
  cout << endl;

  T.insertion(33,0.2);
  cout << endl;
  T.printTree(T.getRoot());
  cout << endl;

  T.printLeafList();
  return 0;
}