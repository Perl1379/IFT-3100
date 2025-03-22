/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * SplineControlPoint class definition
 *
 *****************************************************/
#pragma once
#include "ofMain.h"
#include "SphereNode.h"

class SplineControlPoint : public SphereNode {

protected:
	int m_index;

public:
	SplineControlPoint(const std::string& p_name, const glm::vec3& p_pos);
	~SplineControlPoint();

	int getIndex() const								{ return m_index; };
	void setIndex(int p_index)							{ m_index = p_index; };
	void setPosition(float p_x, float p_y, float p_z)	{ setPosition(glm::vec3(p_x, p_y, p_z)); };
	void setPosition(const glm::vec3& p_pos)			{ m_transform.setPosition(p_pos); };
	glm::vec3 getPosition() const						{ return m_transform.getPosition(); };

	std::vector<NodeProperty> getProperties() const override;
	void setProperty(const std::string& p_name, std::any p_value);

};

