/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * Camera class implementation
 *
 *****************************************************/
#include "Camera.h"

#include <Global.h>
#include <ofMatrix4x4.h>
#include <ofGraphics.h>


/**
 * Extract frustum planes
 */
std::array<Camera::Plane, 6> Camera::extractFrustumPlanes(const glm::mat4& m) {
	std::array<Plane, 6> planes;

	// Left Plane
	planes[0].normal = glm::vec3(m[0][3] + m[0][0], m[1][3] + m[1][0], m[2][3] + m[2][0]);
	planes[0].d = m[3][3] + m[3][0];

	// Right Plane
	planes[1].normal = glm::vec3(m[0][3] - m[0][0], m[1][3] - m[1][0], m[2][3] - m[2][0]);
	planes[1].d = m[3][3] - m[3][0];

	// Bottom Plane
	planes[2].normal = glm::vec3(m[0][3] + m[0][1], m[1][3] + m[1][1], m[2][3] + m[2][1]);
	planes[2].d = m[3][3] + m[3][1];

	// Top Plane
	planes[3].normal = glm::vec3(m[0][3] - m[0][1], m[1][3] - m[1][1], m[2][3] - m[2][1]);
	planes[3].d = m[3][3] - m[3][1];

	// Near Plane
	planes[4].normal = glm::vec3(m[0][3] + m[0][2], m[1][3] + m[1][2], m[2][3] + m[2][2]);
	planes[4].d = m[3][3] + m[3][2];

	// Far Plane
	planes[5].normal = glm::vec3(m[0][3] - m[0][2], m[1][3] - m[1][2], m[2][3] - m[2][2]);
	planes[5].d = m[3][3] - m[3][2];

	// Normalize all planes
	for (auto& plane : planes) {
		plane.normalize();
	}

	return planes;
}



/**
  * Setup camera with default values
  */
void Camera::setup(ofVec3f p_initialPosition, ofVec3f p_initialOrientation) {

	m_initialPosition = p_initialPosition;
	m_initialOrientation = p_initialOrientation;
	m_fboTexture.allocate(32, 32, GL_RGB);
	m_fboPickingTexture.allocate(32, 32, GL_RGB);
	m_fboPostProcessTexture.allocate(32, 32, GL_RGB);
	m_initialFOV = 70;
	m_initialzNear = 1.0f;
	m_initialzFar = 20000.0f;

	m_shaderTonemap = Global::m_shaders.getShader("tonemap_none");
	reset();
}


/**
* Update camera
*/
void Camera::update() {
	if (m_occlusion == NO_OCCLUSION) return;

	if (m_occlusion == FRUSTUM_CULLING) {
		glm::mat4 viewProjectionMatrix = m_camera.getProjectionMatrix() * m_camera.getModelViewMatrix();
		m_frustumPlanes = extractFrustumPlanes(viewProjectionMatrix);
	}
}


/**
 * Reset camera state
 */
void Camera::reset() {

	m_camera.setPosition(m_initialPosition);
	m_camera.lookAt(m_initialOrientation);
	m_camera.setFov(m_initialFOV);
	m_camera.setNearClip(m_initialzNear);
	m_camera.setFarClip(m_initialzFar);
	setLightModel(OPENGL_LIGHTS);
	setTonemapType(NO_TONEMAP);
}


/**
 * Display camera matrices and information
 */
