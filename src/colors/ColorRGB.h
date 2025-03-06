/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ColorRGB class definition
 *
 *****************************************************/
 #pragma once


class ColorRGB
{
public:
	ColorRGB(int p_red, int p_green, int p_blue, int p_a);
	ColorRGB();

private:
	int m_red;
	int m_green;
	int m_blue;
	int m_alpha;

public:
	int getRed() const;
	int getGreen() const;
	int getBlue() const;
	int getAlpha() const;
};

