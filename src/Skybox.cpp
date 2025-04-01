/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * Skybox class implementation
 *
 *****************************************************/
#include "Skybox.h"

#include <ofGraphics.h>
#include <ofImage.h>
#include <ofPixels.h>


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
        "skybox/images/" + p_theme + "/left.png",
        "skybox/images/" + p_theme + "/right.png",
        "skybox/images/" + p_theme + "/top.png",
        "skybox/images/" + p_theme + "/bottom.png",
        "skybox/images/" + p_theme + "/back.png",
        "skybox/images/" + p_theme + "/front.png"
    };


    m_cubemapTexture.allocate(1024, 1024, GL_RGB, GL_TEXTURE_CUBE_MAP);
    m_cubemapTexture.bind();


    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Load images
    for (int i = 0; i < 6; i++) {
        ofImage image;

        if (!image.load(faces[i])) {
            ofLogError("Skybox") << "Failed to load image " << faces[i];
            ofExit(-1);
        }

        ofPixels pixels = image.getPixels();
        if (pixels.getNumChannels() == 4) {
            pixels.setImageType(OF_IMAGE_COLOR);  // Converts RGBA → RGB
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0, GL_RGB, pixels.getWidth(), pixels.getHeight(),
                     0, GL_RGB, GL_UNSIGNED_BYTE, pixels.getData());

    }

    m_cubemapTexture.unbind();

    float size = 500.0f;  // Size of the skybox

    skyboxMesh.setMode(OF_PRIMITIVE_TRIANGLES);

    // Define the cube with normalized texture coordinates (-1 to 1)
    std::vector<glm::vec3> vertices = {
        // Right face
        {size, -size, -size}, {size, -size, size}, {size, size, size},
        {size, size, size}, {size, size, -size}, {size, -size, -size},

        // Left face
        {-size, -size, size}, {-size, -size, -size}, {-size, size, -size},
        {-size, size, -size}, {-size, size, size}, {-size, -size, size},

        // Top face
        {-size, size, -size}, {size, size, -size}, {size, size, size},
        {size, size, size}, {-size, size, size}, {-size, size, -size},

        // Bottom face
        {-size, -size, -size}, {-size, -size, size}, {size, -size, size},
        {size, -size, size}, {size, -size, -size}, {-size, -size, -size},

        // Front face
        {-size, -size, size}, {-size, size, size}, {size, size, size},
        {size, size, size}, {size, -size, size}, {-size, -size, size},

        // Back face
        {size, -size, -size}, {size, size, -size}, {-size, size, -size},
        {-size, size, -size}, {-size, -size, -size}, {size, -size, -size}
    };

    // Add vertices to the mesh
    skyboxMesh.addVertices(vertices);


    //for (int i = 0; i < 6; i++) {
    //
    //     if (!ofLoadImage(m_textures[i],faces[i])) {
    //         ofLogError("Skybox") << "Failed to load image " << faces[i];
    //         ofExit(-1);
    //     }
    // }
    //
    //
    //
    // float size = 500;  // Size of the cube
    // //
    // // // Create a custom mesh for the skybox
    // skyboxMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    // // Define the vertices for the cube (8 unique vertices)
    // std::vector<glm::vec3> vertices = {
    //      // Front face
    //      glm::vec3(-size, -size,  size), // 0
    //      glm::vec3( size, -size,  size), // 1
    //      glm::vec3( size,  size,  size), // 2
    //      glm::vec3(-size,  size,  size), // 3
    //
    //      // Back face
    //      glm::vec3( size, -size, -size), // 4
    //      glm::vec3(-size, -size, -size), // 5
    //      glm::vec3(-size,  size, -size), // 6
    //      glm::vec3( size,  size, -size), // 7
    //  };
    //
    //  // Define the indices for the cube (12 triangles, 2 per face)
    //  std::vector<unsigned int> indices = {
    //      // Front face
    //      0, 1, 2, 2, 3, 0,
    //
    //      // Back face
    //      4, 5, 6, 6, 7, 4,
    //
    //      // Left face
    //      5, 0, 3, 3, 6, 5,
    //
    //      // Right face
    //      1, 4, 7, 7, 2, 1,
    //
    //      // Top face
    //      3, 2, 7, 7, 6, 3,
    //
    //      // Bottom face
    //      5, 4, 1, 1, 0, 5
    //  };
    //
    // // // Define texture coordinates for each vertex
    // // std::vector<glm::vec2> texCoords = {
    // //     // Front face
    // //     glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),
    // //
    // //     // Back face
    // //     glm::vec2(1, 0), glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1),
    // //
    // //     // Left face
    // //     glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),
    // //
    // //     // Right face
    // //     glm::vec2(1, 0), glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1),
    // //
    // //     // Top face
    // //     glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0), glm::vec2(0, 0),
    // //
    // //     // Bottom face
    // //     glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1)
    // // };
    // //
    // // // Add vertices, indices, and texture coordinates to the mesh
    // skyboxMesh.addVertices(vertices);
    // skyboxMesh.addIndices(indices);
    // // skyboxMesh.addTexCoords(texCoords);

}


/**
 * Draw skybox
 */
void Skybox::draw(const ofVec3f& cameraPosition) {

    ofDisableDepthTest();
//    glDepthFunc(GL_LEQUAL);  // Ensure skybox is drawn correctly behind everything
    m_shader.begin();

    ofMatrix4x4 viewMatrix = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);
    viewMatrix.setTranslation(0, 0, 0); // Remove translation from the camera (skybox remains static)

    m_shader.setUniformMatrix4f("view", viewMatrix);
    m_shader.setUniformMatrix4f("projection", ofGetCurrentMatrix(OF_MATRIX_PROJECTION));
    m_shader.setUniformTexture("skybox", m_cubemapTexture, 0);

    glActiveTexture(GL_TEXTURE0);
    m_cubemapTexture.bind();

    skyboxMesh.draw(); // Draw cube without texture coordinates

    m_cubemapTexture.unbind();
    m_shader.end();
    //glDepthFunc(GL_LESS); // Restore depth test
    ofEnableDepthTest();

    // ofDisableDepthTest(); // Ensure skybox renders in the background
    //
    // m_shader.begin();
    // for (int i = 0; i < 6; i++) {
    //     m_shader.setUniformTexture("Tex" + ofToString(i), m_textures[i], i);
    // }
    // ofTranslate(cameraPosition);
    // skyboxMesh.draw();
    // ofTranslate(-cameraPosition);
    // m_shader.end();
    // ofEnableDepthTest();
}


/**
 * Get current skybox name
 */
std::string Skybox::getCurrentSkybox() const {
    return m_currentSkybox;
}

