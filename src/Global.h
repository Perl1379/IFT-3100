/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Global class definition
 *
 *****************************************************/
#pragma once

#include <ActionManager.h>

#include "Level.h"
#include <array>
#include <Camera.h>
#include <TransformTools.h>
#include "TooltipMessages.hpp"
#include "Skybox.h"

class Global {

public:

	static std::array<Camera, 3> m_cameras;
	static int m_countNodeRender[3];

	static Level m_level;
	static int m_selectedNode;
	static bool m_selectedFromViewport;
	static TransformTools m_transformTools;
	static ActionManager m_actions;
	static Skybox m_skybox;
	static void setup();
	static ofColor idToColor(int id);
	static int colorToId(ofColor color);

	static TooltipMessages m_tooltipMessages;

};

