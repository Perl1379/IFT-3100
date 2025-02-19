/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Global class definition
 *
 *****************************************************/
#pragma once

#include <ofFbo.h>
#include <ofCamera.h>
#include "Level.h"
#include <array>
#include <Camera.h>

class Global {

public:

 static std::array<Camera,3> m_cameras;
 static Level m_level;

 static void setup();
 static ofColor idToColor(int id);
 static int colorToId(ofColor color);


};

