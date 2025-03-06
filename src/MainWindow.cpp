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
	ofSetVerticalSync(false);

	Global::setup();
	m_ui.setup();

	// To be removed
	ofEnableDepthTest();  // Enable depth for 3D rendering
	m_light.setup();
	m_light.setPosition(0, 1000, 2000);  // Set light position

}


/**
 * Main draw function
 */
void MainWindow::draw() {

	ofBackground(0);

	// Reset render stats
	for (int i = 0;i < 3;i++) {
		Global::m_countNodeRender[i] = 0;
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
	ofBackground(0);

	// We render skybox first
	Global::m_skybox.draw(camera->getPosition());

	ofEnableLighting();
	m_light.enable();
	ofSetColor(255);
	Global::m_countNodeRender[index] = Global::m_level.draw(false, &Global::m_cameras[index]);
	Global::m_transformTools.draw(false);
	m_light.disable();
	ofDisableLighting();
	camera->end();
	fbo->end();

	// Generate Object picking FBO only for hovered camera viewport
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

		if (key.key == 'z' || key.key == 'Z') {
			Global::m_actions.undo();
		}

		if (key.key == 'r' || key.key == 'R') {
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
		if ((key.key == 'p') || (key.key == 'P')) {
			Global::m_cameras[index].debug();
		}

		// Toggle ortho projection
		if ((key.key == 'o') || (key.key == 'O')) {
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
	if ((key.key == 'q' || key.key == 'Q') || (key.key == 'e' || key.key == 'E')) {
		if (!pressed) {
			m_cameraRotation = 0.0;
			return;
		}
		m_cameraRotation = (key.key == 'q' ? 1.0f : -1.0f);
	}

	// Handle longitudinal movements
	if ((key.key == 'w' || key.key == 'W') || (key.key == 's' || key.key == 'S')) {

		if (!pressed) {
			m_cameraMovement.z = 0;
			return;
		}

		m_cameraMovement.z = ((key.key == 'w' || key.key == 'W') ? -1.0f : 1.0f);
		return;
	}

	// Handle lateral movements
	if ((key.key == 'a' || key.key == 'A') || (key.key == 'd' || key.key == 'D')) {

		if (!pressed) {
			m_cameraMovement.x = 0;
			return;
		}

		m_cameraMovement.x = ((key.key == 'a' || key.key == 'A') ? -1.0f : 1.0f);
		return;
	}

	// Handle vertical movements
	if (key.key == ' ' || key.key == 'z' || key.key == 'Z') {

		if (!pressed) {
			m_cameraMovement.y = 0;
			return;
		}

		m_cameraMovement.y = (key.key == ' ' ? 1.0f : -1.0f);
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

		float sensitivity = 0.2f; // Rotation speed

		float deltaX = mx - m_lastMousePosition.x;
		float deltaY = my - m_lastMousePosition.y;

		ofCamera* camera = Global::m_cameras[index].getCamera();
		float xdiff = -deltaX * sensitivity;
		float ydiff = -deltaY * sensitivity;

		ofVec3f upvec = Global::m_cameras[index].getUpVector();
		ofVec3f sidev = camera->getSideDir();

		camera->rotate(ydiff, sidev);
		camera->rotate(xdiff, upvec);

		m_lastMousePosition.set(mx, my);
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