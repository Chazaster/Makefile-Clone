#include <iostream>
#include <string>
#include <vector>
#include "systemInterface.hpp"
using namespace std;

class GraphNode {
public:
  GraphNode (string name);
  string getName()                            {return _name;}
  void setName (string name)                  {_name = name;}
  long getTimestamp()                         {return _timestamp;}
  void setTimestamp (long ts)                 {_timestamp = ts;}
  vector <GraphNode *> *dependentNodes()      {return _listOfDependentNodes;}
  void setCommand (string cmnd)               {_command = cmnd;}
  string getCommand()                         {return _command;}
  void runCommand();                          // Execute the command associated with this node
  void addDependentNode (GraphNode *child)    {_listOfDependentNodes -> push_back(child);}
  bool onPath()                               {return _onPath;}
  void onPath (bool v)                        {_onPath = v;}
  bool wasMade()                              {return _wasMade;}
  void wasMade (bool v)                       {_wasMade = v;}
  bool isATarget()                            {return _isATarget;}
  void isATarget (bool v)                     {_isATarget = v;}
  long numDependentNodes()                    {return _listOfDependentNodes -> size();}
  void print();

private:
  string _name, _command;
  long _timestamp;
  vector <GraphNode *> *_listOfDependentNodes;
  bool _onPath, _isATarget, _wasMade;
};
