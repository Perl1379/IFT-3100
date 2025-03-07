/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * TransformTools class implementation
 *
 *****************************************************/
#include "TransformTools.h"
#include <Global.h>
#include <ofGraphics.h>


/**
 * Object constructor
 */
TransformTools::TransformTools() {

    m_materialUnlit.setEmissiveColor(ofFloatColor(1.0, 1.0, 1.0));
    m_materialUnlit.setAmbientColor(ofFloatColor(0.0, 0.0, 0.0));
    m_materialUnlit.setDiffuseColor(ofFloatColor(0.0));
    m_materialUnlit.setSpecularColor(ofFloatColor(0.0));
    
    //"conePrimitives" are the points of the translation gizmo's arrows
    m_conePrimitives[0].setScale(m_conePrimitivesScale);
    m_conePrimitives[0].setOrientation(glm::vec3(0, 0, 90));
    m_conePrimitives[1].setScale(m_conePrimitivesScale);
    m_conePrimitives[1].setOrientation(glm::vec3(180, 0, 0));
    m_conePrimitives[2].setScale(m_conePrimitivesScale);
    m_conePrimitives[2].setOrientation(glm::vec3(-90, 0, 0));
    m_spherePrimitives[0].setScale(m_spherePrimitivesScale);
    m_spherePrimitives[1].setScale(m_spherePrimitivesScale);
    m_spherePrimitives[2].setScale(m_spherePrimitivesScale);
    m_cubePrimitives[0].setScale(m_cubePrimitivesScale);
    m_cubePrimitives[1].setScale(m_cubePrimitivesScale);
    m_cubePrimitives[2].setScale(m_cubePrimitivesScale);
    m_cubePrimitives[3].setScale(m_cubePrimitivesScale);

    m_conePrimitivesObjectPicking[0].setScale(m_conePrimitivesScaleObjectPicking);
    m_conePrimitivesObjectPicking[0].setOrientation(glm::vec3(0, 0, 90));
    m_conePrimitivesObjectPicking[1].setScale(m_conePrimitivesScaleObjectPicking);
    m_conePrimitivesObjectPicking[1].setOrientation(glm::vec3(180, 0, 0));
    m_conePrimitivesObjectPicking[2].setScale(m_conePrimitivesScaleObjectPicking);
    m_conePrimitivesObjectPicking[2].setOrientation(glm::vec3(-90, 0, 0));
    m_spherePrimitivesObjectPicking[0].setScale(m_spherePrimitivesScaleObjectPicking);
    m_spherePrimitivesObjectPicking[1].setScale(m_spherePrimitivesScaleObjectPicking);
    m_spherePrimitivesObjectPicking[2].setScale(m_spherePrimitivesScaleObjectPicking);
    m_cubePrimitivesObjectPicking[0].setScale(m_cubePrimitivesScaleObjectPicking);
    m_cubePrimitivesObjectPicking[1].setScale(m_cubePrimitivesScaleObjectPicking);
    m_cubePrimitivesObjectPicking[2].setScale(m_cubePrimitivesScaleObjectPicking);
    m_cubePrimitivesObjectPicking[3].setScale(m_cubePrimitivesScaleObjectPicking);

}

/**
 * Draw transform tools
 */
void TransformTools::draw(bool p_objectPicking) {
    if (Global::m_selectedNode == -1) return;

    BaseNode* node = Global::m_level.getTree()->findNode(Global::m_selectedNode);
    m_materialUnlit.begin();
    ofDisableDepthTest();

    m_transform.transformGL();
    m_transform.setOrientation(node->getTransform().getGlobalOrientation());
    m_transform.setPosition(node->getTransform().getGlobalPosition());


    switch(m_transformMode) {
        case TRANSLATE:
            drawTranslate(p_objectPicking, node);
            break;
        case ROTATE:
            drawRotate(p_objectPicking, node);
            break;
        case SCALE:
            drawScale(p_objectPicking, node);
            break;

    }

    m_transform.restoreTransformGL();
    ofEnableDepthTest();
    m_materialUnlit.end();

}


/**
 * Draw translate arrows
 */
