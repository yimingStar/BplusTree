// <PROJECT>_<PATH>_<FILE>_H_.
#ifndef TEST_H_
#define TEST_H_

class test {
  public:
    void testSearch(bPlusTree &tree);
    void testRangeSearch(bPlusTree &tree);
    void testInsertion(bPlusTree &tree);
    void testDeletetion(bPlusTree &tree);
};

#endif  // TEST_H_