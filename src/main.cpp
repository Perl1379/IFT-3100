/*****************************************************
 * TP IFT3100H24 - 3D Scene Editor
 * by Team 12
 *****************************************************
 *
 * Main entry point
 *
 *****************************************************/

#include <ofAppRunner.h>
#include <ofWindowSettings.h>
#include "application.h"

/**
 * Main entry point for the program
 */
int main() {

    ofGLWindowSettings settings;
    settings.setSize(1440, 900);
    settings.windowMode = OF_WINDOW;

    ofCreateWindow(settings);
    ofRunApp(new Application);

}