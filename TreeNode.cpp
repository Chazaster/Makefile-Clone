// Name: Chase Watson
// Date: 12/8/16
// Assignment: Project 4
// File: TreeNode.cpp

#include "TreeNode.hpp"
using namespace std;

TreeNode::TreeNode(GraphNode *nNode) {
  makeNode = nNode;
  leftSubtree = nullptr;
  rightSubtree = nullptr;
}

void TreeNode::print() {
  cout << makeNode -> getName() << endl;
}
