/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Level class definition
 *
 *****************************************************/
#include "Level.h"
#include "SphereNode.h"
#include "ModelNode.h"

 /**
  * Constructor
  */
Level::Level() {

	m_tree = new BaseNode("Level");

}


/**
 * Draw node tree
 */
void Level::draw(bool objectPicking) {

	m_tree->getTransform().transformGL();
	m_tree->draw(objectPicking);
	m_tree->getTransform().restoreTransformGL();
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
	return false;
}


/**
 * Reset to a level with default values
 */
void test_spawn_sphere(BaseNode* tree, int sphere_count, float sphere_spacing, float z, int depth = 0) {

	for (int y = 0; y < sphere_count; y++) {
		for (int x = 0; x < sphere_count; x++) {
			SphereNode* node = new SphereNode("Sphere_" + std::to_string(x) + "_" + std::to_string(y));

			float ox = -((float)sphere_count * sphere_spacing) / 4.0f;
			float oy = -((float)sphere_count * sphere_spacing) / 4.0f;
			tree->addChild(node);
			float xx = ox + ((float)x * sphere_spacing);
			float yy = oy + ((float)y * sphere_spacing);
			node->getTransform().setPosition(xx, yy, z);

			if (depth == 0) {
				node->setRadius(50.0f);
				test_spawn_sphere(node, 2, 8.0, 0, 1);
			}
			else {
				node->setRadius(20.0f);
			}
		}
	}
}



/**
 * Reset level
 */
void Level::reset() {

	int sphere_count = 2;
	float sphere_spacing = 160.0f;
	for (int z = 0; z < 2; z++) {
		test_spawn_sphere(m_tree, sphere_count, sphere_spacing, z * sphere_spacing, 0);
	}

	float scale_x = 0.05;
	float scale_y = 0.05;
	float scale_z = 0.05;

	ModelNode* node_rogue = new ModelNode("Rogue", "Kaykit/Characters/gltf/Rogue.glb");
	m_tree->addChild(node_rogue);
	//node_rogue->getModel().setScale(scale_x, scale_y, scale_z);
	//node_rogue->getModel().setRotation(0, 180, 0, 0, 1);
	node_rogue->getModel().setRotation(0, 180, 1, 0, 0);
	//node_rogue->getModel().setPosition(node_rogue->getModel().getPosition().x, node_rogue->getModel().getPosition().y, node_rogue->getModel().getPosition().z - 50);


	ModelNode* node_barbarian = new ModelNode("Barbarian", "Kaykit/Characters/gltf/Barbarian.glb");
	m_tree->addChild(node_barbarian);
	//node_barbarian->getModel().setScale(scale_x, scale_y, scale_z);
	node_barbarian->getModel().setPosition(350,0,400);
	//node_barbarian->getModel().setRotation(0, 180, 0, 0, 1);
	node_barbarian->getModel().setRotation(0, 180, 1, 0, 0);
	//node_rogue->getModel().setPosition(node_rogue->getModel().getPosition().x, node_rogue->getModel().getPosition().y, node_rogue->getModel().getPosition().z - 50);

	ModelNode* node_mage = new ModelNode("Mage", "Kaykit/Characters/gltf/Mage.glb");
	m_tree->addChild(node_mage);
	//node_mage->getModel().setScale(scale_x, scale_y, scale_z);
	node_mage->getModel().setPosition(-300, 0, 0);
	//node_mage->getModel().setRotation(0, 180, 0, 0, 1);
	node_mage->getModel().setRotation(0, 180, 1, 0, 0);

	ModelNode* node_engineer = new ModelNode("Engineer", "Kaykit/Characters/gltf/Engineer.glb");
	m_tree->addChild(node_engineer);
	//node_engineer->getModel().setScale(scale_x, scale_y, scale_z);
	node_engineer->getModel().setPosition(-700, 0, -250);
	//node_engineer->getModel().setRotation(0, 180, 0, 0, 1);
	node_engineer->getModel().setRotation(0, 180, 1, 0, 0);

	ModelNode* node_druid = new ModelNode("Druid", "Kaykit/Characters/gltf/Druid.glb");
	m_tree->addChild(node_druid);
	//node_druid->getModel().setScale(scale_x, scale_y, scale_z);
	node_druid->getModel().setPosition(600, 0, -400);
	//node_druid->getModel().setRotation(0, 180, 0, 0, 1);
	node_druid->getModel().setRotation(0, 180, 1, 0, 0);

}
