/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Global class definition
 *
 *****************************************************/
#pragma once

#include "Level.h"
#include <array>
#include <Camera.h>
#include <TransformTools.h>


class Global {

public:

	static std::array<Camera, 3> m_cameras;
	static Level m_level;
	static int m_selectedNode;
	static TransformTools m_transformTools;

	static void setup();
	static ofColor idToColor(int id);
	static int colorToId(ofColor color);


};

