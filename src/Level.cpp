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
				node->setRadius(5.0f);
				test_spawn_sphere(node, 2, 8.0, 0, 1);
			}
			else {
				node->setRadius(2.0f);
			}

		}
	}

}



/**
 * Reset level
 */
void Level::reset() {

	int sphere_count = 2;
	float sphere_spacing = 16.0f;
	for (int z = 0; z < 2; z++) {
		test_spawn_sphere(m_tree, sphere_count, sphere_spacing, z * sphere_spacing, 0);
	}

}
