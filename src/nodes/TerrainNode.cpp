/*****************************************************
* TP IFT3100H24 - Knight Maker
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

    ofPixels heightmap;
    int width, height;
    float scale = 20.0;  // Height scale factor
    float vertexScale = 20.0f;

    ofLoadImage(heightmap, "images/terrains/default.png");

    width = heightmap.getWidth();
    height = heightmap.getHeight();

    m_meshTerrain.setMode(OF_PRIMITIVE_TRIANGLES);
    // Create vertices
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Map brightness to height
            float brightness = heightmap.getColor(x, height-y).getBrightness();
            float z = ofMap(brightness, 0, 255, -scale, scale);

            auto vertice = glm::vec3(
                (x - width / 2) * vertexScale,
                (y - height / 2) * vertexScale,
                z * vertexScale);
            m_meshTerrain.addVertex(vertice);
            m_meshTerrain.addTexCoord(glm::vec2(x, y));  // Texture coordinates
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
    for (int i = 0; i < m_meshTerrain.getIndices().size(); i += 3) {
        int i1 = m_meshTerrain.getIndex(i);
        int i2 = m_meshTerrain.getIndex(i + 1);
        int i3 = m_meshTerrain.getIndex(i + 2);

        glm::vec3 v1 = m_meshTerrain.getVertex(i1);
        glm::vec3 v2 = m_meshTerrain.getVertex(i2);
        glm::vec3 v3 = m_meshTerrain.getVertex(i3);

        // Calculate normal using cross product
        glm::vec3 edge1 = v2 - v1;
        glm::vec3 edge2 = v3 - v1;
        glm::vec3 normal = glm::normalize(glm::cross(edge2, edge1));

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
    m_boundingBox = maxBound - minBound;
    m_boundingBox.rotate(90,0,0);

}


/**
 * Draw node content
 */
int TerrainNode::draw(bool p_objectPicking, Camera* p_camera) {
    if (!m_displayNode) return 0;
    int count = 0;
    beginDraw(p_objectPicking);

    if (p_camera->testVisibility(m_transform.getGlobalPosition(), getBoundingBox())) {
        m_transform.transformGL();
        ofRotateDeg(-90,1.0, 0.0, 0.0);
        m_meshTerrain.drawFaces();
        ofRotateDeg(90,1.0, 0.0, 0.0);

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
