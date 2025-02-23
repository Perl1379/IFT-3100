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
        int m_transformMode = TRANSFORM_MODE::TRANSLATE;
        int m_currentTransformPixelColor = -1;
        int m_camera_index = 0;
        ImVec2 m_previousMousePosition;
        glm::vec3 m_initialNodePosition;
        glm::vec3 m_initialNodeOrientation;
        glm::vec3 m_initialNodeScale;

        ofMaterial m_materialUnlit;
        ofConePrimitive m_conePrimitives[3];
        ofSpherePrimitive m_spherePrimitives[3];
        ofBoxPrimitive m_cubePrimitives[4];

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

};


