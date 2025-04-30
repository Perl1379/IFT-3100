/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * TextureInfo class implementation
 *
 *****************************************************/

#include "TextureInfo.h"
#include <ofPixels.h>
#include <ofImage.h>
#include <PerlinNoiseTexture.h>


/**
 * Constructor
 */
TextureInfo::TextureInfo() {
}


/**
 * Texture setup
 */
void TextureInfo::setup(const ofFloatColor& p_color) {

    loadTexture(TEXTURE_FLAT_COLOR, p_color);

}


/**
 * Load texture
 */
bool TextureInfo::loadTexture(TEXTURE_TYPE p_type, const std::any& p_parameters) {
    bool success = false;

    m_textureType = p_type;

    switch(p_type) {

        case TEXTURE_FLAT_COLOR:
        {
            auto p_color = std::any_cast<ofFloatColor>(p_parameters);
            ofImage plainTexture;
            plainTexture.allocate(1, 1, OF_IMAGE_COLOR); // 1x1 white texture
            plainTexture.setColor(0,0, p_color);  // Create a white texture
            plainTexture.update(); // Make sure it's updated
            m_texture.allocate(plainTexture);
            m_textureType = TEXTURE_FLAT_COLOR;
            m_textureParameters = p_color;

        }
        break;

        case TEXTURE_FILE:
        {
            ofImage image;
            auto filename = std::any_cast<std::string>(p_parameters);
            
#ifdef TARGET_WIN32
            std::replace(filename.begin(), filename.end(), '/', '\\');
#endif
            
            image.load(filename);
            m_texture.allocate(image);
            m_textureParameters = filename;


        }
        break;

        case TEXTURE_PROCGEN:
        {
            auto procgen = std::any_cast<std::string>(p_parameters);
            m_textureParameters = p_parameters;
            int width = 512;
            int height = 512;
            ofImage image;
            image.allocate(width, height, OF_IMAGE_COLOR);

            if (procgen == "perlin") {
                PerlinNoiseTexture perlinNoise;
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        double noiseValue = perlinNoise.noise(x * 0.1, y * 0.1, 0.0);
                        noiseValue = ofMap(noiseValue, -1, 1, 0, 255);
                        image.setColor(x, y, ofColor(noiseValue,noiseValue,noiseValue));
                    }
                }
                image.update();
                m_texture.allocate(image);
            } else if (procgen == "checkerboard") {
                // checkerboard
                int tileSize = 32;

                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        int tileX = x / tileSize;
                        int tileY = y / tileSize;

                        if ((tileX + tileY) % 2 == 0) {
                            image.setColor(x, y, ofColor(255,255,255));
                        } else {
                            image.setColor(x, y, ofColor(0,0,0));
                        }
                    }
                }
                image.update();
                m_texture.allocate(image);
            } else if (procgen == "radial_gradient") {
                float cx = width / 2.0;
                float cy = height / 2.0;
                float maxDist = sqrt(cx*cx + cy*cy);

                for (int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        float dx = x - cx;
                        float dy = y - cy;
                        float dist = sqrt(dx*dx + dy*dy);
                        float brightness = ofMap(dist, 0, maxDist, 255, 0);
                        image.setColor(x, y, ofColor(brightness));
                    }
                }
                image.update();
                m_texture.allocate(image);
            }

        }
        break;
    }

    if ((m_filterMinimum == GL_NEAREST_MIPMAP_NEAREST) || (m_filterMinimum == GL_NEAREST_MIPMAP_LINEAR) || (m_filterMinimum == GL_LINEAR_MIPMAP_LINEAR) || (m_filterMinimum == GL_LINEAR_MIPMAP_NEAREST)) {
        m_texture.generateMipmap();
    }

    m_texture.setTextureWrap(m_wrapMode, m_wrapMode);
    m_texture.setTextureMinMagFilter(m_filterMinimum, m_filterMaximum);
    return success;
}


/**
 *  Get texture
 */
const ofTexture* TextureInfo::getTexture() {
    return &m_texture;
}


/**
 * Get texture parameters
 */
std::any TextureInfo::getTextureParameters() {
    return m_textureParameters;
}


/**
 * Get texture type
 */
int TextureInfo::getTextureType() {
    return m_textureType;
}


/**
 * Get property value (serialized)
 */
std::string TextureInfo::getPropertyValue() {

    std::string property;

    switch(m_textureType) {
        case TEXTURE_FLAT_COLOR: {
            auto color = std::any_cast<ofFloatColor>(m_textureParameters);
            property = "color=" + std::to_string(color.r)+","+ std::to_string(color.g)+","+ std::to_string(color.b);
        }
        break;
        case TEXTURE_FILE: {
            auto filename = std::any_cast<std::string>(m_textureParameters);
            property = "filename=" + filename;
        }
        break;

        case TEXTURE_PROCGEN: {
            auto procgen = std::any_cast<std::string>(m_textureParameters);
            property = "procgen=" + procgen;
        }
        break;
    }

    property += ";";
    property += std::to_string(m_texture.getWidth()) + ";" + std::to_string(m_texture.getHeight()) + ";";
    property += std::to_string(m_filterMinimum) + ";" + std::to_string(m_filterMaximum) + ";";
    property += std::to_string(m_wrapMode) + ";" + std::to_string(m_textureScale);

    return property;
}


/**
 * Load texture from serialized
 */
void TextureInfo::setPropertyValue(std::string p_value) {

    std::vector<std::string> params = ofSplitString(p_value, ";");
    std::vector<std::string> first = ofSplitString(params[0], "=");
    int minFilter = ofToInt(params[3]);
    int maxFilter = ofToInt(params[4]);

    int wrapMode = ofToInt(params[5]);
    float textureScale = ofToFloat(params[6]);

    setTextureWrap(wrapMode);
    setTextureScale(textureScale);

    setMinMaxFilters(minFilter, maxFilter);

    if (first[0] == "filename") {

        loadTexture(TEXTURE_FILE, first[1]);
    } else if (first[0] == "procgen") {
        loadTexture(TEXTURE_PROCGEN, first[1]);
    } else {
        // color
        std::vector<std::string> channels = ofSplitString(first[1], ",");
        ofFloatColor color;
        color.r = ofToFloat(channels[0]);
        color.g = ofToFloat(channels[1]);
        color.b = ofToFloat(channels[2]);

        loadTexture(TEXTURE_FLAT_COLOR, color);
    }

}

/**
 * Set min max filters
 */
void TextureInfo::setMinMaxFilters(int p_min, int p_max) {
    m_filterMinimum = p_min;
    m_filterMaximum = p_max;


    if ((p_min == GL_NEAREST_MIPMAP_NEAREST) || (p_min == GL_NEAREST_MIPMAP_LINEAR) || (p_min == GL_LINEAR_MIPMAP_LINEAR) || (p_min == GL_LINEAR_MIPMAP_NEAREST)) {
        m_texture.generateMipmap();
    }
    m_texture.setTextureMinMagFilter(m_filterMinimum, m_filterMaximum);
}


/**
 * Set texture scale
 */
void TextureInfo::setTextureScale(float p_scale) {
    m_textureScale = p_scale;
}


/**
 * Set texture wrap
 */
void TextureInfo::setTextureWrap(int p_wrapMode) {
    m_wrapMode = p_wrapMode;
    m_texture.setTextureWrap(m_wrapMode, m_wrapMode);
}


