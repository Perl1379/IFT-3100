/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * MainWindow class implementation
 *
 *****************************************************/
#include "MainWindow.h"
#include "Global.h"


 // Declare GUI elements

 /**
  * Main window setup (title, menu and various visual elements)
  */
void MainWindow::setup() {

	ofSetEscapeQuitsApp(false);  // Disable ESC quitting

	ofSetWindowTitle("Adventure Party Maker");
	ofSetVerticalSync(true);

	m_ui.setup();
	Global::setup();
	ofSetGlobalAmbientColor(Global::m_ambientLightColor);

	// To be removed
	ofEnableDepthTest();  // Enable depth for 3D rendering

}


/**
 * Main draw function
 */
void MainWindow::draw() {

	// Reset render stats
	for (int i = 0;i < 3;i++) {
		Global::m_countNodeRender[i] = 0;
	}

	// Update lights
	for (int i=0;i<8;i++) {
		Global::m_lights[i].update();
	}

	// We render three times
	for (int i = 0; i < 3; i++) {

		cameraDraw(i);
		if (m_ui.onlyOneCamera()) break;
	}

	m_ui.draw();

}


/**
* Draw a specific camera to a FBO texture
*/
void MainWindow::cameraDraw(int index) {

	auto fbo = Global::m_cameras[index].getFbo();
	Global::m_cameras[index].update();
	auto camera = Global::m_cameras[index].getCamera();
	Global::m_cameras[index].resizeTextureIfNeeded();

	fbo->begin();


	camera->begin();
	ofBackground(64);

	// We render skybox first
	Global::m_skybox.draw(camera->getPosition());

	ofShader* m_shaderLight = Global::m_cameras[index].getLightShader();
	if (m_shaderLight == nullptr) {
		ofEnableLighting();
	} else {

		m_shaderLight->begin();

		int lightTypes[8];
		glm::vec3 lightPositions[8];
		glm::vec3 lightOrientations[8];
		float lightAttenuations[8];
		glm::vec3 lightAmbientColors[8];
		glm::vec3 lightDiffuseColors[8];
		glm::vec3 lightSpecularColors[8];

		ofMatrix4x4 modelView = camera->getModelViewMatrix();

		// Pass light information
		int count = 0;
		for (int i = 0; i < 8; i++) {
		 	LightSource* light = &Global::m_lights[i];
		 	if (!light->getEnabled()) {
		 		continue;
		 	}

		 	lightTypes[i] = light->getLightType();
		 	lightPositions[i] =  light->getPosition() * modelView;


			ofVec3f euler = light->getOrientation();
			ofQuaternion q;
			q.makeRotate(euler.x, ofVec3f(1, 0, 0), euler.y, ofVec3f(0, 1, 0), euler.z, ofVec3f(0, 0, 1));
			ofVec3f direction = q * ofVec3f(0, 0, -1);
			direction.normalize();


		 	lightOrientations[i] = modelView.getRotate() * direction;


		 	lightAttenuations[i] = light->getAttenuation();

		 	ofFloatColor colorAmbient = light->getColorAmbient();
		 	ofFloatColor colorDiffuse = light->getColorDiffuse();
		 	ofFloatColor colorSpecular = light->getColorSpecular();

			lightAmbientColors[i] = glm::vec3(colorAmbient.r, colorAmbient.g, colorAmbient.b);
			lightDiffuseColors[i] = glm::vec3(colorDiffuse.r, colorDiffuse.g, colorDiffuse.b);
			lightSpecularColors[i] = glm::vec3(colorSpecular.r, colorSpecular.g, colorSpecular.b);

		 	count++;
		 }

		m_shaderLight->setUniform1iv("light_type", (GLint*)&lightTypes[0], 8);
		m_shaderLight->setUniform3fv("light_position", (GLfloat*)&lightPositions[0], 8);
		m_shaderLight->setUniform3fv("light_orientation", (GLfloat*)&lightOrientations[0], 8);
		m_shaderLight->setUniform1fv("light_attenuation", (GLfloat*)&lightAttenuations[0], 8);
		m_shaderLight->setUniform3fv("light_color_ambient", (GLfloat*)&lightAmbientColors[0], 8);
		m_shaderLight->setUniform3fv("light_color_diffuse", (GLfloat*)&lightDiffuseColors[0], 8);
		m_shaderLight->setUniform3fv("light_color_specular", (GLfloat*)&lightSpecularColors[0], 8);

		m_shaderLight->setUniform1i("light_sources", count);
		m_shaderLight->setUniform3f("global_ambient_color", Global::m_ambientLightColor.r, Global::m_ambientLightColor.g, Global::m_ambientLightColor.b);
	}

	//ofSetColor(255);

	Global::m_countNodeRender[index] = Global::m_level.draw(false, &Global::m_cameras[index]);
	Global::m_transformTools.draw(false);

	if (m_shaderLight == nullptr) {
		ofDisableLighting();
	} else {
		m_shaderLight->end();
	}

	camera->end();
	fbo->end();
	if (Global::m_cameras[index].getTonemapType() != NO_TONEMAP) {
		Global::m_cameras[index].applyPostProcess();
	}

	// Generate Object picking FBO only for hovered camera viewport
	if (Global::m_doColorPicking) {
		if (getCurrentCameraIndex() == index) {
			auto fboPicking = Global::m_cameras[index].getPickingFbo();
			fboPicking->begin();
			camera->begin();
			ofBackground(0);
			Global::m_level.draw(true, &Global::m_cameras[index]);
			Global::m_transformTools.draw(true);
			camera->end();
			fboPicking->end();
		}
	}

}





