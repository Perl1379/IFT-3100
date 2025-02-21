/*****************************************************
 * TP IFT3100H25 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Color class implementation
 *
 *****************************************************/
#include "Color.h"

Color::Color(float p_v1, float p_v2, float p_v3, float p_v4, float p_a) : m_value1(p_v1), m_value2(p_v2), m_value3(p_v3), m_value4(p_v4), m_alpha(p_a) {
}

float Color::getValue1() const {
	return m_value1;
}

float Color::getValue2() const {
	return m_value2;
}

float Color::getValue3() const {
	return m_value3;
}

float Color::getValue4() const {
	return m_value4;
}

float Color::getAlpha() const {
	return m_alpha;
}

std::string Color::getType() const {
	return m_type;
}