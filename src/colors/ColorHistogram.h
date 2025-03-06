/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * HistogramDialog class definition
 *
 *****************************************************/
#pragma once

#include "ofMain.h"
#include "Global.h"

constexpr auto INTENSITY_SPLIT = 10;

struct ColorStat {
	std::array<int, INTENSITY_SPLIT> intensitySplits{ {25, 50, 75, 100, 125, 150, 175, 200, 225, 250} };
	unsigned char totalColors = 37;

	std::array<std::pair<unsigned long int, double>, INTENSITY_SPLIT> domReds = { { {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}} };
	std::array<std::pair<unsigned long int, double>, INTENSITY_SPLIT> domGreens = { { {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}} };
	std::array<std::pair<unsigned long int, double>, INTENSITY_SPLIT> domBlues = { { {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}, {0,0.0}} };

	unsigned long int reds = 0; //red higher than others
	unsigned long int blues = 0;
	unsigned long int greens = 0;

	unsigned long int blacks = 0; // 255 everywhere
	unsigned long int whites = 0; // 0 everywhere

	unsigned long int grays = 0; // all equals

	unsigned long int mids = 0;
	//unsigned long int yellows = 0; // red & green
	//unsigned long int cyans = 0; // green & blue
	//unsigned long int pinks = 0; // red & blue

	double redsP = 0;
	double bluesP = 0;
	double greensP = 0;

	double blacksP = 0;
	double whitesP = 0;
	double graysP = 0;
	double midsP = 0;

	unsigned long int biggest = 0;
	unsigned long int pixCount = 0;
};


class Histogram {

public:
	Histogram();
	ColorStat reGenerateHistogram(int viewport = 0);


private:
	ofFbo m_histogramFbo;
	ofPixels m_pixels;

	unsigned long int fillArray(std::array<std::pair<unsigned long int, double>, INTENSITY_SPLIT>& cA, unsigned char val);
	bool isBiggest(unsigned char c1, unsigned char c2, unsigned char c3);
	bool isInThreshold(unsigned char c);



};