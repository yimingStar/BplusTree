# COP5536 Advance Data Structure - B+ Tree
---

## Author:
- **Name:** Yi-Ming Chang
- **UFID:** 83816537
- **email:** yimingchang@ufl.edu

---
## A. Introduction

### ***1. Run this program***
Firstly, we'll going to show the usage on executing the program.
After execute the makefile, we can run the program by the command below.

  ```
  ./bplustree [input_file name]
  ```
The result will be store into ***output_file.txt***.


### ***2. File structures***
This project builds a B+ tree by using C++. So, the plan of the project is majorly seperate into three part

- Maintain B+ Tree property
- Arrangement of the tree node's interior values
- Command execution

Accordingly, we seperate the project into 3 parts
  - ***bPlusTree.cpp*** - build to maintain the B+ tree structure.
  - ***treeNode.cpp*** - focusing on the interior of a tree node.
  - ***main.cpp*** - execute the input command, and output the result. 

Moreover, the project files only exist in the first directory, with ***header files showing the parameters and functions of each class***. The file list is showed as below:

  ```
  📦 BplusTree
   ┣ 📜 bPlusTree.cpp
   ┣ 📜 bPlusTree.hpp
   ┣ 📜 treeNode.cpp
   ┣ 📜 treeNode.hpp
   ┣ 📜 main.cpp
   ------
   ┣ 📜 constant.hpp // constant stored
   ┣ 📜 bplustree // exec file
   ┗  📜 makefile
  ```
  

---
## B. Functions ProtoTypes and Descriptions
This section show the functions input output parameters and simply describe how the process works to use these functions to build the B+ tree.

### ***bPlusTree*** 
1. Construct Tree and assigning property parameters.

  |   | Function Names | input | return | description |
  |---| ------------- | ------------- | ----------- | ------- | 
  |(a)| bPlusTree | int degree | None | tree constructure |
  |(b)| init | int degree | None | init tree parameters |

2. Search operation 

  |   | Function Names | input | return | description |
  |---|------------- | ------------- | ----------- | ------- | 
  |(a)| searchLeaf | int key | treeNode* | traverse to the leaf contains the key|
  |(b)| search | int key | int success | output the value of the key |
  |(c)| searchRange | int start, int finish | int success | output the values in the range |

