/*****************************************************
 * TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Camera class definition
 *
 *****************************************************/
#pragma once
#include <ofCamera.h>
#include <ofFbo.h>


class Camera {

private:

	ofVec3f m_initialPosition;
	ofVec3f m_initialOrientation;

	ofFbo m_fboTexture;
	ofFbo m_fboPickingTexture;
	ofCamera m_camera;
	int m_viewportWidth = 0;
	int m_viewportHeight = 0;


public:

	void setup(ofVec3f p_initial_position, ofVec3f p_initial_orientation);
	void reset();
	void setViewportSize(int p_width, int p_height);
	void resizeTextureIfNeeded();

	ofFbo& getFbo();
	ofFbo& getPickingFbo();
	ofCamera& getCamera();


};
