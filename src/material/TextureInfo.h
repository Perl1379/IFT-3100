/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * TextureInfo class definition
 *
 *****************************************************/
#pragma once
#include <any>
#include <ofTexture.h>
#include <ofImage.h>
#include <string>


enum TEXTURE_TYPE {
    TEXTURE_FLAT_COLOR = 0,
    TEXTURE_FILE = 1,
    TEXTURE_PROCGEN = 2
};


class TextureInfo {

private:
    int m_filterMinimum = GL_LINEAR;
    int m_filterMaximum = GL_LINEAR;
    int m_wrapMode = GL_REPEAT;
    float m_textureScale = 1.0f;
    int m_textureType;
    std::any m_textureParameters;
    ofTexture m_texture;

public:
    TextureInfo();
    void setup(const ofFloatColor &p_color);
    void setMinMaxFilters(int p_min, int p_max);
    void setTextureScale(float p_scale);
    void setTextureWrap(int p_wrapMode);
    bool loadTexture(TEXTURE_TYPE type, const std::any &parameters);

    const ofTexture* getTexture();
    std::any getTextureParameters();
    int getTextureType();
    std::string getPropertyValue();
    void setPropertyValue(std::string p_value);
    int getFilterMinimum() const { return m_filterMinimum; }
    int getFilterMaximum() const { return m_filterMaximum; }
    float getTextureScale() const { return m_textureScale; }
    int getTextureWrapMode() const { return m_wrapMode; }
};
