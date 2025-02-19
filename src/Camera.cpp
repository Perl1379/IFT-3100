//
// Created by cobolfoo on 2/13/25.
//

#include "Camera.h"

/**
*
*/
void Camera::setup(ofVec3f p_initial_position, ofVec3f p_initial_orientation) {

    m_initial_position = p_initial_position;
    m_initial_orientation = p_initial_orientation;
    m_fboTexture.allocate(32, 32, GL_RGB);
    m_fboPickingTexture.allocate(32, 32, GL_RGB);

    reset();
}


void Camera::reset() {
    m_camera.setPosition(m_initial_position);
    m_camera.lookAt(m_initial_orientation);

}


void Camera::resizeTextureIfNeeded() {

    if (m_viewport_width == 0) return;
    if (m_viewport_height == 0) return;

    int tw = (int) m_fboTexture.getWidth();
    int th = (int) m_fboTexture.getHeight();
    if (m_viewport_width != tw || m_viewport_height != th) {
        m_fboTexture.allocate(m_viewport_width, m_viewport_height, GL_RGB);
        m_fboPickingTexture.allocate(m_viewport_width, m_viewport_height, GL_RGB);
    }
}


void Camera::setViewportSize(int width, int height) {
    m_viewport_width = width;
    m_viewport_height = height;
}