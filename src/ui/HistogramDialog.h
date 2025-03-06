/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * HistogramDialog class definition
 *
 *****************************************************/
#pragma once
#include "ModalDialog.h"
#include "ColorHistogram.h"
#include "Global.h"
#include <sstream>

class HistogramDialog : public ModalDialog {
public:
    HistogramDialog();
	void draw() override;
	bool m_onlyOneCamera = false;

private:
	void drawHistogram();
	void makeResultText();
	void clearResultText();

private:
	//--- histogram
	std::array<Histogram, 3> m_histograms;
	ofFbo m_histogramFbo;
	Histogram m_histogram;
	ColorStat m_colorStats;
	std::ostringstream m_histogramInfo;
	std::ostringstream m_histogramRedsInfo;
	std::ostringstream m_histogramGreensInfo;
	std::ostringstream m_histogramBluesInfo;
	int m_histogramTextureID;

	//--- widget look & drawings
	std::string m_title = "Color Histogram";
	float m_guiWidth = 300;
	float m_guiHeight = 200;

	//--- histogram look
	float m_width = m_guiWidth - 4;
	float m_height = m_guiHeight - 10;
	float m_columnW;
	float m_baseX = 0;
	float m_dX = 0;
};