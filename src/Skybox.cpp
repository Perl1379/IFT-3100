/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Skybox class implementation
 *
 *****************************************************/
#include "Skybox.h"

#include <ofGraphics.h>
#include <ofImage.h>


/**
 * Setup skybox
 */
void Skybox::setup(const std::string& p_theme) {

    if (!m_shader.isLoaded()) {
        // Load the shader
        m_shader.load("skybox/shaders/skybox.vert", "skybox/shaders/skybox.frag");
    }

    m_currentSkybox = p_theme;

    std::string faces[6] = {
        "skybox/images/" + p_theme + "/right.png", "skybox/images/" + p_theme + "/left.png",
        "skybox/images/" + p_theme + "/top.png", "skybox/images/" + p_theme + "/bottom.png",
        "skybox/images/" + p_theme + "/back.png", "skybox/images/" + p_theme + "/front.png"
    };

    for (int i = 0; i < 6; i++) {

        if (!ofLoadImage(m_textures[i],faces[i])) {
            ofLogError("Skybox") << "Failed to load image " << faces[i];
            ofExit(-1);
        }
    }

    float size = 500;  // Size of the cube

    // Create a custom mesh for the skybox
    skyboxMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    // Define the vertices for the cube (8 unique vertices)
    std::vector<glm::vec3> vertices = {
        // Front face
        glm::vec3(-size, -size,  size), // 0
        glm::vec3( size, -size,  size), // 1
        glm::vec3( size,  size,  size), // 2
        glm::vec3(-size,  size,  size), // 3

        // Back face
        glm::vec3( size, -size, -size), // 4
        glm::vec3(-size, -size, -size), // 5
        glm::vec3(-size,  size, -size), // 6
        glm::vec3( size,  size, -size), // 7
    };

    // Define the indices for the cube (12 triangles, 2 per face)
    std::vector<unsigned int> indices = {
        // Front face
        0, 1, 2, 2, 3, 0,

        // Back face
        4, 5, 6, 6, 7, 4,

        // Left face
        5, 0, 3, 3, 6, 5,

        // Right face
        1, 4, 7, 7, 2, 1,

        // Top face
        3, 2, 7, 7, 6, 3,

        // Bottom face
        5, 4, 1, 1, 0, 5
    };

    // Define texture coordinates for each vertex
    std::vector<glm::vec2> texCoords = {
        // Front face
        glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),

        // Back face
        glm::vec2(1, 0), glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1),

        // Left face
        glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),

        // Right face
        glm::vec2(1, 0), glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1),

        // Top face
        glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0), glm::vec2(0, 0),

        // Bottom face
        glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1)
    };

    // Add vertices, indices, and texture coordinates to the mesh
    skyboxMesh.addVertices(vertices);
    skyboxMesh.addIndices(indices);
    skyboxMesh.addTexCoords(texCoords);

}


/**
 * Draw skybox
 */
void Skybox::draw(const ofVec3f& cameraPosition) {
    ofDisableDepthTest(); // Ensure skybox renders in the background

    m_shader.begin();
    for (int i = 0; i < 6; i++) {
        m_shader.setUniformTexture("Tex" + ofToString(i), m_textures[i], i);
    }
    ofTranslate(cameraPosition);
    skyboxMesh.draw();
    ofTranslate(-cameraPosition);
    m_shader.end();
    ofEnableDepthTest();
}


/**
 * Get current skybox name
 */
std::string Skybox::getCurrentSkybox() const {
    return m_currentSkybox;
}

