/*****************************************************
* TP IFT3100H24 - 3D Scene Editor
 * by Team 12
 *****************************************************
 *
 * Application class definition
 *
 *****************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <ofBaseApp.h>
#include <ofxImGui.h>

/**
 * Application : The main application class
 */
class Application : public ofBaseApp {

    private:
        ofxImGui::Gui gui;

        void _draw_menu();
        void _draw_tree();
        void _draw_status();
        void _draw_properties();
        void _draw_viewport();

    public:
        void setup();
        void draw();
        void exit();


};



#endif //APPLICATION_H