/**
 * Callback function for handling key pressed events
 */
void MainWindow::keyPressed(ofKeyEventArgs& key) {


	int index = getCurrentCameraIndex();
	if (index == -1) {
		m_cameraMovement.set(0, 0, 0);
		return;
	}

	if (!key.hasModifier(OF_KEY_CONTROL))
		handleCameraInput(true, key, index);

}


/**
 * Callback function for handling key released events
 */
void MainWindow::keyReleased(ofKeyEventArgs& key) {
	if (!key.hasModifier(OF_KEY_CONTROL))
	{
		int index = getCurrentCameraIndex();
		if (index == -1) {
			resetCameraMovement();
			return;
		}

		handleCameraInput(false, key, index);
	}
	else {
		// Handle history

		if (key.keycode == 'z' || key.keycode == 'Z') {
			Global::m_actions.undo();
		}

		if (key.keycode == 'r' || key.keycode == 'R') {
			Global::m_actions.redo();
		}

	}


}


/**
 * Reset camera movement
 */
void MainWindow::resetCameraMovement() {
	m_cameraMovement.set(0, 0, 0);
	m_cameraRotation = 0.0;
}

/**
 * Handle key presses for camera control
 */
void MainWindow::handleCameraInput(bool pressed, ofKeyEventArgs& key, int index) {


	if (!pressed) {

		// Handle reset
		if (key.key == OF_KEY_HOME) {
			Global::m_cameras[index].reset();
			resetCameraMovement();
			return;
		}

		// Print debug information
		if (key.keycode  == 'P') {
			Global::m_cameras[index].debug();
		}

		// Toggle ortho projection
		if (key.keycode == 'O') {
			if (Global::m_cameras[index].getCamera()->getOrtho()) {
				Global::m_cameras[index].getCamera()->disableOrtho();
			}
			else {
				Global::m_cameras[index].getCamera()->enableOrtho();

			}

		}

		// Swap cameras
		if (key.key == OF_KEY_INSERT) {
			if (index != 0) {

				// Retrieve position and orientation of main camera
				glm::vec3 firstPosition = Global::m_cameras[0].getCamera()->getPosition();
				glm::vec3 firstDirection = Global::m_cameras[0].getCamera()->getLookAtDir();
				bool firstOrtho = Global::m_cameras[0].getCamera()->getOrtho();

				// Retrieve position of current camera
				glm::vec3 currentPosition = Global::m_cameras[index].getCamera()->getPosition();
				glm::vec3 currentDirection = Global::m_cameras[index].getCamera()->getLookAtDir();
				bool currentOrtho = Global::m_cameras[index].getCamera()->getOrtho();

				// Set main camera to current camera
				Global::m_cameras[index].getCamera()->setPosition(firstPosition);
				Global::m_cameras[index].getCamera()->lookAt(firstDirection);
				if (firstOrtho) {
					Global::m_cameras[index].getCamera()->enableOrtho();
				}
				else {
					Global::m_cameras[index].getCamera()->disableOrtho();
				}

				// Set current camera to main
				Global::m_cameras[0].getCamera()->setPosition(currentPosition);
				Global::m_cameras[0].getCamera()->lookAt(currentDirection);
				if (currentOrtho) {
					Global::m_cameras[0].getCamera()->enableOrtho();
				}
				else {
					Global::m_cameras[0].getCamera()->disableOrtho();
				}

				ImGui::SetWindowFocus("Main Camera");

			}
			return;
		}
	}

	// Handle rotation along forward vector
	if (key.keycode == 'Q' || key.keycode == 'E') {
		if (!pressed) {
			m_cameraRotation = 0.0;
			return;
		}
		m_cameraRotation = (key.keycode == 'Q' ? 1.0f : -1.0f);
	}

	// Handle longitudinal movements
	if (key.keycode == 'W' || key.keycode == 'S') {

		if (!pressed) {
			m_cameraMovement.z = 0;
			return;
		}

		m_cameraMovement.z = (key.keycode == 'W' ? -1.0f : 1.0f);
		return;
	}

	// Handle lateral movements
	if (key.keycode == 'A' || key.keycode == 'D') {

		if (!pressed) {
			m_cameraMovement.x = 0;
			return;
		}

		m_cameraMovement.x = (key.keycode == 'A' ? -1.0f : 1.0f);
		return;
	}

	// Handle vertical movements
	if (key.keycode == ' ' || key.keycode == 'Z') {

		if (!pressed) {
			m_cameraMovement.y = 0;
			return;
		}

		m_cameraMovement.y = (key.keycode == ' ' ? 1.0f : -1.0f);
	}

}