void TransformTools::drawTranslate(bool p_objectPicking, BaseNode* node)  {

    glm::vec3 pos(0,0,0);
    auto scale = node->getTransform().getGlobalScale();
    auto length = node->getBoundingBox() * 0.5;

    if (p_objectPicking) {
        m_materialUnlit.setEmissiveColor(Global::idToColor(TRANSLATE_X));
    } else {
        m_materialUnlit.setEmissiveColor(ofFloatColor(1.0, 0.0, 0.0));
    }

    if (p_objectPicking) {
        m_conePrimitivesObjectPicking[0].setPosition(pos + glm::vec3(abs(length[0] * scale.x), 0.0, 0.0));
        m_conePrimitivesObjectPicking[0].draw();
    } else {
        ofDrawLine(pos, pos + glm::vec3(abs(length[0] * scale.x), 0.0, 0.0));
        m_conePrimitives[0].setPosition(pos + glm::vec3(abs(length[0] * scale.x), 0.0, 0.0));
        m_conePrimitives[0].draw();
    }

    if (p_objectPicking) {
        m_materialUnlit.setEmissiveColor(Global::idToColor(TRANSLATE_Y));
    } else {
        m_materialUnlit.setEmissiveColor(ofFloatColor(0.0, 1.0, 0.0));
    }

    if (p_objectPicking) {
        m_conePrimitivesObjectPicking[1].setPosition(pos + glm::vec3(0, abs(length[1] * scale.y), 0.0));
        m_conePrimitivesObjectPicking[1].draw();
    } else {
        ofDrawLine(pos, pos + glm::vec3(0.0, abs(length[1] * scale.y), 0.0));
        m_conePrimitives[1].setPosition(pos + glm::vec3(0, abs(length[1] * scale.y), 0.0));
        m_conePrimitives[1].draw();
    }

    if (p_objectPicking) {
        m_materialUnlit.setEmissiveColor(Global::idToColor(TRANSLATE_Z));
    } else {
        m_materialUnlit.setEmissiveColor(ofFloatColor(0.0, 0.0, 1.0));
    }

    if (p_objectPicking) {
        m_conePrimitivesObjectPicking[2].setPosition(pos + glm::vec3(0.0, 0.0, abs(length[2] * scale.z)));
        m_conePrimitivesObjectPicking[2].draw();
    } else {
        ofDrawLine(pos, pos + glm::vec3(0.0, 0.0, abs(length[2] * scale.z)));
        m_conePrimitives[2].setPosition(pos + glm::vec3(0.0, 0.0, abs(length[2] * scale.z)));
        m_conePrimitives[2].draw();

    }

}



/**
 * Draw rotate circles
 */
void TransformTools::drawRotate(bool p_objectPicking, BaseNode* node)  {

    glm::vec3 pos(0,0,0);
    auto scale = node->getTransform().getScale();
    auto length = node->getBoundingBox() * 0.5;
    ofNoFill();

    if (p_objectPicking) {
        m_materialUnlit.setEmissiveColor(Global::idToColor(ROTATE_X));
    } else {
        m_materialUnlit.setEmissiveColor(ofFloatColor(1.0, 0.0, 0.0));
    }

    if (p_objectPicking) {
        m_spherePrimitivesObjectPicking[0].setPosition(pos + glm::vec3(length[0] * scale.x, 0.0, 0.0));
        m_spherePrimitivesObjectPicking[0].draw();

    } else {
        ofNoFill();
        ofDrawCircle(pos, length[0] * scale.x);
        ofFill();
        m_spherePrimitives[0].setPosition(pos + glm::vec3(length[0] * scale.x, 0.0, 0.0));
        m_spherePrimitives[0].draw();
    }

    if (p_objectPicking) {
        m_materialUnlit.setEmissiveColor(Global::idToColor(ROTATE_Y));
    } else {
        m_materialUnlit.setEmissiveColor(ofFloatColor(0.0, 1.0, 0.0));
    }

    if (p_objectPicking) {
        m_spherePrimitivesObjectPicking[1].setPosition(pos + glm::vec3(0, length[1] * scale.y, 0.0));
        m_spherePrimitivesObjectPicking[1].draw();
    } else {
        ofPushMatrix();
        ofRotateYDeg(90);
        ofNoFill();
        ofDrawCircle(pos, length[1] * scale.y);
        ofFill();
        ofPopMatrix();;
        m_spherePrimitives[1].setPosition(pos + glm::vec3(0, length[1] * scale.y, 0.0));
        m_spherePrimitives[1].draw();

    }

    if (p_objectPicking) {
        m_materialUnlit.setEmissiveColor(Global::idToColor(ROTATE_Z));
    } else {
        m_materialUnlit.setEmissiveColor(ofFloatColor(0.0, 0.0, 1.0));
    }

    if (p_objectPicking) {
        m_spherePrimitivesObjectPicking[2].setPosition(pos + glm::vec3(0.0, 0.0, length[2] * scale.z));
        m_spherePrimitivesObjectPicking[2].draw();
    } else {
        ofPushMatrix();
        ofRotateXDeg(90);
        ofNoFill();
        ofDrawCircle(pos, length[2] * scale.z);
        ofFill();
        ofPopMatrix();;
        m_spherePrimitives[2].setPosition(pos + glm::vec3(0.0, 0.0, length[2] * scale.z));
        m_spherePrimitives[2].draw();
    }

}


