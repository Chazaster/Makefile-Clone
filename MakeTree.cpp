// Name: Chase Watson
// Date: 12/8/16
// Assignment: Project 4
// File: MakeTree.cpp

#include "MakeTree.hpp"
using namespace std;

TreeNode *MakeTree::insert(TreeNode *tNode, GraphNode *nNode) {
  if (tNode == nullptr) return new TreeNode (nNode);
  // Check names to of both tree and graphnode pointers
  // To determine where to recursively insert
  if (tNode -> graphNode() -> getName() > nNode -> getName())
    tNode -> left(insert(tNode -> left(), nNode));
  else
    tNode -> right(insert(tNode -> right(), nNode));
  return tNode;
}

GraphNode *MakeTree::find (string name) {
  return localFind (_root, name);
}

GraphNode *MakeTree::localFind (TreeNode *root, string name) {
  if (root == nullptr) return nullptr;
  if (root -> graphNode() -> getName() == name)
    return root -> graphNode();
  if (root -> graphNode() -> getName() > name)
    return localFind(root -> left(), name);
  return localFind (root -> right(), name);
}

void MakeTree::print(TreeNode *root) {
  // In order traversal
  if (root == nullptr) return;
  print (root -> left());
  root -> graphNode() -> print();
  print (root -> right());
}
