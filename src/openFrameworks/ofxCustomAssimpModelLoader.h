#pragma once
#include <ofxAssimpModelLoader.h>


class ofxCustomAssimpModelLoader : public ofxAssimpModelLoader {

private:
    std::vector<bool> m_meshEnabled;
    bool createEnabledMeshes();

public:
    bool load(const std::string & p_filename);
    void draw(ofPolyRenderMode renderType);
    void drawFaces();
    void setMeshEnabled(const std::string& p_meshName, bool p_value);
    void setMeshEnabled(int p_index, bool p_value);
};




