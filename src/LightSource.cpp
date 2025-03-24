/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * Lightsource class implementation
 *
 *****************************************************/
#include "LightSource.h"

#include <ofAppRunner.h>
#include <ofVec3f.h>


/**
 * Light source setup
 */
void LightSource::setup() {
    m_light = new ofLight();
    m_light->setup();
    m_light->disable();
    m_light->setAttenuation(1.0, 0, 0);

}


/**
 * Set if light source is enabled
 */
void LightSource::setEnabled(bool enabled) {
    m_enabled = enabled;
    if (m_enabled) {
        m_light->enable();
    } else {
        m_light->disable();
    }
}


/**
 * Is light source enabled?
 */
bool LightSource::getEnabled() {
    return m_enabled;
}


/**
 * Set light source position
 */
void LightSource::setPosition(const ofVec3f &position) {
    m_light->setPosition(position);
}


/**
 * Set light source orientation
 */
void LightSource::setOrientation(const ofVec3f &orientation) {
    m_light->setOrientation(orientation);

}


/**
 * Set light source scale
 */
void LightSource::setScale(const ofVec3f &scale) {
    m_light->setScale(scale);
}


/**
 * Set light source attenuation (linear)
 */
void LightSource::setAttenuation(float attenuation) {
    m_light->setAttenuation(1.0, attenuation);
}


/**
 * Get light source attenuation (linear)
 */
float LightSource::getAttenuation() const {
    return m_light->getAttenuationLinear();
}


/**
 * Set light source type
 */
void LightSource::setLightType(LIGHT_TYPE type) {
    switch (type) {
        case DIRECTIONAL_LIGHT:
            m_light->setDirectional();
            break;
        case POINT_LIGHT:
            m_light->setPointLight();
            break;
        case SPOT_LIGHT:
            m_light->setSpotlight();
            break;
    }
}


/**
 * Get light source type
 */
LIGHT_TYPE LightSource::getLightType() {

    if (m_light->getIsDirectional()) return DIRECTIONAL_LIGHT;
    else if (m_light->getIsSpotlight()) return SPOT_LIGHT;
    else return POINT_LIGHT;
}



/**
 * Get light source position
 */
ofVec3f LightSource::getPosition() const {
    return m_light->getPosition();
}


/**
 * Get light source orientation
 */
ofVec3f LightSource::getOrientation() const {
    return m_light->getOrientationEulerDeg();
}


/**
 * Get light source orientation
 */
ofVec3f LightSource::getScale() const {
    return m_light->getScale();
}


/**
 * Set ambient color
 */
void LightSource::setColorAmbient(const ofFloatColor &color) {
    m_light->setAmbientColor(color);
}


/**
 * Set diffuse color
 */
void LightSource::setColorDiffuse(const ofFloatColor &color) {
    m_light->setDiffuseColor(color);
}


/**
 * Set specular color
 */
void LightSource::setColorSpecular(const ofFloatColor &color) {
    m_light->setSpecularColor(color);
}


/**
 * get ambient color
 */
ofFloatColor LightSource::getColorAmbient() const {
    return m_light->getAmbientColor();
}


/**
 * get diffuse color
 */
ofFloatColor LightSource::getColorDiffuse() const {
    return m_light->getDiffuseColor();
}


/**
 * get specular color
 */
ofFloatColor LightSource::getColorSpecular() const {
    return m_light->getSpecularColor();
}

