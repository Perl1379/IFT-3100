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
	std::string getClassName() override { return "SplineControlPoint"; }


	// setters
	void setIndex(int p_index) { m_index = p_index; };
	void setPosition(float p_x, float p_y, float p_z) { setPosition(glm::vec3(p_x, p_y, p_z)); };
	void setPosition(const glm::vec3& p_pos) { m_transform.setPosition(p_pos); };
	void setAxisTransformX(bool p_value) { m_axisTransformX = p_value; };
	void setAxisTransformY(bool p_value) { m_axisTransformY = p_value; };
	void setAxisTransformZ(bool p_value) { m_axisTransformZ = p_value; };


	// getters
	int getIndex() const { return m_index; };
	glm::vec3 getPosition() const { return m_transform.getPosition(); };
	bool isSerializable() { return false; }


	std::vector<NodeProperty> getProperties() const override;
	void setProperty(const std::string& p_name, std::any p_value);

private:
	std::string getTransfoAllowed(bool p_value) const;

};

