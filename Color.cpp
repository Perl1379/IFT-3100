/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * Color class implementation
 *
 *****************************************************/
#include "Color.h"

Color::Color(float v1, float v2, float v3, float v4, int a) : value1(v1), value2(v2), value3(v3), value4(v4), alpha(a) {
}

float Color::get_value1() {
	return value1;
}

float Color::get_value2() {
	return value2;
}

float Color::get_value3() {
	return value3;
}

float Color::get_value4() {
	return value4;
}

int Color::get_alpha() {
	return alpha;
}

std::string Color::get_type() {
	return type;
}