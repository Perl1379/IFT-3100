#include "Cursor.h"
#include <ofImage.h>

Cursor::Cursor()
{
}

Cursor::Cursor(std::string p_name)
{
	m_name = p_name;
	ofImage img;
	img.load("images/ui/cursors/" + p_name + ".png");
	m_texture = img.getTexture();
}

const ofTexture& Cursor::getTexture() const
{
	return m_texture;
}

const std::string& Cursor::getName() const
{
	return m_name;
}
