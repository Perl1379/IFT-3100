/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ShaderManager class implementation
 *
 *****************************************************/
#include "ShaderManager.h"


/**
 * Load all shaders
 */
bool ShaderManager::setup() {

    if (!loadShader("skybox", "shaders/skybox.vert", "shaders/skybox.frag")) {
        return false;
    }

    if (!loadShader("tonemap_none", "shaders/tonemap/tonemap_none.vert", "shaders/tonemap/tonemap_none.frag")) {
        return false;
    }

    if (!loadShader("tonemap_grayscale", "shaders/tonemap/tonemap_grayscale.vert", "shaders/tonemap/tonemap_grayscale.frag")) {
        return false;
    }
    return true;
}


/**
 * Load shader
 */
bool ShaderManager::loadShader(const std::string &p_name, const std::string& p_vertexShader, const std::string& p_fragmentShader) {

    ofShader shader;
    if (!shader.load(p_vertexShader, p_fragmentShader)) return false;

    m_shaders[p_name] = shader;
    return true;
}


/**
 * Retrieve a specific shader
 */
ofShader *ShaderManager::getShader(const std::string &p_shaderName) {
    return &m_shaders[p_shaderName];
}