3. Insert operation

  |   | Function Names | input | return | description |
  |---| ------------- | ------------- | ----------- | ------- | 
  |(a)| insertion | int key, double value |int success| insert data {key, value} |

  The progress of this function is using ***1-(a)*** to find the spot to insert the data. 
  After the node insert [***8-(b) insertLeafNode)*** or ***8-(a) insertIndexNode***](#insert_treeNode), there might cause a node ***overfull***, a new sibling nod will be created (See detailed in 8.) which will trigger a propagation insert up to the upper level node. . To simplify the porpogation. We shown the flow chart as below.

  ```mermaid
  graph LR
  A{overfull?} --> | NO | A1[done]
  A --> | YES | B[split]
  B --> C[mid key abd new nodes] --> |insert| C1[parent key] --> |organize| D[check parent] --> A
  ```
  
  As the flow char shown, the ***middle key*** will be ***insert*** into the parent. However, if the parent node is missing, parent node will have to be created. According to the overfull situation, the ***organize*** contains key and child pointers re-arrangement in the parent node. So, if the splitted node is INDEX node, we not only have to organize the key but also have to set some of the children pointer correctly. 


4. Delete operation

  |   | Function Names | input | return | description |
  |---| ------------- | ------------- | ----------- | ------- | 
  |(a)| deletion | int key, double value |int success| delete data {key, value} |
  |(b)| borrowFromIndex | treeNode* parent, treeNode* deficient |bool occurs| borrow key from sibling index node |
  |(c)| borrowFromLeaf | treeNode* parent, treeNode* deficient |bool occurs| borrow key from sibling leaf node |
  |(d)| combineWithIndex | treeNode* parent, treeNode* deficient |bool occurs| combine with sibling index node |
  |(e)| combineWithLeaf | treeNode* parent, treeNode* deficient |bool occurs| combine with sibling leaf node |
  |(f)| getInvalidParentKeyIdx | treeNode* parent, vector<treeNode*>::iterator changNodeIt |int distance| return the deficient index location of the key and child|
  
  
  Also using 1-(a) to find the spot to delete the data. 
  After the interior LEAF node delete ***9-(a) deleteLeafNode***, the LEAF node might be  ***deficient***, which will trigger the a ***propagation process*** fixing the deficient node. The flow chart shows a breaf of the fixing process.
  
  ```mermaid
  graph LR
  A{deficient?} --> | NO | A1[done]
  A --> | YES | B{borrow?}
  B --> | Yes | B1[done]
  B --> | NO  | C[combine] --> D[check parent] --> A
  ```
  
  Most importantly, combining with sibling might cause the parent becoming deficient, the process might propogates from leaf to root.
  
5. Test functions

  |   | Function Names | input | return | description |
  |---| ------------- | ------------- | ----------- | ------- | 
  |(a)| getTreeDegree | None | int degree | return tree degree |
  |(b)| printLeafList | None | None | print out leaf double link list |
  |(c)| printTree | None | None | print out the whole tree by DSF |
  |(d)| getRoot | None | treeNode* | return tree root |

### ***treeNode*** 
6. Construct treeNode

  |   | Function Names | input | return | description |
  |---| ------------- | ------------- | ----------- | ------- | 
  |(a)| treeNode | int degree, int key, bool insert | None | construct INDEX node |
  |(b)| treeNode | int degree, int key, double value, bool insert | None | construct LEAF node |


7. Search treeNode interiorly

  |   | Function Names | input | return | description |
  |---| ------------- | ------------- | ----------- | ------- | 
  |(a)| searchIndexNode | int key | treeNode* | return the index node |
  |(b)| searchLeafNode | int key | pair<bool, double> | return the data |


8. <a name="insert_treeNode">Insert Object into treeNode interiorly</a>
  
  |   | Function Names | input | return | description |
  |---| ------------- | ------------- | ----------- | ------- | 
  |(a)| insertIndexNode | treeNode* target, std::pair<int,double> | std::pair<int, treeNode*> | insert key into index node |
  |(b)| insertLeafNode | treeNode* target, std::pair<int,double>, std::list<treeNode*> &leafList | std::pair<int, treeNode*> | insert key into leaf node |
  |(c)| getMiddleKey | None | std::map<int, double> | return the middle key-value after insert |
  |(d)| getMiddleChild | None | std::vector<treeNode*>::iterator | return the middle child pointer after insert |
  |(e)| copyAndDeleteKeys | treeNode *newNode, std::map<int, double>::iterator start, std::map<int, double>::iterator end | int success | split occurs, copy keys to new node, delete keys from old|
  |(f)| copyAndDeleteChilds | int key | int success | split occurs, copy childs to new node, delete childs from old|
  
  When split occurs, a new sibling node will be create. Then we copy the proper keys and childs to the new node, and remove them from the old node. 
  ```mermaid
  graph LR
  A{overfull?} --> | NO | A1[done]
  A --> | YES | B[split]
  B --> C[create sibling] --> C1[copyAndDelete] --> D[ return push key and new node]
  ```


9. Delete Object from treeNode interiorly

  |   | Function Names | input | return | description |
  |---| ------------- | ------------- | ----------- | ------- | 
  |(a)| deleteLeafNode | int key | bool isDeficient | delete the key in data |

10. Get Classes private variables

  |   | Function Names | input | return | description |
  |---| ------------- | ------------- | ----------- | ------- | 
  |(a)| getIsLeaf | None | bool isLeaf | return tree node is LEAF or INDEX |
  |(b)| getKeyPairs | None | std::map<int,double>& | return tree node's key-values |
  |(b)| getChildPointers | None | std::vector<treeNode*>& | return tree node's child pointers |
  
  
11. Test function

  |   | Function Names | input | return | description |
  |---| -------------  | ------------- | ----------- | ------- | 
  |(a)| printNodeKeyValue | None | None | print the node key-values |
  
---

## C.Design Details
This secection I'm going to show the data structures I used in bPlusTree and treeNode classes and why I uses it.

### ***bPlusTree*** 
```
class bPlusTree {
  private: 
    int degree;
    int minPairsSize;
    treeNode *root;
    std::vector<treeNode*> tracePath;
    std::list<treeNode*> leafList;
}
```

