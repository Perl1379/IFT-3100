/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * TransformTools class implementation
 *
 *****************************************************/
#pragma once
#include <BaseNode.h>
#include <imgui.h>
#include <of3dPrimitives.h>
#include <ofMaterial.h>

enum TRANSFORM_MODE {
    TRANSLATE,
    ROTATE,
    SCALE
};

enum TRANSFORM_PIXEL_COLOR {
    TRANSLATE_X = 991,
    TRANSLATE_Y = 992,
    TRANSLATE_Z = 993,
    ROTATE_X = 994,
    ROTATE_Y = 995,
    ROTATE_Z = 996,
    SCALE_X = 997,
    SCALE_Y = 998,
    SCALE_Z = 999,
    SCALE_ALL = 1000
};

class TransformTools {

    private:
        ofNode m_transform;
        int m_transformMode = TRANSFORM_MODE::TRANSLATE;
        int m_currentTransformPixelColor = -1;
        int m_camera_index = 0;
        ImVec2 m_previousMousePosition;
        glm::vec3 m_initialNodePosition;
        glm::vec3 m_initialNodeOrientation;
        glm::vec3 m_initialNodeScale;

        // Tweak size of gizmos here
        float m_conePrimitivesScale = 1.2;
        float m_spherePrimitivesScale = 1.2;
        float m_cubePrimitivesScale = 0.6;
        float m_conePrimitivesScaleObjectPicking = 2.4;
        float m_spherePrimitivesScaleObjectPicking = 2.4;
        float m_cubePrimitivesScaleObjectPicking = 1.2;

        ofMaterial m_materialUnlit;
        std::vector<ofConePrimitive> m_conePrimitives;
        std::vector<ofSpherePrimitive> m_spherePrimitives;
        std::vector<ofBoxPrimitive> m_cubePrimitives;
        std::vector<ofConePrimitive> m_conePrimitivesObjectPicking;
        std::vector<ofSpherePrimitive> m_spherePrimitivesObjectPicking;
        std::vector<ofBoxPrimitive> m_cubePrimitivesObjectPicking;

    public:
        TransformTools();

        void draw(bool p_objectPicking);
        void drawTranslate(bool p_objectPicking,BaseNode* node);
        void drawRotate(bool p_objectPicking, BaseNode* node);
        void drawScale(bool p_objectPicking, BaseNode* node);

        void setCameraIndex(int index);
        int getTransformMode() const;
        void setTransformMode(int mode);

        void onMouseButtonPressed(int p_transformPixelColor, ImVec2 mousePosition);
        void onMouseDrag(ImVec2 mousePosition);
        void onMouseButtonReleased(ImVec2 mousePosition);
        const std::vector<ofConePrimitive>& getConePrimitives();
        const std::vector<ofSpherePrimitive>& getSpherePrimitives();
        const std::vector<ofBoxPrimitive>& getCubePrimitives();

};