void Camera::debug() {

	ofMatrix4x4 viewMatrix = inverse(m_camera.getGlobalTransformMatrix());
	ofMatrix4x4 modelMatrix = m_camera.getModelViewMatrix();
	ofMatrix4x4 projectionMatrix = m_camera.getProjectionMatrix();
	ofLog() << "Initial position: " << m_initialPosition.x << " " << m_initialPosition.y << " " << m_initialPosition.z;
	ofLog() << "Resolution: " << m_fboTexture.getWidth() << "," << m_fboTexture.getHeight();
	ofLog() << "FOV:" << m_camera.getFov();
	ofLog() << "Aspect Ratio:" << m_camera.getAspectRatio();
	ofLog() << "Force Aspect Ratio:" << m_camera.getForceAspectRatio();
	ofLog() << "ZNear:" << m_camera.getNearClip();
	ofLog() << "ZFar:" << m_camera.getFarClip();

	ofLog() << "==============================";
	ofLog() << "View Matrix (Camera's Transform):";
	for (int i = 0; i < 4; ++i) {
		ofLog() << "Row " << i + 1 << ": "
				<< std::setw(10) << viewMatrix(0, i) << " "
				<< std::setw(10) << viewMatrix(1, i) << " "
				<< std::setw(10) << viewMatrix(2, i) << " "
				<< std::setw(10) << viewMatrix(3, i);
	}

	ofLog() << "==============================";
	ofLog() << "Model-View Matrix (Model * View):";
	for (int i = 0; i < 4; ++i) {

		ofLog() << "Row " << i + 1 << ": "
				<< std::setw(10) << modelMatrix(0, i) << " "
				<< std::setw(10) << modelMatrix(1, i) << " "
				<< std::setw(10) << modelMatrix(2, i) << " "
				<< std::setw(10) << modelMatrix(3, i);
	}

	ofLog() << "==============================";
	ofLog() << "Projection Matrix (Camera Projection):";
	for (int i = 0; i < 4; ++i) {

		ofLog() << "Row " << i + 1 << ": "
				<< std::setw(10) << projectionMatrix(0, i) << " "
				<< std::setw(10) << projectionMatrix(1, i) << " "
				<< std::setw(10) << projectionMatrix(2, i) << " "
				<< std::setw(10) << projectionMatrix(3, i);
	}

	ofLog() << "==============================";

}


/**
 * Resize FBO texture to match viewport size
 */
void Camera::resizeTextureIfNeeded() {

	if (m_viewportWidth == 0) return;
	if (m_viewportHeight == 0) return;

	int tw = (int)m_fboTexture.getWidth();
	int th = (int)m_fboTexture.getHeight();
	if (m_viewportWidth != tw || m_viewportHeight != th) {
		m_fboTexture.allocate(m_viewportWidth, m_viewportHeight, GL_RGB);
		m_fboPickingTexture.allocate(m_viewportWidth, m_viewportHeight, GL_RGB);
		m_fboPostProcessTexture.allocate(m_viewportWidth, m_viewportHeight, GL_RGB);

		m_meshPostProcess.clear();
		// First triangle
		m_meshPostProcess.addVertex(ofPoint(0, 0));
		m_meshPostProcess.addTexCoord(ofVec2f(0.0, 0.0));

		m_meshPostProcess.addVertex(ofPoint(m_viewportWidth, 0));
		m_meshPostProcess.addTexCoord(ofVec2f(1.0, 0.0));

		m_meshPostProcess.addVertex(ofPoint(m_viewportWidth, m_viewportHeight));
		m_meshPostProcess.addTexCoord(ofVec2f(1.0, 1.0));

		// Second triangle
		m_meshPostProcess.addVertex(ofPoint(0, 0));
		m_meshPostProcess.addTexCoord(ofVec2f(0.0, 0.0));

		m_meshPostProcess.addVertex(ofPoint(m_viewportWidth, m_viewportHeight));
		m_meshPostProcess.addTexCoord(ofVec2f(1.0, 1.0));

		m_meshPostProcess.addVertex(ofPoint(0, m_viewportHeight));
		m_meshPostProcess.addTexCoord(ofVec2f(0.0, 1.0));

	}
}


/**
 * Set viewport size
 */
void Camera::setViewportSize(int width, int height) {
	m_viewportWidth = width;
	m_viewportHeight = height;
}


/**
 * Retrieve FBO texture
 */
ofFbo* Camera::getFbo() {
	return &m_fboTexture;
}


/**
 * Retrieve FBO texture (Object picking)
 */
ofFbo* Camera::getPickingFbo() {
	return &m_fboPickingTexture;
}

ofFbo* Camera::getPostProcessTextureFbo()
{
	//return &m_fboTexture;
	return &m_fboPostProcessTexture;
}


/**
 * Retrieve camera object
 */
ofCustomCamera* Camera::getCamera() {
	return &m_camera;
}


/**
 * Apply post processing effect (tonemapping)
 */
void Camera::applyPostProcess() {
	m_fboPostProcessTexture.begin();
	ofClear(0, 0, 0, 0);

	m_shaderTonemap->begin();
	m_shaderTonemap->setUniformTexture("tex0", m_fboTexture.getTexture(), 0);

	for (auto & m_tonemapUniform : m_tonemapUniforms) {
		m_shaderTonemap->setUniform1f(m_tonemapUniform.first, m_tonemapUniform.second);
	}

	m_meshPostProcess.draw();
	m_shaderTonemap->end();

	m_fboPostProcessTexture.end();
}


