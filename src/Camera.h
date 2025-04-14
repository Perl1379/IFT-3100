/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * Camera class definition
 *
 *****************************************************/
#pragma once
#include <of3dPrimitives.h>
#include <ofCamera.h>
#include <ofCustomCamera.h>
#include <ofFbo.h>
#include <ofShader.h>


enum OCCLUSION_MODE {
	NO_OCCLUSION = 0,
	FRUSTUM_CULLING = 1
};


enum TONEMAP_TYPE {
	NO_TONEMAP = 0,
	GRAYSCALE = 1,
	SEPIA = 2
};


enum LIGHTMODEL_TYPE {
	OPENGL_LIGHTS = 0,
	LAMBERT = 1,
	GOURAUD = 2,
	PHONG = 3,
	BLINN_PHONG = 4,
	PBR = 5,
	NON_REALISTIC = 6
};


class Camera {


private:

	struct Plane {
		glm::vec3 normal;
		float d;

		// Normalize the plane
		void normalize() {
			float length = glm::length(normal);
			normal /= length;
			d /= length;
		}
	};
	std::array<Plane, 6> m_frustumPlanes;

	ofVec3f m_upVector = ofVec3f(0, 1, 0);
	ofVec3f m_initialPosition;
	ofVec3f m_initialOrientation;
	ofShader* m_shaderLight;
	int m_lightModel = OPENGL_LIGHTS;

	float m_initialFOV;
	float m_initialzNear;
	float m_initialzFar;
	OCCLUSION_MODE m_occlusion = FRUSTUM_CULLING;

	ofFbo m_fboTexture;
	ofFbo m_fboPickingTexture;
	ofFbo m_fboPostProcessTexture;
	ofMesh m_meshPostProcess;
	ofCustomCamera m_camera;
	int m_viewportWidth = 0;
	int m_viewportHeight = 0;
	std::array<Plane, 6> extractFrustumPlanes(const glm::mat4& m);
	ofShader* m_shaderTonemap = nullptr;
	std::map<std::string, float> m_tonemapUniforms;
	TONEMAP_TYPE m_tonemapType = NO_TONEMAP;

public:

	void setup(ofVec3f p_initial_position, ofVec3f p_initial_orientation);
	void reset();
	void update();
	void setViewportSize(int p_width, int p_height);
	void resizeTextureIfNeeded();
	void setUpVector(ofVec3f p_upVector) {
		m_upVector = p_upVector;
	}
	ofVec3f getUpVector() {
		return m_upVector;
	}

	bool testVisibility(const ofVec3f& p_position, const ofVec3f& p_boundingBox);
	bool isInsideFrustum(const ofVec3f& ofPosition, const ofVec3f& p_boundingBox);
	void setOcclusion(OCCLUSION_MODE mode);
	OCCLUSION_MODE getOcclusion();
	void debug();
	ofFbo* getFbo();
	ofFbo* getPickingFbo();
	ofFbo* getPostProcessTextureFbo();
	ofCustomCamera* getCamera();
	void applyPostProcess();
	void setTonemapUniforms(std::map<std::string, float>);
	std::map<std::string, float> getTonemapUniforms();
	void setTonemapType(TONEMAP_TYPE type);
	TONEMAP_TYPE getTonemapType();
	void setLightModel(LIGHTMODEL_TYPE type);
	int getLightModel();
	ofShader* getLightShader();


};
