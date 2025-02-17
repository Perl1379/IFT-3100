#pragma once
#include <ofCamera.h>
#include <ofFbo.h>


class Camera {

  private:

    ofVec3f m_initial_position;
    ofVec3f m_initial_orientation;

    ofFbo m_fboTexture;
    ofCamera m_camera;
    int m_viewport_width = 0;
    int m_viewport_height = 0;


public:

    void setup(ofVec3f p_initial_position, ofVec3f p_initial_orientation);
    void reset();
    void setViewportSize(int width, int height);
    void resizeTextureIfNeeded();

    ofFbo & getFbo() {
        return m_fboTexture;
    }

    ofCamera & getCamera() {
        return m_camera;
    }

};