/**
 * Update function, called as often as draw
 */
void MainWindow::update() {

	// Calculate delta
	float currentTime = ofGetElapsedTimef();
	float deltaTime = currentTime - m_lastUpdateTime;
	m_lastUpdateTime = currentTime;

	int index = getCurrentCameraIndex();
	if (index == -1) return;
	updateCamera(index, deltaTime);
	Global::m_transformTools.setCameraIndex(index);

	// Record main camera
	if (Global::m_sequenceCount != -1) {
		Global::m_sequenceTotalDelta += deltaTime;
		if (Global::m_sequenceTotalDelta >= Global::m_sequenceInterval) {
			Global::m_sequenceTotalDelta -= Global::m_sequenceInterval;
			ofPixels pixels;
			Global::m_cameras[0].getFbo()->readToPixels(pixels);
			ofSaveImage(pixels,	"output/" + Global::m_sequenceName + "/" + std::to_string(Global::m_sequenceCount) + ".png");
			Global::m_sequenceCount++;
			if (Global::m_sequenceCount == 60) {
				Global::m_sequenceCount = -1;
			}
		}
	}

}


/**
 * Update camera (movements)
 */
void MainWindow::updateCamera(int index, float deltaTime) {

	float cameraMoveSpeed = 800.0f;
	float cameraRotationSpeed = 100.0f;
	float cameraOrthoZoomSpeed = 1.0f;

	auto camera = Global::m_cameras[index].getCamera();

	// Allow only if not in ortho mode
	if (!camera->getOrtho()) {
		camera->dolly(m_cameraMovement.z * cameraMoveSpeed * deltaTime);  // Move forward/backward
	}
	else {
		// Set zoom
		camera->setOrthoZoom(camera->getOrthoZoom() - (m_cameraMovement.z * cameraOrthoZoomSpeed * deltaTime));
	}

	camera->truck(m_cameraMovement.x * cameraMoveSpeed * deltaTime);  // Move left/right
	camera->boom(m_cameraMovement.y * cameraMoveSpeed * deltaTime);   // Move up/down
	camera->rollDeg(m_cameraRotation * cameraRotationSpeed * deltaTime);  // Rotate along forward vector

}


/**
 * Get the currenty selected viewport camera
 */
int MainWindow::getCurrentCameraIndex() {


	std::string	windowName = m_ui.getHoveredWindow();

	int index = -1;

	if (windowName == "Main Camera") {
		index = 0;
	}
	else if (windowName == "Second Camera") {
		index = 1;
	}
	else if (windowName == "Third Camera") {
		index = 2;
	}
	return index;
}


/**
 * Called when the application is about to exit
 */
void MainWindow::exit() {
	// Do nothing for now
}



/**
 * Callback function for handling mouse pressed events
 */
void MainWindow::mousePressed(int x, int y, int button) {

	if (button == OF_MOUSE_BUTTON_MIDDLE) {
		m_isMiddleMousePressed = true;
		m_lastMousePosition.set(x, y);
		int index = getCurrentCameraIndex();
		if (index == -1) return;
		Global::m_cameras[index].setUpVector(Global::m_cameras[index].getCamera()->getUpDir());

	}

	if (button == OF_MOUSE_BUTTON_RIGHT) {
		m_isRightMousePressed = true;
		m_lastMousePosition.set(x, y);
		int index = getCurrentCameraIndex();
		if (index == -1) return;
		Global::m_cameras[index].setUpVector(Global::m_cameras[index].getCamera()->getUpDir());

	}

}


