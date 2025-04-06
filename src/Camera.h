/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * Camera class definition
 *
 *****************************************************/
#pragma once
#include <ofCamera.h>
#include <ofCustomCamera.h>
#include <ofFbo.h>
#include <ofShader.h>


enum OCCLUSION_MODE {
	NO_OCCLUSION = 0,
	FRUSTUM_CULLING = 1
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
	std::array<Plane,6> m_frustumPlanes;

	ofVec3f m_upVector = ofVec3f(0,1,0);
	ofVec3f m_initialPosition;
	ofVec3f m_initialOrientation;
	float m_initialFOV;
	float m_initialzNear;
	float m_initialzFar;
	OCCLUSION_MODE m_occlusion = FRUSTUM_CULLING;

	ofFbo m_fboTexture;
	ofFbo m_fboPickingTexture;
	ofFbo m_fboPostProcessTexture;
	ofCustomCamera m_camera;
	int m_viewportWidth = 0;
	int m_viewportHeight = 0;
	std::array<Plane, 6> extractFrustumPlanes(const glm::mat4& m);
	ofShader m_shader;

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

	bool testVisibility(const ofVec3f &p_position, const ofVec3f &p_boundingBox);
	bool isInsideFrustum(const ofVec3f& ofPosition, const ofVec3f& p_boundingBox);
	void setOcclusion(OCCLUSION_MODE mode);
	OCCLUSION_MODE getOcclusion();
	void debug();
	ofFbo* getFbo();
	ofFbo* getPickingFbo();
	ofFbo* getPostProcessTextureFbo();
	ofCustomCamera* getCamera();
	void applyPostProcess();


};
