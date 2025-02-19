/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Global class definition
 *
 *****************************************************/
#include "Global.h"
#include <Level.h>
#include <ofAppRunner.h>

 // Static allocation
std::array<Camera, 3> Global::m_cameras;

Level Global::m_level;


/**
 * Setup global singleton object
 */
void Global::setup() {

	m_cameras[0].setup(ofVec3f(0, 0, 100), ofVec3f(0, 0, 0));
	m_cameras[1].setup(ofVec3f(0, 100, 0), ofVec3f(0, 0, 0));
	m_cameras[2].setup(ofVec3f(100, 0, 0), ofVec3f(0, 0, 0));

	m_level.reset();

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
* Decode color to retrive node ID
*/
int Global::colorToId(ofColor color) {
	return (color.r * (256 * 256)) + (color.g * 256) + color.b;
}
