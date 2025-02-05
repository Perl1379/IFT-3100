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
ofFbo Global::m_fboCameraMain;
ofFbo Global::m_fboCameraSecond;
ofFbo Global::m_fboCameraThird;
Level Global::level;


/**
 * Setup global singleton object
 */
void Global::setup() {

 m_fboCameraMain.allocate(FBO_RESOLUTION, FBO_RESOLUTION, GL_RGB);
 m_fboCameraSecond.allocate(FBO_RESOLUTION, FBO_RESOLUTION, GL_RGB);
 m_fboCameraThird.allocate(FBO_RESOLUTION, FBO_RESOLUTION, GL_RGB);
 level.reset();

}