/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * MainWindow class definition
 *
 *****************************************************/
#pragma once
#include <ofMain.h>
#include "ui/UserInterface.h"
#include "ui/TransformTools.h"

class MainWindow : public ofBaseApp {

private:

	UserInterface m_ui;

	ofMaterial m_material;
	bool m_isMiddleMousePressed = false;
	bool m_isRightMousePressed = false;
	ofVec3f m_cameraMovement;
	float m_cameraRotation = 0.0f;
	float m_lastUpdateTime = 0;
	ofVec2f m_lastMousePosition;
	ofShader m_shader;
	void resetCameraMovement();
	void cameraDraw(int index);
	void handleCameraInput(bool pressed, ofKeyEventArgs& key, int index);
	void updateCamera(int index, float deltaTime);
	int getCurrentCameraIndex();

public:

	void setup() override;
	void draw() override;
	void update() override;
	void exit() override;
	void keyPressed(ofKeyEventArgs& key) override;
	void keyReleased(ofKeyEventArgs& key) override;
	void mousePressed(int x, int y, int button) override;
	void mouseReleased(int x, int y, int button) override;
	void mouseDragged(int x, int y, int button) override;
	void mouseScrolled(ofMouseEventArgs& args) override;
};


