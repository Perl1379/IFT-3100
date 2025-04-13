/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * TerrainNode class implementation
 *
 *****************************************************/
 #include "TerrainNode.h"

#include <BaseNode.h>
#include <ofGraphics.h>
#include <ofImage.h>
#include <ofVec3f.h>
#include <ofPixels.h>

/**
 * Constructor
 */
TerrainNode::TerrainNode(const std::string& p_name) : BaseNode(p_name) {
    // Load terrain names
    ofDirectory dirTerrains;
    dirTerrains.listDir("images/terrains/");

    for (size_t i=0;i<dirTerrains.size();i++) {
        std::string name = dirTerrains.getFile(i).getBaseName();
        m_terrainNames.push_back(name);
    }

    sort(m_terrainNames.begin(), m_terrainNames.end());
    m_terrainNames.push_back("0");

    m_materialNode.setShininess(2000);
}


/**
 * Lodd terrain
 */
void TerrainNode::loadTerrain() {

    ofPixels heightmap;
    int width, height;
    float scale = 60.0;  // Height scale factor
    float vertexScale = 20.0f;

    if (!ofLoadImage(heightmap, "images/terrains/" + m_terrainName + ".png")) {
        ofLogError("TerrainNode") << "Failed to load image " << m_terrainName + ".png";
        ofExit(-1);
    }

    width = heightmap.getWidth()-1;
    height = heightmap.getHeight()-1;

    m_meshTerrain.clear();
    m_meshTerrain.setMode(OF_PRIMITIVE_TRIANGLES);
    // Create vertices
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Map brightness to height
            float brightness = heightmap.getColor(x, height-y).getBrightness();
            float z = ofMap(brightness, 0, 255, -scale, scale);

            auto vertice = glm::vec3(
                (x - width / 2) * vertexScale,
                z * vertexScale,
                (y - height / 2) * vertexScale
                );
            m_meshTerrain.addVertex(vertice);
            m_meshTerrain.addTexCoord(glm::vec2((float)x / (width - 1), (float)y / (height - 1)));
//            m_meshTerrain.addTexCoord(glm::vec2(x, y));  // Texture coordinates
            m_meshTerrain.addNormal(glm::vec3(0, 0, 1)); // Temporary
        }
    }

    // Create triangle indices
    for (int y = 0; y < height - 1; y++) {
        for (int x = 0; x < width - 1; x++) {
            int topLeft = y * width + x;
            int topRight = y * width + (x + 1);
            int bottomLeft = (y + 1) * width + x;
            int bottomRight = (y + 1) * width + (x + 1);

            m_meshTerrain.addIndex(topLeft);
            m_meshTerrain.addIndex(bottomLeft);
            m_meshTerrain.addIndex(topRight);

            m_meshTerrain.addIndex(topRight);
            m_meshTerrain.addIndex(bottomLeft);
            m_meshTerrain.addIndex(bottomRight);
        }
    }


    // Compute normals on completed geometry
    std::vector<glm::vec3> normals(m_meshTerrain.getVertices().size(), glm::vec3(0, 0, 0));

    // Loop through all triangles
    for (size_t i = 0; i < m_meshTerrain.getIndices().size(); i += 3) {
        int i1 = m_meshTerrain.getIndex(i);
        int i2 = m_meshTerrain.getIndex(i + 1);
        int i3 = m_meshTerrain.getIndex(i + 2);

        glm::vec3 v1 = m_meshTerrain.getVertex(i1);
        glm::vec3 v2 = m_meshTerrain.getVertex(i2);
        glm::vec3 v3 = m_meshTerrain.getVertex(i3);

        // Calculate normal using cross product
        glm::vec3 edge1 = v2 - v1;
        glm::vec3 edge2 = v3 - v1;
        glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

        // Assign normal to vertices
        normals[i1] += normal;
        normals[i2] += normal;
        normals[i3] += normal;
    }

    // Normalize all normals
    for (auto &n : normals) {
         n = glm::normalize(n);
    }


    // Update mesh normals
    m_meshTerrain.clearNormals();
    for (const auto &n : normals) {
        m_meshTerrain.addNormal(n);
    }

    // Compute bounding box
    ofVec3f minBound, maxBound;

    // Initialize min and max with the first vertex
    minBound = m_meshTerrain.getVertex(0);
    maxBound = m_meshTerrain.getVertex(0);

    // Iterate over all vertices
    for (const auto &v : m_meshTerrain.getVertices()) {
        minBound.x = std::min(minBound.x, v.x);
        minBound.y = std::min(minBound.y, v.y);
        minBound.z = std::min(minBound.z, v.z);

        maxBound.x = std::max(maxBound.x, v.x);
        maxBound.y = std::max(maxBound.y, v.y);
        maxBound.z = std::max(maxBound.z, v.z);
    }

    // Compute center
    m_boundingBox = (maxBound - minBound);
}


/**
 * Draw node content
 */
int TerrainNode::draw(bool p_objectPicking, Camera* p_camera) {
    if (!m_displayNode) return 0;
    int count = 0;
    beginDraw(p_objectPicking, p_camera);

    if (p_camera->testVisibility(m_transform.getGlobalPosition(), getBoundingBox() * m_transform.getGlobalScale())) {
        m_transform.transformGL();

        m_meshTerrain.drawFaces();
        //
        // ofSetColor(255,255,0);
        // for (int i = 0; i < m_meshTerrain.getNumVertices(); ++i) {
        //      glm::vec3 p = m_meshTerrain.getVertex(i);
        //      glm::vec3 n = m_meshTerrain.getNormal(i);
        //
        //      ofDrawLine(p, p + n * 20.0f); // visualize normals
        //  }


        m_transform.restoreTransformGL();
        count++;
    }
    count += endDraw(p_objectPicking, p_camera);
    return count;
}


/**
 * Get bounding box
 */
ofVec3f TerrainNode::getBoundingBox() const {
    return m_boundingBox;
}


/**
 * Set terrain name
 */
void TerrainNode::setTerrainName(const std::string& p_name) {
   
    m_terrainName = p_name;

    for (size_t i=0;i<m_terrainNames.size()-1;i++) {
        if (m_terrainNames[i] == p_name) {
            m_terrainNames.back() = std::to_string(i);
            break;
        }
    }
}


/**
 * Get terrain name
 */
std::string TerrainNode::getTerrainName() const {
    return m_terrainName;
}



/**
 * Get properties
 */
std::vector<NodeProperty> TerrainNode::getProperties() const {
    auto properties = BaseNode::getProperties();
    properties.emplace_back("Terrain parameters", PROPERTY_TYPE::LABEL, nullptr);
    properties.emplace_back("TerrainName", PROPERTY_TYPE::ITEM_LIST, m_terrainNames);
    return properties;
}

/**
 * Set property
 */
void TerrainNode::setProperty(const std::string &p_name, std::any p_value) {

    if (p_name == "TerrainName") {
        int index = std::any_cast<int>(p_value);
        setTerrainName(m_terrainNames[index]);
        loadTerrain();;
        return;
    }


    BaseNode::setProperty(p_name, std::any(p_value));
}


/**
 * Get mesh
 */
ofMesh* TerrainNode::getMesh() {
    return &m_meshTerrain;
}