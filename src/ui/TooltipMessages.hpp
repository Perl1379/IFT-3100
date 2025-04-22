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
	const char * ambient_light_color = "Ambient light color";

	// BaseNode
	const char* node_display = "If ticked, the node is rendered to the screen. \nUntick to hide the node.";

	// Character, Asset, and Model Node
	const char* node_model = "Change the model's visual.";
	const char* node_modelTexture = "Change the model's texture.";
	const char* node_playAnimation = "If ticked, the model will update their animation. \nWhen unticked, the animation stops updating \nleaving the character in its current pose.";
	const char* node_showAllAnimation = "If ticked, the list above will show all \n available animations for the character.";

	// Spline
	const char* spline_pointIndex = "This control point's index in the spline.";

	//Camera options
	const char* camera_orthoZoom = "Orthographic zoom factor";
	const char* camera_FOVDeg = "Field of view (in degrees)";
	const char* camera_nearClip = "Near clipping plane distance";
	const char* camera_farClip = "Far clipping plane distance";
	const char* camera_reset = "Reset the initial value of this viewport's camera. \nThis will also reset the position.";
	const char* camera_lightmodel = "Select a light model for the camera";
	const char* camera_tonemap = "Define a tone map for the camera";

	// Tool bar buttons
	const char* toolbar_new = "New level";
	const char* toolbar_load = "Load level";
	const char* toolbar_save = "Save level";
	const char* toolbar_generate = "Generate a triptych image with the three viewports";
	const char* toolbar_toggleCam = "Toggle between 3 viewports and 1 viewport";
	const char* toolbar_raycast = "Toggle raycast-based object picking";
	const char* toolbar_histogram = "Color histogram tool";
	const char* toolbar_sequence_start = "Start recording";
	const char* toolbar_sequence_stop = "Stop recording";

	// Level buttons
	const char* level_addNode = "This will allow you to add a new node to the level. \n\n-> If you have a node selected, it will add the new node as a child; \nso to add a new parent node, make sure to deselect all nodes.";
	const char* level_delete = "Delete the selected node. \nThere will be a prompt to confirm.";
	const char* level_up = "Move the node up in the list.";
	const char* level_down = "Move the node down in the list.";

	// Material, Shaders
	const char* material_preset = "List of material presets (values and textures).";
	const char* material_applyPreset = "Apply the selected preset values to the material properties.\nBeware that this will override custom values.";
};

