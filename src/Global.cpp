/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * Global class implementation
 *
 *****************************************************/
#include "Global.h"
#include <Level.h>
#include <LevelPersistence.h>

// Static allocation
std::array<Camera, 3> Global::m_cameras;
int Global::m_countNodeRender[3];
Skybox Global::m_skybox;
Level Global::m_level;
int Global::m_selectedNode = 0;
TransformTools Global::m_transformTools;
ActionManager Global::m_actions;
bool Global::m_selectedFromViewport = false;
TooltipMessages Global::m_tooltipMessages;
CursorManager Global::m_cursorManager;
ModelManager Global::m_modelManager;
float Global::m_sequenceInterval = 0.5;
int Global::m_sequenceCount = -1;
std::string Global::m_sequenceName = "";
float Global::m_sequenceTotalDelta = 0;
LightSource Global::m_lights[8];
ofFloatColor Global::m_ambientLightColor = ofFloatColor(0.0, 0.0, 0.0);
bool Global::m_doColorPicking = true;
ShaderManager Global::m_shaders;
int Global::id_next = 1;
MaterialPreset Global::m_materialPreset;


/**
 * Setup global singleton object
 */
void Global::setup() {

	// Load shaders
	if (!m_shaders.setup()) {
		ofLogError() << "Shader setup failed";
		return;
	}

	//Material presets
	m_materialPreset.init();

	//Load models (characters and assets)
	m_modelManager.init();

	//Setup camera positions
	m_cameras[0].setup(ofVec3f(0, 600, 2100), ofVec3f(0, 400, 0));
	m_cameras[1].setup(ofVec3f(0, 3000, 0), ofVec3f(0, 0, 0));
	m_cameras[2].setup(ofVec3f(2400, 300, 200), ofVec3f(0, 300, 200));

	// Init lights
	for (int i=0;i<8;i++) {
		m_lights[i].setup();
		m_lights[i].setLightType(POINT_LIGHT);
		m_lights[i].setPosition(ofVec3f(0, 1000 - (i * 200), 2000));

		if (i > 0) {
			m_lights[i].setEnabled(false);
		} else {
			m_lights[i].setEnabled(true);

		}
	}


	//Init scene
	LevelPersistence lp;
	ofFile file("levels/Default.xml");
	if (file.exists()) {
		lp.loadFromFile("levels/Default.xml");
	} else {
		m_level.reset();
	}


	//Setup cursors
	m_cursorManager.setup();

}


/**
 * Encode a node ID into a specific RGB color
 */
ofColor Global::idToColor(int id) {
	int red = (id / (256 * 256)) % 256;
	int green = (id / 256) % 256;
	int blue = id % 256;

	return ofColor(red, green, blue);
}


/**
* Decode color to retrieve node ID
*/
int Global::colorToId(ofColor color) {
	return (color.r * (256 * 256)) + (color.g * 256) + color.b;
}

