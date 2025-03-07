/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * All tooltip messages should be defined here, so we don't have to chase them all over the place.
 *
 *****************************************************/

#pragma once

struct TooltipMessages {

	// Generic 
	const char* TODO = "Coming soon!";

	// BaseNode
	const char* node_display = "If ticked, the node is rendered to the screen. \nUntick to hide the node.";

	// ModelNode
	const char* node_playAnimation = "If ticked, the model will update their animation. \nWhen unticked, the animation stops updating \nleaving the character in its current pose.";
	const char* node_loopAnimation = "If ticked, the model will play the currently \nassigned animation on a loop. \nMake sure 'Play' is ticked if you want it to play. \n\nTODO: refactor this to a button and make it work! :)";
	const char* node_showAllAnimation = "If ticked, the list above will show all available animations \nfor the character, even those that are not looping.";

	//Camera options
	const char* camera_orthoZoom = "Orthographic zoom factor";
	const char* camera_FOVDeg = "Field of view (in degrees)";
	const char* camera_nearClip = "Near clipping plane distance";
	const char* camera_farClip = "Far clipping plane distance";
	const char* camera_reset = "Reset the initial value of this viewport's camera. \nThis will also reset the position.";

	// Tool bar buttons
	const char* toolbar_new = "New level \n(not implemented)";
	const char* toolbar_load = "Load level \n(not implemented)";
	const char* toolbar_save = "Save level \n(not implemented)";
	const char* toolbar_generate = "Generate a triptych image with the three viewports";
	const char* toolbar_toggleCam = "Toggle between 3 viewports and 1 viewport";
	const char* toolbar_histogram = "Color histogram tool";
	const char* toolbar_sequence_start = "Start recording";
	const char* toolbar_sequence_stop = "Stop recording";

	// Level buttons
	const char* level_addNode = "This will allow you to add a new node to the level. \n\n-> If you have a node selected, it will add the new node as a child; \nso to add a new parent node, make sure to deselect all nodes.";
	const char* level_delete = "Delete the selected node. \nThere will be a prompt to confirm.";
	const char* level_up = "Move the node up in the list.";
	const char* level_down = "Move the node down in the list.";
};

