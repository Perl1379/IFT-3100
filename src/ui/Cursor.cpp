#include "Cursor.h"
#include <ofGraphics.h>
#include "Global.h"
Cursor::Cursor()
{
}

Cursor::Cursor(std::string p_name)
{
	m_name = p_name;
	ofImage img;
	img.load("images/ui/cursors/" + p_name + ".png");
	m_image = img.getTexture();
}

const ofTexture& Cursor::getImage() const
{
	return m_image;
}

const std::string& Cursor::getName() const
{
	return m_name;
}
