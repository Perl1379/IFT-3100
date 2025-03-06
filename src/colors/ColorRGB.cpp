/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ColorRGB class definition
 *
 *****************************************************/
 #include "ColorRGB.h"


 /**
 * Constructor with color values
 */
ColorRGB::ColorRGB(int p_red, int p_green, int p_blue, int p_a)
	: m_red(p_red), m_green(p_green), m_blue(p_blue), m_alpha(p_a) {
}

/**
* Constructor with no vaules
*/
ColorRGB::ColorRGB() {

	m_red = 0;
	m_green = 0;
	m_blue = 0;
	m_alpha = 0;

}


/**
 * Get red component
 */
int ColorRGB::getRed() const{
	return m_red;
}


/**
 * Get green component
 */
int ColorRGB::getGreen() const {
	return m_green;
}


/**
 * Get blue component
 */
int ColorRGB::getBlue() const {
	return m_blue;
}


/**
 * Get alpha component
 */
int ColorRGB::getAlpha() const{
	return m_alpha;
}
