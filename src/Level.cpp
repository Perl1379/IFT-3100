/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * Level class definition
 *
 *****************************************************/
#include "Level.h"
#include <GroupNode.h>
#include <imgui.h>
#include <LightNode.h>
#include <TerrainNode.h>
#include "SphereNode.h"
#include "AssetNode.h"
#include "CharacterNode.h"

 /**
  * Constructor
  */
Level::Level() {

	m_tree = new BaseNode("Level");

}


/**
 * Draw node tree
 */
int Level::draw(bool objectPicking, Camera* p_camera) {

	m_tree->getTransform().transformGL();
	int count = m_tree->draw(objectPicking, p_camera);
	m_tree->getTransform().restoreTransformGL();
	return count;
}


/**
* Retrieve node tree (first node)
*/
BaseNode* Level::getTree() {
	return m_tree;
}



/**
 * Reset to a level with default values
 */
void test_spawn_sphere(BaseNode* tree, int sphere_count, float sphere_spacing, float z, int depth = 0) {

	for (int y = 0; y < sphere_count; y++) {
		for (int x = 0; x < sphere_count; x++) {
			SphereNode* node = new SphereNode("Sphere_" + std::to_string(x) + "_" + std::to_string(y));
			node->setProperty("Diffuse Color", ofFloatColor(1, 0, 0));
			float ox = -((float)sphere_count * sphere_spacing) / 4.0f;
			float oy = -((float)sphere_count * sphere_spacing) / 4.0f;
			tree->addChild(node);
			float xx = ox + ((float)x * sphere_spacing);
			float yy = oy + ((float)y * sphere_spacing);
			node->getTransform().setPosition(xx, yy, z);

			if (depth == 0) {
				node->setRadius(100.0f);
				test_spawn_sphere(node, 2, 150.0, 0, 1);
			}
			else {
				node->setRadius(50.0f);
			}
		}
	}
}


/**
 * Reset level
 */
