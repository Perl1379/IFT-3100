/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * SphereNode class implementation
 *
 *****************************************************/
#include "SphereNode.h"

#include <Global.h>
#include <of3dGraphics.h>
#include <ofGraphics.h>
#include <ofLight.h>


/**
 * Constructor
 */
SphereNode::SphereNode(const std::string& p_name, float p_radius) : BaseNode(p_name) {

	m_primitive.setRadius(p_radius);
	m_primitive.setResolution(16.0);
	m_primitive.setPosition(0, 0, 0);

}


/**
 * Draw node content
 */
int SphereNode::draw(bool p_objectPicking, Camera* p_camera) {
    if (!m_displayNode) return 0;
    int count = 0;
    beginDraw(p_objectPicking, p_camera);

    if (p_camera->testVisibility(m_transform.getGlobalPosition(), getBoundingBox() * m_transform.getGlobalScale())) {
        m_transform.transformGL();
        m_vboTangent.bind();
        m_vboBitangent.bind();
        m_primitive.draw();
        m_vboBitangent.unbind();
        m_vboTangent.unbind();

        m_transform.restoreTransformGL();
        count++;
    }
	count += endDraw(p_objectPicking, p_camera);
    return count;
}


/**
 * Set sphere radius
 */
void SphereNode::setRadius(float p_radius) {
	m_primitive.setRadius(p_radius);
}


/**
 * Get bounding box
 */
ofVec3f SphereNode::getBoundingBox() const {
	const float size = m_primitive.getRadius() * 2.0f;
	return {size, size, size};
}


/**
 * Get properties
 */
std::vector<NodeProperty> SphereNode::getProperties() const {
    auto properties = BaseNode::getProperties();
    properties.emplace_back("Sphere parameters", PROPERTY_TYPE::LABEL, nullptr);
    properties.emplace_back("Radius", PROPERTY_TYPE::FLOAT_FIELD, m_primitive.getRadius());
    properties.emplace_back("Resolution", PROPERTY_TYPE::INT_FIELD, m_primitive.getResolution());
    return properties;
}


/**
 * Set property
 */
void SphereNode::setProperty(const std::string &p_name, std::any p_value) {
    if (p_name == "Radius") {
        m_primitive.setRadius(std::any_cast<float>(p_value));
        calculateTangentsAndBitangents();
        return;
    }

    if (p_name == "Resolution") {
        m_primitive.setResolution(std::any_cast<int>(p_value));
        calculateTangentsAndBitangents();
        return;
    }

    BaseNode::setProperty(p_name, std::any(p_value));

}


/**
 * Calculate tangents and bitangents
 */
void SphereNode::calculateTangentsAndBitangents() {

    // Get the mesh from the sphere

    // Get the mesh from the sphere
    ofMesh& mesh = m_primitive.getMesh();

    // Loop through the mesh indices and calculate tangents/bitangents for each triangle
    vector<glm::vec3>& vertices = mesh.getVertices(); // Use glm::vec3 here
    vector<glm::vec2>& texCoords = mesh.getTexCoords(); // Use glm::vec2 here
    vector<glm::vec3>& normals = mesh.getNormals(); // Use glm::vec3 here

    // Initialize tangents and bitangents
    vector<ofVec3f> tangents(vertices.size(), ofVec3f(0, 0, 0));
    vector<ofVec3f> bitangents(vertices.size(), ofVec3f(0, 0, 0));

    // Go through each triangle
    for (int i = 0; i < mesh.getNumIndices(); i += 3) {
        // Get indices for the triangle vertices
        int i0 = mesh.getIndex(i);
        int i1 = mesh.getIndex(i + 1);
        int i2 = mesh.getIndex(i + 2);

        // Get positions and texcoords for the three vertices of the triangle
        ofVec3f p0 = vertices[i0];
        ofVec3f p1 = vertices[i1];
        ofVec3f p2 = vertices[i2];

        ofVec2f uv0 = texCoords[i0];
        ofVec2f uv1 = texCoords[i1];
        ofVec2f uv2 = texCoords[i2];

        // Calculate edges in 3D space
        ofVec3f edge1 = p1 - p0;
        ofVec3f edge2 = p2 - p0;

        // Calculate delta UVs
        ofVec2f deltaUV1 = uv1 - uv0;
        ofVec2f deltaUV2 = uv2 - uv0;

        // Calculate tangent and bitangent using the formula
        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        ofVec3f tangent = (edge1 * deltaUV2.y - edge2 * deltaUV1.y) * f;
        ofVec3f bitangent = (edge2 * deltaUV1.x - edge1 * deltaUV2.x) * f;

        // Add tangent and bitangent to the respective vertices
        tangents[i0] += tangent;
        tangents[i1] += tangent;
        tangents[i2] += tangent;

        bitangents[i0] += bitangent;
        bitangents[i1] += bitangent;
        bitangents[i2] += bitangent;
    }

    // Normalize the tangents and bitangents
    for (int i = 0; i < tangents.size(); i++) {
        tangents[i].normalize();
        bitangents[i].normalize();
    }

    // Add tangents and bitangents as custom attributes to the mesh
    m_vboTangent.setVertexData(&tangents[0], tangents.size(), GL_STATIC_DRAW);
    m_vboBitangent.setVertexData(&bitangents[0], bitangents.size(), GL_STATIC_DRAW);
}


/**
 * Set resolution
 */
void SphereNode::setResolution(int p_resolution) {
    m_primitive.setResolution(p_resolution);
}


/**
 * Get mesh
 */
ofMesh* SphereNode::getMesh() {
    return &m_primitive.getMesh();
}