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
#include <PlaneNode.h>
#include <TerrainNode.h>

#include "SphereNode.h"
#include "ModelNode.h"
#include "CylinderNode.h"
#include "ConeNode.h"
#include "XmlHandler.h"

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
 * Load level from file
 */
bool Level::loadFromFile(const std::string& filename)
{
	return false;
}


/**
 * Save level to file
 */
bool Level::saveToFile(const std::string& filename)
{
	XmlHandler* xmlHandler = XmlHandler::getInstance();
	xmlHandler->createNewFile(filename);
	int x = 0;
	for (Camera camera : Global::m_cameras) {
		auto position = camera.getCamera()->getPosition();
		auto orientation = camera.getCamera()->getGlobalOrientation();
		bool isOrtho = camera.getCamera()->getOrtho();
		if (x == 0) {
			xmlHandler->setFirstCameraPosition(position.x, position.y, position.z);
			xmlHandler->setFirstCameraOrientation(orientation.x, orientation.y, orientation.z);
			xmlHandler->setFirstCameraOrtho(isOrtho);
		}
		if (x == 1) {
			xmlHandler->setSecondCameraPosition(position.x, position.y, position.z);
			xmlHandler->setSecondCameraOrientation(orientation.x, orientation.y, orientation.z);
			xmlHandler->setSecondCameraOrtho(isOrtho);
		}
		if (x == 2) {
			xmlHandler->setThirdCameraPosition(position.x, position.y, position.z);
			xmlHandler->setThirdCameraOrientation(orientation.x, orientation.y, orientation.z);
			xmlHandler->setThirdCameraOrtho(isOrtho);
		}

		++x;
	}
	xmlHandler->setNodesProperties();
	xmlHandler->save();

	return true;
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


void test_print_modelNode_positions(ModelNode* p_node)
{
	ofLog() << p_node->getName() << " : " << p_node->getModel().getPosition().x << " : " << p_node->getModel().getPosition().y << " : " << p_node->getModel().getPosition().z;
	ofLog() << p_node->getName() << " : " << p_node->getTransform().getPosition().x << " : " << p_node->getTransform().getPosition().y << " : " << p_node->getTransform().getPosition().z;
}


/**
 * Reset level
 */
void Level::reset() {

	//--- Group of 5 adventurers. 
	// The user can add the knight via the "Add Node" button (it's more insteresting to use if they are not addding a duplicate)
	GroupNode* adventurer_group = new GroupNode("Adventurers");
	adventurer_group->getTransform().setOrientation(glm::vec3(0, 0, 0));
	m_tree->addChild(adventurer_group);

	ModelNode* node_rogue = new ModelNode("Rogue", "Kaykit/Characters/gltf/Rogue.glb");
	adventurer_group->addChild(node_rogue);
	node_rogue->setProperty("Animation", 11);

	ModelNode* node_barbarian = new ModelNode("Barbarian", "Kaykit/Characters/gltf/Barbarian.glb");
	adventurer_group->addChild(node_barbarian);
	node_barbarian->setPosition(-600, 0, -75);
	node_barbarian->getTransform().setOrientation(glm::vec3(0,25,0));

	ModelNode* node_mage = new ModelNode("Mage", "Kaykit/Characters/gltf/Mage.glb");
	adventurer_group->addChild(node_mage);
	node_mage->setPosition(-1200, 0, -200);
	node_mage->getTransform().setOrientation(glm::vec3(0, 45, 0));
	node_mage->setProperty("Animation", 13);

	ModelNode* node_engineer = new ModelNode("Engineer", "Kaykit/Characters/gltf/Engineer.glb");
	adventurer_group->addChild(node_engineer);
	node_engineer->setPosition(600, 0, -75);
	node_engineer->getTransform().setOrientation(glm::vec3(0, -25, 0));

	ModelNode* node_druid = new ModelNode("Druid", "Kaykit/Characters/gltf/Druid.glb");
	adventurer_group->addChild(node_druid);
	node_druid->setPosition(1200, 0, -200);
	node_druid->getTransform().setOrientation(glm::vec3(0, -45, 0));
	node_druid->setProperty("Animation", 0);

	//--- A pine tree made of primitives
	GroupNode* tree_group = new GroupNode("Pine Tree");
	tree_group->getTransform().setPosition(300, 300, -1200);
	m_tree->addChild(tree_group);

	CylinderNode* node_cylinder = new CylinderNode("Trunk");
	tree_group->addChild(node_cylinder);
	node_cylinder->getTransform().setScale(3,4,3);
	node_cylinder->setProperty("Diffuse Color", ofFloatColor(0.5, 0.31, 0.07));

	ConeNode* node_cone = new ConeNode("Foliage");
	tree_group->addChild(node_cone);
	node_cone->getTransform().rotateDeg(180.0,glm::vec3(0,0,1));
	node_cone->getTransform().setPosition(0, 600, 0);
	node_cone->getTransform().setScale(10, 7, 10);
	node_cone->setProperty("Diffuse Color", ofFloatColor(0.08, 0.28, 0.20));

	//--- Ground and water
	TerrainNode* terrain = new TerrainNode("Terrain");
	terrain->getTransform().setPosition(0, 300, 0);
	terrain->getTransform().setScale(2.0, 1.0, 2.0);
	terrain->setTerrainName("plains_with_mountains");
	terrain->loadTerrain();
	m_tree->addChild(terrain);
	terrain->setProperty("Diffuse Color", ofFloatColor(0.78, 0.53, 0.36));

	PlaneNode* plane = new PlaneNode("Water");
	plane->getTransform().setPosition(0, -50, 0);
	plane->getTransform().setOrientation(glm::vec3(-90, 0, 0));
	plane->getTransform().setScale(2.0, 2.0, 1.0);
	plane->setWidth(5000);
	plane->setHeight(5000);
	plane->getMaterial().setDiffuseColor(ofFloatColor(0.27, 0.73, 1.0));
	m_tree->addChild(plane);

	//--- Group node of spheres. This showcases the "Display" feature
	GroupNode* node = new GroupNode("Group");
	node->getTransform().setPosition(0, 0, 0);
	m_tree->addChild(node);

	int sphere_count = 1;
	float sphere_spacing = 320.0f;
	for (int z = 0; z < 1; z++) {
	    test_spawn_sphere(node, sphere_count, sphere_spacing, z * sphere_spacing, 0);
	}
	node->setDisplayNode(false);


}