/**
 * Callback function for handling mouse released events
 */
void MainWindow::mouseReleased(int x, int y, int button) {

	if (button == OF_MOUSE_BUTTON_MIDDLE) {
		m_isMiddleMousePressed = false;
		int index = getCurrentCameraIndex();
		if (index == -1) return;
		Global::m_cameras[index].setUpVector(Global::m_cameras[index].getCamera()->getUpDir());
	}

	if (button == OF_MOUSE_BUTTON_RIGHT) {
		m_isRightMousePressed = false;
		int index = getCurrentCameraIndex();
		if (index == -1) return;
		Global::m_cameras[index].setUpVector(Global::m_cameras[index].getCamera()->getUpDir());
	}
}


/**
 * Callback function for handling mouse dragged events
 */
void MainWindow::mouseDragged(int x, int y, int button) {

	int index = getCurrentCameraIndex();
	if (index == -1) return;
	if (m_isMiddleMousePressed && button == OF_MOUSE_BUTTON_MIDDLE) {


		auto mx = static_cast<float>(x);
		auto my = static_cast<float>(y);
		float sensitivity = 0.2f;
		float deltaX = mx - m_lastMousePosition.x;
		float deltaY = my - m_lastMousePosition.y;
		ofCamera* camera = Global::m_cameras[index].getCamera();
		float xdiff = -deltaX * sensitivity;
		float ydiff = -deltaY * sensitivity;

		ofVec3f rightVector = camera->getSideDir();
		float maxPitch = 85.0f;
		float currentPitch = glm::degrees(asin(camera->getLookAtDir().y));
		if ((currentPitch + ydiff) > maxPitch) {
			ydiff = maxPitch - currentPitch;
		} else if ((currentPitch + ydiff) < -maxPitch) {
			ydiff = -maxPitch - currentPitch;
		}

		camera->rotateDeg(ydiff, rightVector);
		camera->rotateDeg(xdiff, {0, 1, 0});

		m_lastMousePosition.set(mx, my);

	}

	if (m_isRightMousePressed && button == OF_MOUSE_BUTTON_RIGHT) {
		if (Global::m_selectedNode >= 2) {
			auto mx = static_cast<float>(x);
			auto my = static_cast<float>(y);

			float sensitivity = 0.2f; // Rotation speed

			float deltaX = mx - m_lastMousePosition.x;
			float deltaY = my - m_lastMousePosition.y;

			BaseNode* node = Global::m_level.getTree()->findNode(Global::m_selectedNode);
			ofCamera* camera = Global::m_cameras[index].getCamera();
			float xdiff = -deltaX * sensitivity;
			float ydiff = -deltaY * sensitivity;

			// Get camera current position relative to the node
			ofVec3f camPos = camera->getPosition();
			ofVec3f nodePos = node->getTransform().getGlobalPosition();
			ofVec3f camOffset = camPos - nodePos; // Vector from node to camera

			// Convert offset to spherical coordinates (radius, yaw, pitch)
			float radius = camOffset.length();
			float yaw = atan2(camOffset.z, camOffset.x);
			float pitch = asin(camOffset.y / radius);

			// Apply rotation
			yaw += ofDegToRad(xdiff);
			pitch += ofDegToRad(ydiff);

			// Clamp to avoid flipping
			float pitchLimit = ofDegToRad(85.0f);
			pitch = glm::clamp(pitch, -pitchLimit, pitchLimit);

			// Convert back to coordinates
			float newX = radius * cos(pitch) * cos(yaw);
			float newY = radius * sin(pitch);
			float newZ = radius * cos(pitch) * sin(yaw);

			camera->setPosition(nodePos + ofVec3f(newX, newY, newZ));
			camera->lookAt(nodePos);

			m_lastMousePosition.set(mx, my);
		}
	}
}


/**
 * Callback function for handling mouse scrolled events
 */
void MainWindow::mouseScrolled(ofMouseEventArgs& args) {

	int index = getCurrentCameraIndex();
	if (index == -1) return;

	float zoomSpeed = 50.0f;
	float cameraOrthoZoomSpeed = 1.0f;


	auto camera = Global::m_cameras[index].getCamera();

	// Allow only if not in ortho mode
	if (!camera->getOrtho()) {
		camera->dolly(-args.scrollY * zoomSpeed);
	}
	else {
		// Set zoom
		camera->setOrthoZoom(camera->getOrthoZoom() - (args.scrollY * cameraOrthoZoomSpeed));
	}


}