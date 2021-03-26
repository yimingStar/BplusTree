// <PROJECT>_<PATH>_<FILE>_H_.

#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

class bPlusTree {
  private: 
    int degree;
  public:
  
  /**
   * project description functions
   */
  bPlusTree(int degree);
  void insertion();
  void deletion();
  void search(int arr[]);


  /**
   * test functions
   */
  int getTreeDegree();
};

#endif  // BPLUSTREE_H_