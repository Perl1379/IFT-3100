/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * SplineNode class definition
 *
 *****************************************************/
#include "SplineNode.h"
#include "Global.h"

/* 
TODO / ideas
    - add buttons in parameters to show/hide all control points at once
    - and/or show control points only when the spline or another point is selected
    - allow changing the primitive used by a point (could be per point or for all at once)
    - option to add/insert control points (could have only that option in the AddNodeDialog instead of m_userCanAddChild)
    - option to change the drawing mode (curveTo, bezierTo, etc.)
    - figure out setStrokeWidth (dunno why it works in a test project but not here)
    - draw a spline bounding box so it encompasses all the points maximum position
    - option to close the spline (link first and last points)
    - clean up unecessary or unused parameters
    - apply the spline's color to its points
    - etc.
*/


/**
 * Constructor
 * Make sure to call "init()" after creating the spline otherwise it won't have any control points.
 */
SplineNode::SplineNode(const std::string& p_nodeName)
    : BaseNode(p_nodeName)
{
    // for now, to make things easier, a spline can only have SplineControlPoint as children (these SplineControlPoint may have children)
    m_userCanAddChild = false;
    m_strokeWidth = m_DEFAULT_STROKE_WIDTH;
}


/**
 * Creates the control points
 */
void SplineNode::init(int p_controlPointsCount)
{
    // number of gaps times the space between each points, divided by 2,
    // give the "center" of the spline, so the first point is at minus that value
    float x = -(((p_controlPointsCount - 1) * m_DEFAULT_SPACING) / 2);
    float y = 0;
    float z = m_DEFAULT_SPACING;

    for (int i = 0; i < p_controlPointsCount; i++) {
        SplineControlPoint* controlPoint = new SplineControlPoint("Control point " + std::to_string(i+1), glm::vec3(x, y, z));
        z = -z;
        x += m_DEFAULT_SPACING;
        addChild(controlPoint);
        m_controlPoints.push_back(controlPoint);
        controlPoint->setIndex(i);
    }
    updatePath();
}


/**
 * Reform the path after a change
 */
void SplineNode::updatePath() 
{
    m_path.clear();
    m_path.setFilled(false);
    m_path.setStrokeColor(m_materialNode.getAmbientColor());
    m_path.setStrokeWidth(m_strokeWidth);

    m_path.moveTo(m_children[0]->getTransform().getPosition());
    m_path.curveTo(m_children[0]->getTransform().getPosition());
    for (size_t i = 0; i < m_children.size(); i++) {
        m_path.curveTo(m_children[i]->getTransform().getPosition());
        m_controlPoints[i]->setIndex(i); //in case a point was deleted
    }
    m_path.curveTo(m_children.back()->getTransform().getPosition());
}

/**
 * Draw node content
 */
int SplineNode::draw(bool p_objectPicking, Camera* p_camera) 
{
    if (m_dirty) {
        m_dirty = false; 
        updatePath();
    }
    if (!m_displayNode) return 0;

    int count = 0;
    beginDraw(p_objectPicking, p_camera);

    if (p_camera->testVisibility(m_transform.getGlobalPosition(), getBoundingBox() * m_transform.getGlobalScale())) {
        m_transform.transformGL();
        m_path.draw();
        m_transform.restoreTransformGL();
        count++;
    }
    count += endDraw(p_objectPicking, p_camera);
    return count;
}


/**
 * For a SplineNode, this is received after a spline control point changed (moved, reordered, deleted...)
 */
void SplineNode::nodeChanged(const std::string& p_name, std::any p_value) 
{
    if (p_name == "Deleted") {
        // A SplineControlPoint is being deleted.
        // we defer updatePath() to the next frame, that is to say after the SplineControlPoint as finished deleting
        // we remove it from the controlPoint list right now
        m_dirty = true; 
        m_controlPoints.erase(m_controlPoints.begin() + std::any_cast<int>(p_value)); 
        return;
    }
    else if (p_name == "Child Order Swapped") {
        std::pair< BaseNode*, BaseNode*> swapped = std::any_cast<std::pair< BaseNode*, BaseNode*>>(p_value);

        //Swapping the SplineControlPoint also in control points list
        SplineControlPoint* temp1 = nullptr;
        SplineControlPoint* temp2 = nullptr;
        for (SplineControlPoint* controlPoint : m_controlPoints) {
            if (controlPoint->getId() == swapped.first->getId()) {
                temp1 = controlPoint;
            }
            else if (controlPoint->getId() == swapped.second->getId()) {
                temp2 = controlPoint;
            }
        }
        if ((temp1 != nullptr) && (temp2 != nullptr)) {
            std::vector<SplineControlPoint*> temp_controlpoints;
            for (SplineControlPoint* controlPoint : m_controlPoints) {
                if (controlPoint == temp1) {
                    temp_controlpoints.push_back(temp2);
                }
                else if (controlPoint == temp2) {
                    temp_controlpoints.push_back(temp1);
                }
                else {
                    temp_controlpoints.push_back(controlPoint);
                }
            }
            m_controlPoints = temp_controlpoints;
        }
    }
    updatePath();
}

std::vector<NodeProperty> SplineNode::getProperties() const
{
    std::vector<NodeProperty> properties;
    properties.emplace_back("Name", PROPERTY_TYPE::TEXT_FIELD, m_name);
    properties.emplace_back("Display", PROPERTY_TYPE::BOOLEAN_FIELD, m_displayNode, Global::m_tooltipMessages.node_display);
    properties.emplace_back("Transform", PROPERTY_TYPE::LABEL, nullptr);
    properties.emplace_back("Position", PROPERTY_TYPE::VECTOR3, m_transform.getPosition());
    properties.emplace_back("Orientation", PROPERTY_TYPE::VECTOR3, m_transform.getOrientationEulerDeg());
    properties.emplace_back("Scale", PROPERTY_TYPE::VECTOR3, m_transform.getScale());
    properties.emplace_back("Material", PROPERTY_TYPE::LABEL, nullptr);
    properties.emplace_back("Diffuse Color", PROPERTY_TYPE::COLOR_PICKER, m_materialNode.getDiffuseColor());
    properties.emplace_back("Ambient Color", PROPERTY_TYPE::COLOR_PICKER, m_materialNode.getAmbientColor());
    properties.emplace_back("Emissive Color", PROPERTY_TYPE::COLOR_PICKER, m_materialNode.getEmissiveColor());
    properties.emplace_back("Specular Color", PROPERTY_TYPE::COLOR_PICKER, m_materialNode.getSpecularColor());
    properties.emplace_back("Shininess", PROPERTY_TYPE::FLOAT_FIELD, m_materialNode.getShininess());

    //Spline property
    properties.emplace_back("Spline parameters", PROPERTY_TYPE::LABEL, nullptr);
    properties.emplace_back("Thickness", PROPERTY_TYPE::FLOAT_FIELD, m_strokeWidth);
    properties.emplace_back("Points count", PROPERTY_TYPE::TEXT_INFO, std::to_string(m_children.size()));

    return properties;
}
