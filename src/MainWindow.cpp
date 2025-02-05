/*****************************************************
 * TP IFT3100H24 - Knight Maker
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

 ofSetWindowTitle("Knight Maker");

 Global::setup();
 ui.setup();

 cameraMain.setPosition(0, 0, 50);
 cameraSecond.setPosition(0, 50, 0);
 cameraSecond.lookAt(glm::vec3(0,0,0));
 cameraThird.setPosition(50, 0, 0);
 cameraThird.lookAt(glm::vec3(0,0,0));

 // To be removed
 ofEnableDepthTest();  // Enable depth for 3D rendering
 light.setup();
 light.setPosition(100, 200, 100);  // Set light position
 material.setShininess(100);  // Controls specular reflection
 material.setSpecularColor(ofColor(255, 255, 255));  // Highlights

}


/**
 * Main draw function
 */
void MainWindow::draw() {

 ofBackground(0);

 // We render three times
 fboDraw(cameraMain, Global::m_fboCameraMain);
 fboDraw(cameraSecond, Global::m_fboCameraSecond);
 fboDraw(cameraThird, Global::m_fboCameraThird);

 ui.draw();

}


/**
* Draw to texture (FBO)
*/
void MainWindow::fboDraw(ofCamera& camera, const ofFbo& fbo) {

 fbo.begin();
 camera.begin();
 ofBackground(0);
 ofEnableLighting();
 light.enable();
 material.begin();
 ofSetColor(255); // Ensure color is white to see lighting effects

 Global::level.draw();

 material.end();
 light.disable();
 ofDisableLighting();
 camera.end();
 fbo.end();

}


/**
 * Handle key presses
 */
void MainWindow::keyPressed(ofKeyEventArgs &key) {

 if (key.key == 'w') {
  cameraMain.setPosition(cameraMain.getPosition() + glm::vec3(0, 0, -10)); // Move camera forward
 }

 if (key.key == 's') {
  cameraMain.setPosition(cameraMain.getPosition() + glm::vec3(0, 0, 10));  // Move camera backward
 }

}


/**
 * Called when the application is about to exit
 */
void MainWindow::exit() {
 // Do nothing for now
}

