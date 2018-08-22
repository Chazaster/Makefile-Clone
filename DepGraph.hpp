#ifndef _DepGraph_hpp
#define _DepGraph_hpp

#include <iostream>
#include <cstring>
#include "MakeTree.hpp"
#include "Token.hpp"
#include "Reader.hpp"
#include "systemInterface.hpp"
using namespace std;

class DepGraph {
public:
  DepGraph (string name);
  void print();
  void parseDepGraph();
  void runMake();
  bool isCyclic()         {return isCyclic(firstTarget);}
  bool update();;
  
private:
  Token readAndProcessDependencyPair (Reader *);
  bool isCyclic (GraphNode *);
  void runMake (GraphNode *p);
  
private:
  string _fileToMake, _targetToMake;
  GraphNode *firstTarget;
  MakeTree *_tree;
  bool local_runMake (long stamp, GraphNode *p);
  bool _update;
};

#endif
