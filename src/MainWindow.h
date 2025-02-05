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
    ofCamera cameraMain;
    ofCamera cameraSecond;
    ofCamera cameraThird;

    void fboDraw(ofCamera& camera, const ofFbo& fbo);

    // This light is just temporary
    ofLight light;
    ofMaterial material;


public:

    void setup() override;
    void draw() override;
    void exit() override;
    void keyPressed(ofKeyEventArgs &key) override;

};