/**
 * Draw scale cubes
 */
void TransformTools::drawScale(bool p_objectPicking, BaseNode* node)  {

    glm::vec3 pos(0,0,0);
    auto scale = node->getTransform().getScale();
    auto length = node->getBoundingBox() * 0.5;

    if (p_objectPicking) {
        m_materialUnlit.setEmissiveColor(Global::idToColor(SCALE_X));
    } else {
        m_materialUnlit.setEmissiveColor(ofFloatColor(1.0, 0.0, 0.0));
    }

    if (p_objectPicking) {
        m_cubePrimitivesObjectPicking[0].setPosition(pos + glm::vec3(length[0] * scale.x, 0.0, 0.0));
        m_cubePrimitivesObjectPicking[0].draw();
    } else {
        ofDrawLine(pos, pos + glm::vec3(length[0] * scale.x, 0.0, 0.0));
        m_cubePrimitives[0].setPosition(pos + glm::vec3(length[0] * scale.x, 0.0, 0.0));
        m_cubePrimitives[0].draw();
    }

    if (p_objectPicking) {
        m_materialUnlit.setEmissiveColor(Global::idToColor(SCALE_Y));
    } else {
        m_materialUnlit.setEmissiveColor(ofFloatColor(0.0, 1.0, 0.0));
    }

    if (p_objectPicking) {
        m_cubePrimitivesObjectPicking[1].setPosition(pos + glm::vec3(0, length[1] * scale.y, 0.0));
        m_cubePrimitivesObjectPicking[1].draw();
    } else {
        ofDrawLine(pos, pos + glm::vec3(0.0, length[1] * scale.y, 0.0));
        m_cubePrimitives[1].setPosition(pos + glm::vec3(0, length[1] * scale.y, 0.0));
        m_cubePrimitives[1].draw();
    }

    if (p_objectPicking) {
        m_materialUnlit.setEmissiveColor(Global::idToColor(SCALE_Z));
    } else {
        m_materialUnlit.setEmissiveColor(ofFloatColor(0.0, 0.0, 1.0));
    }

    if (p_objectPicking) {
        m_cubePrimitivesObjectPicking[2].setPosition(pos + glm::vec3(0.0, 0.0, length[2] * scale.z));
        m_cubePrimitivesObjectPicking[2].draw();
    } else {
        ofDrawLine(pos, pos + glm::vec3(0.0, 0.0, length[2] * scale.z));
        m_cubePrimitives[2].setPosition(pos + glm::vec3(0.0, 0.0, length[2] * scale.z));
        m_cubePrimitives[2].draw();
    }

    if (p_objectPicking) {
        m_materialUnlit.setEmissiveColor(Global::idToColor(SCALE_ALL));
    } else {
        m_materialUnlit.setEmissiveColor(ofFloatColor(1.0, 0.0, 1.0));
    }

    if (p_objectPicking) {
        m_cubePrimitivesObjectPicking[2].setPosition(pos);
        m_cubePrimitivesObjectPicking[2].draw();
    } else {
        m_cubePrimitives[2].setPosition(pos);
        m_cubePrimitives[2].draw();
    }

}


/**
 * Begin transformation
 */
void TransformTools::onMouseButtonPressed(int p_transformPixelColor, ImVec2 mousePosition) {

    m_previousMousePosition = mousePosition;
    m_currentTransformPixelColor = p_transformPixelColor;
    BaseNode* node = Global::m_level.getTree()->findNode(Global::m_selectedNode);
    if (node != nullptr) {
        m_initialNodePosition = node->getTransform().getPosition();
        m_initialNodeOrientation = node->getTransform().getOrientationEulerDeg();
        m_initialNodeScale = node->getTransform().getScale();
    }

}


/**
 * Apply temporary changes to node
 */
