/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * MainWindow class definition
 *
 *****************************************************/
#pragma once
#include <ofMain.h>
#include "ui/UserInterface.h"

class MainWindow : public ofBaseApp {

private:

	UserInterface ui;

	// This light is just temporary
	ofLight light;
	ofMaterial material;

	bool isMiddleMousePressed = false;
	ofVec3f cameraMovement;
	float cameraRotation = 0.0f;
	float lastUpdateTime = 0;
	ofVec2f lastMousePosition;

	void resetCameraMovement();
	void cameraDraw(int index);
	void handleCameraInput(bool pressed, ofKeyEventArgs& key, int index);
	void updateCamera(int index, float deltaTime);
	int getCurrentCameraIndex(bool hovered);

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


