/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
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
    std::string getCurrentSkybox() const;
private:
    ofShader m_shader;
    ofTexture m_cubemapTexture;
//    ofTexture m_textures[6];
    ofMesh skyboxMesh;
    std::string m_currentSkybox;
};
