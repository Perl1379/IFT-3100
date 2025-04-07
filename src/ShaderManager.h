/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ShaderManager class definition
 *
 *****************************************************/
#pragma once
#include <map>
#include <ofShader.h>

class ShaderManager {

private:
    std::map<std::string, ofShader> m_shaders;

    bool loadShader(const std::string &p_name, const std::string& p_vertexShader, const std::string& p_fragmentShader);

public:
    bool setup();
    ofShader* getShader(const std::string& p_shaderName);

};


