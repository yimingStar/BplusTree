#include <iostream>
#include "bplustree.h"
using namespace std;

/**
 * 1. The input line read from the file in same directory
 * 2. [Important] Output the result into output.txt
*/
int main() {
  bPlusTree tree(3);
  tree.insertion(20, 2.0);
  cout << endl;
  tree.search(20);
  cout << endl;

  tree.search(22);
  cout << endl;
  tree.insertion(22, 2.2);
  cout << endl;
  tree.search(22);
  cout << endl;

  tree.insertion(21, 2.1);
  cout << endl;
  tree.search(21);
  cout << endl;
  
  tree.printLeafList();
  return 0;
}