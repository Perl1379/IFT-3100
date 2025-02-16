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
std::array<Camera,3> Global::m_cameras;

Level Global::level;


/**
 * Setup global singleton object
 */
void Global::setup() {

 m_cameras[0].setup(ofVec3f(0, 0, 100), ofVec3f(0, 0, 0));
 m_cameras[1].setup(ofVec3f(0, 100, 0), ofVec3f(0, 0, 0));
 m_cameras[2].setup(ofVec3f(100, 0, 0), ofVec3f(0, 0, 0));

 level.reset();

}