void Level::reset() {

	m_tree->removeAllChildren();
	Global::m_selectedNode = -1;

	// Create two main groups (Objects, Lights)
	GroupNode* m_objects = new GroupNode("Objects");
	m_tree->addChild(m_objects);

	GroupNode* m_lights = new GroupNode("Lights");
	m_lights->setExpanded(false);
	m_tree->addChild(m_lights);

	Global::m_skybox.setup("lightsky");

	// //--- Group of 5 adventurers.
	// // The user can add the knight via the "Add Node" button (it's more insteresting to use if they are not addding a duplicate)
	// GroupNode* adventurer_group = new GroupNode("Adventurers");
	// m_objects->addChild(adventurer_group);
	//
	// CharacterNode* node_rogue = new CharacterNode("Rogue", "Rogue");
	// adventurer_group->addChild(node_rogue);
	// node_rogue->setProperty("Animation", 6);
	//
	// CharacterNode* node_barbarian = new CharacterNode("Barbarian", "Barbarian");
	// adventurer_group->addChild(node_barbarian);
	// node_barbarian->setPosition(-600, 0, 75);
	// node_barbarian->getTransform().setOrientation(glm::vec3(0, 25, 0));
	//
	// CharacterNode* node_mage = new CharacterNode("Mage", "Mage");
	// adventurer_group->addChild(node_mage);
	// node_mage->setPosition(-1200, 0, 200);
	// node_mage->getTransform().setOrientation(glm::vec3(0, 45, 0));
	// node_mage->setProperty("Animation", 7);
	//
	// CharacterNode* node_engineer = new CharacterNode("Engineer", "Engineer");
	// adventurer_group->addChild(node_engineer);
	// node_engineer->setPosition(600, 0, 75);
	// node_engineer->getTransform().setOrientation(glm::vec3(0, -25, 0));
	//
	// CharacterNode* node_druid = new CharacterNode("Druid", "Druid");
	// adventurer_group->addChild(node_druid);
	// node_druid->setPosition(1200, 0, 200);
	// node_druid->getTransform().setOrientation(glm::vec3(0, -45, 0));
	// node_druid->setProperty("Animation", 0);
	//
	// //--- Some assets
	// GroupNode* loot_group = new GroupNode("Loot");
	// m_objects->addChild(loot_group);
	//
	// AssetNode* chest_node = new AssetNode("Crate", "ammo_crate_withLid");
	// loot_group->addChild(chest_node);
	// chest_node->setPosition(-600, 0, -700);
	// chest_node->getTransform().setOrientation(glm::vec3(0, 5, 0));
	//
	// AssetNode* potion_node = new AssetNode("Large blue potion", "potion_large_blue");
	// loot_group->addChild(potion_node);
	// potion_node->setPosition(1100, 425, -700);
	//
	// //--- A pine tree made of primitives
	// GroupNode* tree_group = new GroupNode("Pine Tree");
	// tree_group->getTransform().setPosition(300, 300, -1200);
	// m_objects->addChild(tree_group);
	//
	// CylinderNode* node_cylinder = new CylinderNode("Trunk");
	// tree_group->addChild(node_cylinder);
	// node_cylinder->getTransform().setScale(3, 4, 3);
	// node_cylinder->setProperty("Diffuse Color", ofFloatColor(0.5, 0.31, 0.07));
	//
	// ConeNode* node_cone = new ConeNode("Foliage");
	// tree_group->addChild(node_cone);
	// node_cone->getTransform().rotateDeg(180.0, glm::vec3(0, 0, 1));
	// node_cone->getTransform().setPosition(0, 600, 0);
	// node_cone->getTransform().setScale(10, 7, 10);
	// node_cone->setProperty("Diffuse Color", ofFloatColor(0.08, 0.28, 0.20));
	//
	// //--- Ground and water
	// TerrainNode* terrain = new TerrainNode("Terrain");
	// terrain->getTransform().setPosition(0, 300, 0);
	// terrain->getTransform().setScale(2.0, 1.0, 2.0);
	// terrain->setTerrainName("plains_with_mountains");
	// terrain->loadTerrain();
	// m_objects->addChild(terrain);
	// terrain->setProperty("Diffuse Color", ofFloatColor(0.78, 0.53, 0.36));
	//
	// PlaneNode* plane = new PlaneNode("Water");
	// plane->getTransform().setPosition(0, -50, 0);
	// plane->getTransform().setOrientation(glm::vec3(-90, 0, 0));
	// plane->getTransform().setScale(2.0, 2.0, 1.0);
	// plane->setWidth(5000);
	// plane->setHeight(5000);
	// plane->getMaterial().setDiffuseColor(ofFloatColor(0.27, 0.73, 1.0));
	// m_objects->addChild(plane);
	//
	// //--- Spline
	// SplineNode* spline = new SplineNode("Spline");
	// spline->init();
	// spline->getTransform().setPosition(glm::vec3(0.0, 50.0, 800.0));
	// spline->getMaterial().setDiffuseColor(ofFloatColor(0.0, 0.0, 1.0));
	// m_objects->addChild(spline);


	// Add light sources
	for (int i=0;i<8;i++) {
		LightNode* light = new LightNode("Light #" + std::to_string(i+1), i);
		light->setUseMaterial(false);
		light->getTransform().setPosition(Global::m_lights[i].getPosition());
		m_lights->addChild(light);
	}

	// //--- Group node of spheres. This showcases the "Display" feature
	// GroupNode* node = new GroupNode("Group");
	// node->getTransform().setPosition(0, 0, 0);
	// m_tree->addChild(node);
	//
	// int sphere_count = 1;
	// float sphere_spacing = 320.0f;
	// for (int z = 0; z < 1; z++) {
	// 	test_spawn_sphere(node, sphere_count, sphere_spacing, z * sphere_spacing, 0);
	// }
	// node->setDisplayNode(false);


}


/**
 * Intersect test using a sphere
 */
