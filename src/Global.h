/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
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
#include <ShaderManager.h>
#include <TransformTools.h>
#include "TooltipMessages.hpp"
#include "Skybox.h"
#include "CursorManager.h"
#include "ModelManager.h"
#include "LightSource.h"

class Global {

public:

	static std::array<Camera, 3> m_cameras;
	static int m_countNodeRender[3];
	static LightSource m_lights[8];
	static ofFloatColor m_ambientLightColor;

	// Sequence recording
	static std::string m_sequenceName;
	static float m_sequenceTotalDelta;
	static float m_sequenceInterval;
	static int m_sequenceCount;

	static Level m_level;
	static int m_selectedNode;
	static bool m_selectedFromViewport;
	static bool m_doColorPicking;
	static TransformTools m_transformTools;
	static ActionManager m_actions;
	static Skybox m_skybox;
	static void setup();
	static ofColor idToColor(int id);
	static int colorToId(ofColor color);
	static CursorManager m_cursorManager;
	static ModelManager m_modelManager;
	static TooltipMessages m_tooltipMessages;
	static ShaderManager m_shaders;

};

