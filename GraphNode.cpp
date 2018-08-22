// Name: Chase Watson
// Date: 12/8/16
// Assignment: Project 4
// File: GraphNode.cpp

#include "GraphNode.hpp"
using namespace std;

GraphNode::GraphNode(string name) {
  _name = name;
  _command = "";
  _timestamp = 0;
  _listOfDependentNodes = new vector <GraphNode *> ();
  _onPath = false;
  _isATarget = false;
  _wasMade = false;
}

void GraphNode::runCommand() {
  // Use executeCommand found in systemInterface.cpp
  // to execute command associated with this node
  executeCommand(_command.c_str());
}

void GraphNode::print() {
  cout << getName() << " Timestamp: " << getTimestamp() << " Dependent Nodes: " << endl;
  for (int i = 0; i < numDependentNodes(); i++)
    cout << _listOfDependentNodes -> at(i) -> getName() << " Timestamp: " << _listOfDependentNodes -> at(i) -> getTimestamp() << endl;
}
