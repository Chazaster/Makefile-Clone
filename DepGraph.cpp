// Name: Chase Watson
// Date: 12/8/16
// Assignment: Project 4
// File: DepGraph.cpp

#include "DepGraph.hpp"
using namespace std;

DepGraph::DepGraph(string name) {
  _fileToMake = name;
  _targetToMake = "";
  firstTarget = nullptr;
  _tree = new MakeTree();
  _update = false;
}

void DepGraph::print() {
  _tree -> print();
}

void DepGraph::parseDepGraph() {
  // Use Reader for pointer to read in new file and grab token
  // Check if token is at end or file, then return
  Reader *reader = new Reader (_fileToMake);
  while (true) {
    Token token = readAndProcessDependencyPair(reader);
    if (token.isEOF()) return;
  }
}

void DepGraph::runMake() {
  runMake (firstTarget);
  if (!update()) cout << "make: 'make.x' is up to date." << endl;
}

void DepGraph::runMake(GraphNode *p) {
  // Use long for timestamp since the timestamp has been continuous since the 1970's
  long stamp = 0;
  // Call timestamp from systemInterface to get the name of the file and the timestamp of that file
  // Then set the passed GraphNode pointer to that timestamp
  timestamp(p -> getName().c_str(), &stamp);
  p -> setTimestamp(stamp);
  // Recursively run runMake for however many nodes are in the tree
  for (int i = 0; i < p -> numDependentNodes(); i++)
    runMake(p -> dependentNodes() -> at(i));
  if (p -> numDependentNodes() != 0) {
    if (local_runMake(stamp, p)) {
      p -> runCommand();
      _update = true;
      timestamp(p -> getName().c_str(), &stamp);
      p -> setTimestamp(stamp);
    }
  }
}

bool DepGraph::local_runMake(long stamp, GraphNode *p) {
  // Have helper to check if the GraphNode pointer has dependent nodes or not
  // If GraphNode pointer has no dependent noes AND does not exist, produce error message
  // If anything else return true
  for (int i = 0; i < p -> numDependentNodes(); i++) {
    if (p -> dependentNodes() -> at(i) -> numDependentNodes() == 0
        && p -> dependentNodes() -> at(i) -> getTimestamp() == -1) {
      cout << "Error: " << p -> dependentNodes() -> at(i) -> getName() << "does not exist" << endl;
      exit(1);
    }
    if (stamp == -1 || stamp < p -> dependentNodes() -> at(i) -> getTimestamp()) return true;
  }
  return false;
}

bool DepGraph::isCyclic(GraphNode *p) {
  // Check to see if makefile is cyclic or not
  if (p -> onPath()) return true;
  p -> onPath(true);
  // Go through dependency graph and check if there is a cycle at each node
  for (int i = 0; i < p -> numDependentNodes(); i++)
    if (isCyclic (p -> dependentNodes() -> at(i))) return true;
  p -> onPath(false);
  return false;
}

Token DepGraph::readAndProcessDependencyPair(Reader *reader) {
  Token target = reader -> getToken();
  // Initial base cases
  if (target.isEOF()) return target;
  if (!target.isName()) {
    cout << "First token of dependency line should be a name - token" << endl;
    exit(1);
  }
  // Only use colon pointer for this base case
  Token colon = reader -> getToken();
  if (!colon .isColon()) {
    cout << "Dependency line is missing colon" << endl;
    exit(1);
  }
  // Now add target to dependency tree
  GraphNode *g_target = nullptr;
  // If the first target doesn't exist, insert it into the tree
  if (firstTarget == nullptr) {
    firstTarget = new GraphNode (target.getName());
    _tree -> insert(firstTarget);
  }
  if (_tree -> find(target.getName()) == nullptr) {
    g_target = new GraphNode(target.getName());
    _tree -> insert(g_target);
  }
  else g_target = _tree -> find(target.getName());
  Token token = reader -> getToken();
  // Now add nodes to tree
  while (token.isName()) {
    // Add the dependent nodes to the tree
    GraphNode *dependency;
    // If the name of the token found in the tree is null,
    // Make dependency pointer into a new GraphNode and insert it into tree
    // Or make pointer equal to found token in tree
    if (_tree -> find(token.getName()) == nullptr) {
      dependency = new GraphNode(token.getName());
      _tree -> insert(dependency);
    }
    else dependency = _tree -> find(token.getName());
    // Now add dependency nodes to listOfDependentNodes vector
    g_target -> addDependentNode(dependency);
    if (token.isName()) token = reader -> getToken();
  }  
  if (!token.isEOL()) {
    cout << "Dependency line has a no-name token" << endl;
    exit(1);
  }
  token = reader -> getToken();
  if (!token.isCommand()) {
    cout << "No command found after dependency line" << endl;
    exit(1);
  }
  g_target -> setCommand(token.getCommand());
  return token;
}

bool DepGraph::update() {
  return _update;
}

