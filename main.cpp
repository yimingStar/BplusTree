#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

#include "bPlusTree.hpp"
#include "constant.hpp"

void executeCmd(vector<string> &cmdSplitVec, bPlusTree *tree) {
  string cmd = cmdSplitVec[0];
  if(cmd == initCmd) {
    int degree = stoi(cmdSplitVec[1]);
    tree->init(degree);
  }
  else if (cmd == searchCmd) {
    if(cmdSplitVec.size() == searchParCount) {
      int key = stoi(cmdSplitVec[1]);
      tree->search(key);
    }
    else {
      int start = stoi(cmdSplitVec[1]);
      int end = stoi(cmdSplitVec[2]);
      tree->searchRange(start, end);
    }
  }
  else if(cmd == insertCmd) {
    int key = stoi(cmdSplitVec[1]);
    double value = stof(cmdSplitVec[2]);
    tree->insertion(key, value);
  }
  else if(cmd == deleteCmd) {
    int key = stoi(cmdSplitVec[1]);
    tree->deletion(key);
  }
  else if(cmd == printTreeCmd){
    tree->printTree(tree->getRoot());
  }
  else if(cmd == printLeadCmd){
    tree->printLeafList();
  }
}

vector<string> splitCmd(string line) {
  vector<string> cmdSplitVec;
  size_t prev = 0, pos;
  while((pos = line.find_first_of("(,) ", prev)) != string::npos){
      string sub = line.substr(prev, pos-prev);
      if(sub.find_first_not_of(' ') != std::string::npos) {
        cmdSplitVec.push_back(sub);
      }
      prev = pos+1;
  }
  return cmdSplitVec;
}

int main(int argc, char** argv) {
  // check input name is in agrv
  if(argc < 2) {
    cout << "[ERROR] missing input file" << endl;
    return -1;
  }

  string inputFileName = argv[1];
  string line;
  ifstream inputFile(inputFileName);

  /**
   * @brief redirect cout to output_file.txt!
   */
  // std::ofstream out("output_file.txt");
  // std::cout.rdbuf(out.rdbuf()); 

  static vector<string> splitResult;
  bPlusTree *tree = new bPlusTree(); 

  if(inputFile.is_open()) {
    while(getline(inputFile, line)) {
      splitResult = splitCmd(line);
      executeCmd(splitResult, tree);
    }
    inputFile.close();
  } 
  return 0;
}
