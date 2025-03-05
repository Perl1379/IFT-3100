//
// Created by cobolfoo on 3/5/25.
//

#include "ofxCustomAssimpModelLoader.h"

#include <ofGraphics.h>

/**
 * Draw faces
 */
void ofxCustomAssimpModelLoader::drawFaces(){
    draw(OF_MESH_FILL);
}


/**
 * Draw meshes (only enabled ones)
 */
void ofxCustomAssimpModelLoader::draw(ofPolyRenderMode renderType) {
    if(scene == NULL) {
        return;
    }

    ofPushStyle();

    ofPushMatrix();
    ofMultMatrix(modelMatrix);

#ifndef TARGET_OPENGLES
    glPolygonMode(GL_FRONT_AND_BACK, ofGetGLPolyMode(renderType));
#endif

    for(size_t i = 0; i < modelMeshes.size(); i++) {
        if (!m_meshEnabled[i]) continue;
        ofxAssimpMeshHelper & mesh = modelMeshes[i];

        ofPushMatrix();
        ofMultMatrix(mesh.matrix);

        if(bUsingTextures){
            if(mesh.hasTexture(aiTextureType_DIFFUSE)) {
                mesh.getTextureRef(aiTextureType_DIFFUSE).bind();
            }
        }

        if(bUsingMaterials){
            mesh.material.begin();
        }

        //		this was broken / backwards
        if(!mesh.twoSided && mCullType >= 0) {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(mCullType);
        }
        else {
            glDisable(GL_CULL_FACE);
        }



        ofEnableBlendMode(mesh.blendMode);

#ifndef TARGET_OPENGLES
        mesh.vbo.drawElements(GL_TRIANGLES,mesh.indices.size());
#else
        switch(renderType){
            case OF_MESH_FILL:
                mesh.vbo.drawElements(GL_TRIANGLES,mesh.indices.size());
            break;
            case OF_MESH_WIREFRAME:
                //note this won't look the same as on non ES renderers.
                    //there is no easy way to convert GL_TRIANGLES to outlines for each triangle
                        mesh.vbo.drawElements(GL_LINES,mesh.indices.size());
            break;
            case OF_MESH_POINTS:
                mesh.vbo.drawElements(GL_POINTS,mesh.indices.size());
            break;
        }
#endif

        if(bUsingTextures){
            if(mesh.hasTexture(aiTextureType_DIFFUSE)) {
                mesh.getTextureRef(aiTextureType_DIFFUSE).unbind();
            }
        }

        if(!mesh.twoSided) {
            glDisable(GL_CULL_FACE);
        }

        if(bUsingMaterials){
            mesh.material.end();
        }

        ofPopMatrix();
    }

#ifndef TARGET_OPENGLES
    //set the drawing mode back to FILL if its drawn the model with a different mode.
    if( renderType != OF_MESH_FILL ){
        glPolygonMode(GL_FRONT_AND_BACK, ofGetGLPolyMode(OF_MESH_FILL));
    }
#endif

    ofPopMatrix();
    ofPopStyle();
}


/**
 * Called after load, we create our list of enable mesesh
 */
bool ofxCustomAssimpModelLoader::createEnabledMeshes() {
    bool result = ofxAssimpModelLoader::processScene();

    m_meshEnabled.clear();
    for (int i=0; i<modelMeshes.size(); i++) {
        m_meshEnabled.push_back(true);
    }

    return result;
}


/**
 * Set mesh enabled (by mesh name)
 */
void ofxCustomAssimpModelLoader::setMeshEnabled(const std::string& p_meshName, bool p_value) {
    std::vector<std::string> meshNames = getMeshNames();
    for (int i = 0; i < meshNames.size(); i++) {
        if (meshNames[i] == p_meshName) {
            m_meshEnabled[i] = p_value;
            return;
        }
    }
}


/**
 * Set mesh enabled (by index)
 */
void ofxCustomAssimpModelLoader::setMeshEnabled(int p_index, bool p_value) {
    m_meshEnabled[p_index] = p_value;
}

/**
 * Load model and enable specific meshes
 */
bool ofxCustomAssimpModelLoader::loadModel(const std::string & p_filename) {
    bool result = ofxAssimpModelLoader::loadModel(p_filename);
    createEnabledMeshes();

    ofFile file(p_filename + ".disabled");
    if (file.exists()) {
        ofBuffer buffer(file);
        for (auto &line : buffer.getLines()) {
            setMeshEnabled(line, false);
        }
    }

    return result;
}
