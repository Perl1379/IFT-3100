#include "ColorRGB.h"
ColorRGB::ColorRGB(int p_red, int p_green, int p_blue, int p_a)
	: m_red(p_red), m_green(p_green), m_blue(p_blue), m_alpha(p_a) {
}

ColorRGB::ColorRGB() {}

int ColorRGB::getRed() const{
	return m_red;
}

int ColorRGB::getGreen() const {
	return m_green;
}

int ColorRGB::getBlue() const {
	return m_blue;
}

int ColorRGB::getAlpha() const{
	return m_alpha;
}