float intersectsSphere(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const glm::vec3& sphereCenter, float sphereRadius) {
	glm::vec3 oc = rayOrigin - sphereCenter;
	float a = glm::dot(rayDir, rayDir);
	float b = 2.0f * glm::dot(oc, rayDir);
	float c = glm::dot(oc, oc) - sphereRadius * sphereRadius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		return -1.0f;
	}

	float sd = glm::sqrt(discriminant);
	float test1 = (-b - sd) / (2.0f * a);
	float test2 = (-b + sd) / (2.0f * a);

	if (test1 > 0) return test1;
	if (test2 > 0) return test2;

	return -1.0f;
}


/**
 * Find a node from a mouse position
 */
int Level::findNodeByMousePosition(int cameraIndex, int x, int y, glm::vec2 viewportSize) {


	ofCustomCamera* cam = Global::m_cameras[cameraIndex].getCamera();

	float nx = (x / (float)viewportSize.x) * 2.0f - 1.0f;
	float ny = 1.0f - (y / (float)viewportSize.y) * 2.0f;  // Flip Y-axis

	float aspectRatio = (float)viewportSize.x / (float)viewportSize.y;

	float fovY = glm::radians(cam->getFov());
	float fovX = 2.0f * atan(tan(fovY / 2.0f) * aspectRatio);
	nx *= tan(fovX / 2.0f);

	glm::mat4 projMatrix = cam->getProjectionMatrix();
	glm::mat4 viewMatrix = cam->getModelViewMatrix();
	glm::mat4 invViewProj = glm::inverse(projMatrix * viewMatrix);

	glm::vec4 nearPoint;
	glm::vec4 farPoint;

	if (cam->getOrtho()) {
		nearPoint = invViewProj * glm::vec4(nx, ny, 0.0, 1.0);
		farPoint  = invViewProj * glm::vec4(nx, ny, 1.0, 1.0);
	} else {
		nearPoint = invViewProj * glm::vec4(nx, ny, -1.0, 1.0);
		farPoint  = invViewProj * glm::vec4(nx, ny, 1.0, 1.0);
	}

	glm::vec3 rayStart = glm::vec3(nearPoint) / nearPoint.w;
	glm::vec3 rayEnd   = glm::vec3(farPoint) / farPoint.w;
	glm::vec3 rayDir   = glm::normalize(rayEnd - rayStart);


	vector<BaseNode*> nodesToCheck;
	for (BaseNode* subNode : m_tree->getChildren()[0]->getChildren()) {
		nodesToCheck.push_back(subNode);
	}

	vector<std::pair<int, BaseNode*>> nodesFound;
	for (size_t i=0;i<nodesToCheck.size();i++) {

		for (BaseNode* subNode : nodesToCheck[i]->getChildren()) {
			nodesToCheck.push_back(subNode);
		}
		if (nodesToCheck[i]->getClassName() == "GroupNode") continue;
		if ((nodesToCheck[i]->getClassName() == "TerrainNode") && (nodesToCheck.size() > 1)) continue;

		ofVec3f pos = nodesToCheck[i]->getTransform().getGlobalPosition();
		ofVec3f bound = nodesToCheck[i]->getBoundingBox() * nodesToCheck[i]->getTransform().getGlobalScale();
		float radius = bound.length() / 2.0;
		float distance = intersectsSphere(rayStart, rayDir, pos, radius);
		if (distance > 0) {

			//ofLog() << "Node:" << nodesToCheck[i]->getName() << ", Distance:" << distance;
			nodesFound.push_back({distance, nodesToCheck[i]});

		}
	}

	if (nodesFound.size() > 0) {

		int selectedNode = nodesFound[0].second->getId();
		int minDistance = nodesFound[0].first;

		if (nodesFound.size() > 1) {
			for (size_t i=1;i<nodesFound.size();i++) {
				int distance = nodesFound[i].first;
				if (distance < minDistance) {
					selectedNode = nodesFound[i].second->getId();
					minDistance = distance;
				}
			}
		}
		return selectedNode;
	}

	return 0;
}
