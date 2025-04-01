/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * Level class definition
 *
 *****************************************************/
#pragma once

#include "nodes/BaseNode.h"

class Level {

private:
	BaseNode* m_tree;

public:
	Level();

	BaseNode* getTree();

	void reset();
	int draw(bool p_objectPicking, Camera* p_camera);
	int findNodeByMousePosition(int cameraIndex, int x, int y, glm::vec2 viewportSize);

};

