/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * Skybox class implementation
 *
 *****************************************************/
#include "Skybox.h"

#include <Global.h>
#include <ofGraphics.h>
#include <ofImage.h>
#include <ofPixels.h>


/**
 * Setup skybox
 */
void Skybox::setup(const std::string& p_theme) {

    if (m_shader == nullptr) {
        m_shader = Global::m_shaders.getShader("skybox");
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


}


/**
 * Draw skybox
 */
void Skybox::draw(const ofVec3f& cameraPosition) {

    ofDisableDepthTest();
    m_shader->begin();

    ofMatrix4x4 viewMatrix = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);
    viewMatrix.setTranslation(0, 0, 0); // Remove translation from the camera (skybox remains static)

    m_shader->setUniformMatrix4f("view", viewMatrix);
    m_shader->setUniformMatrix4f("projection", ofGetCurrentMatrix(OF_MATRIX_PROJECTION));
    m_shader->setUniformTexture("skybox", m_cubemapTexture, 0);

    glActiveTexture(GL_TEXTURE0);
    m_cubemapTexture.bind();

    skyboxMesh.draw(); // Draw cube without texture coordinates

    m_cubemapTexture.unbind();
    m_shader->end();
    ofEnableDepthTest();

}


/**
 * Get current skybox name
 */
std::string Skybox::getCurrentSkybox() const {
    return m_currentSkybox;
}

