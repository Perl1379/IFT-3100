/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Level class definition
 *
 *****************************************************/
#pragma once

#include "nodes/BaseNode.h"

class Level {

private:
  BaseNode tree;

public:
  Level();
  void reset();
  bool loadFromFile(const char* filename);
  bool saveToFile(const char* filename);
  void draw();

};

