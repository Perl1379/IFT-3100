/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Skybox class definition
 *
 *****************************************************/
 #pragma once

#include <of3dPrimitives.h>
#include <ofShader.h>
#include <ofTexture.h>

class Skybox {

public:
    void setup(const std::string& p_preset);
    void draw(const ofVec3f& cameraPosition);

private:
    ofShader m_shader;
    ofTexture m_textures[6];
    ofBoxPrimitive m_box;
    ofMesh skyboxMesh;
};
