#ifndef _MakeTree_hpp
#define _MakeTree_hpp

#include <iostream>
#include <string>
#include "TreeNode.hpp"
using namespace std;

class MakeTree {
public:
  MakeTree()                            {_root = nullptr;}
  void insert (GraphNode *nNode)        {_root = insert(_root, nNode);}
  GraphNode *find (string name);
  void print()                          {print(_root);}   // print the tree using in-order traversal
  TreeNode *getRoot()                   {return _root;}

private:
  TreeNode *insert (TreeNode *tNode, GraphNode *nNode);
  void print (TreeNode *root);
  GraphNode *localFind (TreeNode *root, string name);
  TreeNode *_root;
};

#endif
