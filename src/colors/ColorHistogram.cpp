/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * HistogramDialog class definition
 *
 *****************************************************/

#include "ColorHistogram.h"


Histogram::Histogram()
{
}


/**
* Grabs the texture of a camera and analyses the pixels in it
*/
ColorStat Histogram::reGenerateHistogram(int viewport)
{
	Global::m_cameras[viewport].getFbo()->getTexture().readToPixels(m_pixels);

	ofPixelFormat pixFormat = m_pixels.getPixelFormat();
	
	ColorStat colorStats;

	/**
	* Prepare looping over the pixels
	*/
	unsigned char r;
	unsigned char g;
	unsigned char b;

	// RGB by default and a case for BGR
	unsigned char redIndex = 0;
	unsigned char greenIndex = 1;
	unsigned char blueIndex = 2;
	if ((pixFormat == OF_PIXELS_BGR) || (pixFormat == OF_PIXELS_BGRA)) {
		redIndex = 2;
		greenIndex = 1;
		blueIndex = 0;
	}
	unsigned long int current = 0; // the last updated color

	auto pixIter = m_pixels.getPixelsIter(); //unsigned char == RGB, RGBA, etc. (basic types)
	for (auto it = pixIter.begin(); it != pixIter.end(); it++) {

		++colorStats.pixCount;

		//RGB //BGR
		r = (*it)[redIndex];
		g = (*it)[greenIndex];
		b = (*it)[blueIndex];

		// Count those bad boys.
		if ((r == g) && (r == b)) {
			if (r <= 5) {
				current = ++colorStats.blacks;
			}
			else if (r >= 250) {
				current = ++colorStats.whites;
			}
			else {
				//TODO: gray intensity
				current = ++colorStats.grays;
			}
		}
		else if (isBiggest(r, g, b)) {
			current = ++colorStats.reds;
			current = fillArray(colorStats.domReds, r);
		}
		else if (isBiggest(g, r, b)) {
			current = ++colorStats.greens;
			current = fillArray(colorStats.domGreens, g);
		}
		else if (isBiggest(b, r, g)) {
			current = ++colorStats.blues;
			current = fillArray(colorStats.domBlues, b);
		}
		else {
			//TODO: intensity and split logic (yellow/pink/etc.)
			current = ++colorStats.mids;
		}
		// remember which count is the biggest (to know the highest column)
		if (current > colorStats.biggest) {
			colorStats.biggest = current;
		}

	}

	colorStats.blacksP = (double)colorStats.blacks / (double)colorStats.biggest;
	colorStats.whitesP = (double)colorStats.whites / (double)colorStats.biggest;
	colorStats.graysP = (double)colorStats.grays / (double)colorStats.biggest;
	colorStats.midsP = (double)colorStats.mids / (double)colorStats.biggest;
	for (auto& p : colorStats.domReds) {
		p.second = (double)p.first / (double)colorStats.biggest;
	}
	for (auto& p : colorStats.domGreens) {
		p.second = (double)p.first / (double)colorStats.biggest;
	}
	for (auto& p : colorStats.domBlues) {
		p.second = (double)p.first / (double)colorStats.biggest;
	}

	// Return the numbers so the app can draw them out
	return colorStats;
}


/**
* Record the dominant color value
*/
unsigned long int Histogram::fillArray(std::array<std::pair<unsigned long int, double>, INTENSITY_SPLIT>& cA, unsigned char val) {
	if (val < 25) {
		return cA.at(0).first++;
	}
	else if (val < 50) {
		return cA.at(1).first++;
	}
	else if (val < 75) {
		return cA.at(2).first++;
	}
	else if (val < 100) {
		return cA.at(3).first++;
	}
	else if (val < 125) {
		return cA.at(4).first++;
	}
	else if (val < 150) {
		return cA.at(5).first++;
	}
	else if (val < 175) {
		return cA.at(6).first++;
	}
	else if (val < 200) {
		return cA.at(7).first++;
	}
	else if (val < 225) {
		return cA.at(8).first++;
	}
	else {
		return cA.at(9).first++;
	}
}

bool Histogram::isBiggest(unsigned char c1, unsigned char c2, unsigned char c3) {
	return c1 > c2 && c1 > c3;
}

bool Histogram::isInThreshold(unsigned char c) {
	return c > 150 ? true : false;
}