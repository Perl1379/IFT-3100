/*****************************************************
* TP IFT3100H25 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Color class definition
 *
 *****************************************************/
#pragma once
#include <string>
#include <iostream>

class Color
{
public:
	Color(float p_v1, float p_v2, float p_v3, float p_v4, float p_a);

private:
	float m_value1;
	float m_value2;
	float m_value3;
	float m_value4;
	float m_alpha;
	std::string m_type;

public:

	float getValue1() const;
	float getValue2() const;
	float getValue3() const;
	float getValue4() const;
	float getAlpha() const;
	std::string getType() const;

};

