#pragma once
#include <string>
#include <ofTexture.h>
#include <ofxImGui.h>


class Cursor
{
private:
	ofTexture m_texture;
	//ofVec2f m_offset;
	std::string m_name;
public:
	Cursor();
	Cursor(std::string p_name);
	const ofTexture& getTexture() const;
	const std::string& getName() const;
	//const ofVec2f& getOffset() const;
};