/**
 * Set occlusion mode
 */
void Camera::setOcclusion(OCCLUSION_MODE mode) {
	m_occlusion = mode;
}


/**
 * Get occlusion mode
 */
OCCLUSION_MODE Camera::getOcclusion() {
	return m_occlusion;
}


/**
 * Test visibility (for occlusion)
 */
bool Camera::testVisibility(const ofVec3f &p_position, const ofVec3f &p_boundingBox) {
	if (m_occlusion == NO_OCCLUSION) return true;

	switch(m_occlusion) {
		case FRUSTUM_CULLING: {
			return isInsideFrustum(p_position, p_boundingBox);
		}
		break;

	}

	return true;
}


/**
 * Check if bounding box is inside frustum
 */
bool Camera::isInsideFrustum(const ofVec3f& ofPosition, const ofVec3f& p_boundingBox) {

	glm::vec3 minBound = ofPosition - p_boundingBox;
	glm::vec3 maxBound = ofPosition + p_boundingBox;

	glm::vec3 corners[8] = {
		{minBound.x, minBound.y, minBound.z}, {maxBound.x, minBound.y, minBound.z},
		{minBound.x, maxBound.y, minBound.z}, {maxBound.x, maxBound.y, minBound.z},
		{minBound.x, minBound.y, maxBound.z}, {maxBound.x, minBound.y, maxBound.z},
		{minBound.x, maxBound.y, maxBound.z}, {maxBound.x, maxBound.y, maxBound.z}
	};

	// Check each plane
	for (const auto& plane : m_frustumPlanes) {
		int outsideCount = 0;

		// Check if all corners are outside this plane
		for (const auto& corner : corners) {
			if (glm::dot(plane.normal, corner) + plane.d < 0) {
				outsideCount++;
			}
		}

		// If all 8 corners are outside, the AABB is completely out of the frustum
		if (outsideCount == 8) {
			return false;
		}
	}

	// At least one corner is inside every frustum plane
	return true;
}


/**
 * Set tonemap uniforms
 */
void Camera::setTonemapUniforms(std::map<std::string, float> p_tonemapUniforms) {
	m_tonemapUniforms = p_tonemapUniforms;
}


/**
 * Get tonemap uniforms
 */
std::map<std::string, float> Camera::getTonemapUniforms() {
	return m_tonemapUniforms;
}


/**
 * Set tonemap type
 */
void Camera::setTonemapType(TONEMAP_TYPE p_type) {
	m_tonemapType = p_type;

	switch(p_type) {
		case NO_TONEMAP: {
			m_shaderTonemap = Global::m_shaders.getShader("tonemap_none");
		}
		break;

		case SEPIA: {
			ofLog() << "Sepia set";
			m_shaderTonemap = Global::m_shaders.getShader("tonemap_sepia");
		}

		break;
		case GRAYSCALE: {
			ofLog() << "fray set";
			m_shaderTonemap = Global::m_shaders.getShader("tonemap_grayscale");
		}
		break;
		
	}
}


/**
 * Get tonemap type
 */
TONEMAP_TYPE Camera::getTonemapType() {
	return m_tonemapType;
}


/**
 * Set light shader
 */
void Camera::setLightModel(LIGHTMODEL_TYPE p_model) {
	m_lightModel = p_model;

	switch(m_lightModel) {
		case OPENGL_LIGHTS: {
			m_shaderLight = nullptr;
		}
		break;

		case LAMBERT: {
			m_shaderLight = Global::m_shaders.getShader("lightmodel_lambert");
		}
		break;


		case GOURAUD: {
			m_shaderLight = Global::m_shaders.getShader("lightmodel_gouraud");
		}
		break;

		case PHONG: {
			m_shaderLight = Global::m_shaders.getShader("lightmodel_phong");
		}
		break;

		case BLINN_PHONG: {
			m_shaderLight = Global::m_shaders.getShader("lightmodel_blinnphong");
		}
		break;
	}

}


/**
 * Get light model
 */
int Camera::getLightModel() {
	return m_lightModel;
}


/**
* Get light shader
*/
ofShader* Camera::getLightShader() {
	return m_shaderLight;
}
