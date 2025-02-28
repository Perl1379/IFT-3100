#include "Skybox.h"

void Skybox::setup() {
    // Load the shader
    shader.load("shaders/skybox.vert", "shaders/skybox.frag");

    // Load six textures manually
    string faces[6] = {
        "images/skybox/front.png", "images/skybox/back.png",
        "images/skybox/left.png", "images/skybox/right.png",
        "images/skybox/top.png", "images/skybox/bottom.png"
    };

    for (int i = 0; i < 6; i++) {
        ofLoadImage(textures[i],faces[i]);
    }

	box.set(512); // Set the size of the skybox
}

void Skybox::draw() {
    ofDisableDepthTest(); // Ensure skybox renders in the background
	shader.begin();
	for (int i = 0; i < 6; i++) {
        shader.setUniformTexture("Tex" + ofToString(i), textures[i], i);
	}
    box.draw();
	shader.end();
    ofEnableDepthTest();
}