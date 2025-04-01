/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * Lightsource class definition
 *
 *****************************************************/
#pragma once
#include <ofLight.h>

enum LIGHT_TYPE {
    SPOT_LIGHT = 0,
    POINT_LIGHT = 1,
    DIRECTIONAL_LIGHT = 2
};

class LightSource {
private:
    ofLight* m_light;
    int m_lightType;
    bool m_enabled = true;
    int m_bindCamera = -1;

public:
    void setup();
    void setEnabled(bool enabled);
    void update();
    void setCameraBind(int cameraIndex);
    int getCameraBind();

    bool getEnabled();

    void setPosition(const ofVec3f &position);
    ofVec3f getPosition() const;
    void setOrientation(const ofVec3f &orientation);
    ofVec3f getOrientation() const;
    void setScale(const ofVec3f &scale);
    ofVec3f getScale() const;
    void setAttenuation(float attenuation);
    float getAttenuation() const;


    void setLightType(LIGHT_TYPE type);
    LIGHT_TYPE getLightType();

    void setColorAmbient(const ofFloatColor &color);
    void setColorDiffuse(const ofFloatColor &color);
    void setColorSpecular(const ofFloatColor &color);
    ofFloatColor getColorAmbient() const;
    ofFloatColor getColorDiffuse() const;
    ofFloatColor getColorSpecular() const;

};
