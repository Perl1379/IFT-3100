#pragma once
#include "ofMain.h"

class Skybox {
public:
    void setup();   // Load skybox textures and shader
    void draw();    // Render the skybox

private:
    ofShader shader;          // Shader for rendering the skybox
    ofTexture textures[6];    // Array to hold the six skybox textures
	ofBoxPrimitive box;	      // Box primitive to render the skybox
};