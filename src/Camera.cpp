/*****************************************************
 * TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Camera class implementation
 *
 *****************************************************/

#include "Camera.h"

 /**
  * Setup camera with default values
  */
void Camera::setup(ofVec3f p_initialPosition, ofVec3f p_initialOrientation) {

	m_initialPosition = p_initialPosition;
	m_initialOrientation = p_initialOrientation;
	m_fboTexture.allocate(32, 32, GL_RGB);
	m_fboPickingTexture.allocate(32, 32, GL_RGB);

	reset();
}


/**
 * Reset camera state
 */
void Camera::reset() {
	m_camera.setPosition(m_initialPosition);
	m_camera.lookAt(m_initialOrientation);

}


/**
 * Resize FBO texture to match viewport size
 */
void Camera::resizeTextureIfNeeded() {

	if (m_viewportWidth == 0) return;
	if (m_viewportHeight == 0) return;

	int tw = (int)m_fboTexture.getWidth();
	int th = (int)m_fboTexture.getHeight();
	if (m_viewportWidth != tw || m_viewportHeight != th) {
		m_fboTexture.allocate(m_viewportWidth, m_viewportHeight, GL_RGB);
		m_fboPickingTexture.allocate(m_viewportWidth, m_viewportHeight, GL_RGB);
	}
}


/**
 * Set viewport size
 */
void Camera::setViewportSize(int width, int height) {
	m_viewportWidth = width;
	m_viewportHeight = height;
}

/**
 * Retrieve FBO texture
 */
ofFbo& Camera::getFbo() {
	return m_fboTexture;
}


/**
 * Retrieve FBO texture (Object picking)
 */
ofFbo& Camera::getPickingFbo() {
	return m_fboPickingTexture;
}


/**
 * Retrieve camera object
 */
ofCamera& Camera::getCamera() {
	return m_camera;
}
