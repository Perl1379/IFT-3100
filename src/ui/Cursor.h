#pragma once
#include <string>
#include <ofTexture.h>


class Cursor
{
private:
	ofTexture m_image;
	std::string m_name;
public:
	Cursor();
	Cursor(std::string p_name);
	const ofTexture& getImage() const;
	const std::string& getName() const;
};