void TransformTools::onMouseDrag(ImVec2 mousePosition) {

    if (m_currentTransformPixelColor == -1) return;

    // Get difference between previous mouse position and current one
    glm::vec2 diff = mousePosition - m_previousMousePosition;
    m_previousMousePosition = mousePosition;
    float mouseSpeedTranslate = 5.0f;
    float mouseSpeedRotate = 0.5f;
    float mouseSpeedScale = 0.025f;

    BaseNode* node = Global::m_level.getTree()->findNode(Global::m_selectedNode);

    // Access the camera's view matrix
    glm::vec3 cameraRight = Global::m_cameras[m_camera_index].getCamera()->getXAxis();
    glm::vec3 cameraUp = Global::m_cameras[m_camera_index].getCamera()->getYAxis();
    glm::vec3 cameraForward = Global::m_cameras[m_camera_index].getCamera()->getZAxis();
    glm::vec3 nodeUp = node->getTransform().getYAxis();
    glm::vec3 nodeRight = node->getTransform().getXAxis();
    glm::vec3 nodeForward = node->getTransform().getZAxis();


    // Depending on the selected axis, update the position
    switch(m_currentTransformPixelColor) {
        case TRANSLATE_X: {
            float rightDirection = glm::dot(nodeRight, cameraRight);
            node->getTransform().truck(diff.x * mouseSpeedTranslate * glm::sign(rightDirection));
        }
        break;

        case TRANSLATE_Y: {

            float upDirection = glm::dot(nodeUp, cameraUp);
            node->getTransform().boom(-diff.y * mouseSpeedTranslate * glm::sign(upDirection));

        }
        break;

        case TRANSLATE_Z: {
            float forwardDirection = glm::dot(nodeForward, cameraForward);
            node->getTransform().dolly(diff.x * mouseSpeedTranslate * glm::sign(forwardDirection));
        }
        break;

        case ROTATE_X: {

            float rightDirection = glm::dot(cameraRight, nodeForward);
            node->getTransform().rotateDeg(glm::sign(rightDirection) * -diff.x * mouseSpeedRotate, nodeForward);

        }
        break;
        case ROTATE_Y: {

            float upDirection = glm::dot(cameraUp, nodeRight);
            node->getTransform().rotateDeg(glm::sign(upDirection) * -diff.y * mouseSpeedRotate, nodeRight);
        }
        break;

        case ROTATE_Z: {
            float forwardDirection = glm::dot(cameraForward, nodeUp);
            node->getTransform().rotateDeg(glm::sign(forwardDirection) * -diff.x * mouseSpeedRotate, nodeUp);
        }
        break;

        case SCALE_X: {
            float rightDirection = glm::dot(cameraRight, nodeRight);
            glm::vec3 scale = node->getTransform().getScale();
            scale.x += glm::sign(rightDirection) * diff.x * mouseSpeedScale;
            node->getTransform().setScale(scale);
        }
        break;

        case SCALE_Y: {
            float upDirection = glm::dot(cameraUp, nodeUp);
            glm::vec3 scale = node->getTransform().getScale();
            scale.y += glm::sign(upDirection) * diff.y * mouseSpeedScale;
            node->getTransform().setScale(scale);
        }
        break;

        case SCALE_Z: {
            float forwardDirection = glm::dot(cameraForward, nodeForward);
            glm::vec3 scale = node->getTransform().getScale();
            scale.z += glm::sign(forwardDirection) * diff.x * mouseSpeedScale;
            node->getTransform().setScale(scale);
        }

        case SCALE_ALL: {
            glm::vec3 scale = node->getTransform().getScale();
            if (cameraForward.y < 0) {
                scale += diff.x * mouseSpeedScale;
            } else {
                scale -= diff.x * mouseSpeedScale;
            }
            node->getTransform().setScale(scale);
        }
        break;
    }
}


/**
 * Complete transformation
 */
void TransformTools::onMouseButtonReleased(ImVec2 mousePosition) {
    if (m_currentTransformPixelColor == -1) return;

    BaseNode* node = Global::m_level.getTree()->findNode(Global::m_selectedNode);
    if (node != nullptr) {
        switch (m_transformMode) {

            case TRANSLATE: {
                Global::m_actions.addAction(node, "Position", m_initialNodePosition, node->getTransform().getPosition());
            }
            break;

            case ROTATE: {
                Global::m_actions.addAction(node, "Orientation", m_initialNodeOrientation, node->getTransform().getOrientationEulerDeg());
            }
            break;

            case SCALE: {
                Global::m_actions.addAction(node, "Scale", m_initialNodeScale, node->getTransform().getScale());
            }
            break;
        }
    }
    m_currentTransformPixelColor = -1;
}


/**
 * Set camera index
 */
void TransformTools::setCameraIndex(int index) {
    m_camera_index = index;
}


/**
 * Get transform mode
 */
int TransformTools::getTransformMode() const {
    return m_transformMode;
}


/**
 * Set transform mode
 */
void TransformTools::setTransformMode(int mode) {
    m_transformMode = mode;
}
