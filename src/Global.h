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
#include "Level.h"

class Global {

public:

const static int FBO_RESOLUTION = 1000;

// Framebuffer objects (camera to texture)
 static ofFbo m_fboCameraMain;
 static ofFbo m_fboCameraSecond;
 static ofFbo m_fboCameraThird;
 static Level level;

 static void setup();


};

