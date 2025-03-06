/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * HistogramDialog class definition
 *
 *****************************************************/
#include "HistogramDialog.h"
#include <imgui.h>

 /**
  * Constructor
  */
HistogramDialog::HistogramDialog() : ModalDialog()
{
	setTitle(m_title);
	m_histogramFbo.allocate(m_guiWidth, m_guiHeight, GL_RGB);
	m_histogramFbo.begin();
	ofClear(255, 255, 255, 0);
	m_histogramFbo.end();
	m_histogramTextureID = m_histogramFbo.getTexture().getTextureData().textureID;

}


/**
 * Draw callback function
 */
void HistogramDialog::draw() {

	if (ImGui::BeginPopupModal(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
        ImGui::Dummy(ImVec2(0, 5));
        ImGui::TextColored(ImVec4(1, 0.5, 0.5, 1), "For each pixel, this tool counts which of red, blue, or green is the dominant color. \nIt does not count individual channels like one would expect. \nHope you find it fun nonetheless!");
		ImGui::Dummy(ImVec2(0.0f, 5.0f));

        if (ImGui::Button("Main Camera")) {
			m_colorStats = m_histograms.at(0).reGenerateHistogram(0);
			drawHistogram();
			makeResultText();
        }
		if (!m_onlyOneCamera)
		{
			ImGui::SameLine();
			if (ImGui::Button("Camera 2")) {
				m_colorStats = m_histograms.at(1).reGenerateHistogram(1);
				drawHistogram();
				makeResultText();
			}
			ImGui::SameLine();
			if (ImGui::Button("Camera 3")) {
				m_colorStats = m_histograms.at(2).reGenerateHistogram(2);
				drawHistogram();
				makeResultText();
			}
		}
        ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::SetNextItemWidth((float)200.0);
		ImGui::Image((ImTextureID)(intptr_t)m_histogramFbo.getTexture().getTextureData().textureID, ImVec2(m_guiWidth, m_guiHeight));
		//ImGui::Image(reinterpret_cast<ImTextureID>(histogramTextureID), ImVec2(histogram.guiWidth, histogram.guiHeight));

		if (!m_histogramInfo.str().empty())
		{
			ImGui::Dummy(ImVec2(0, 5));
			ImGui::TextColored(ImVec4(1, 0.5, 0.5, 1), "Results:");
			ImGui::TextWrapped(m_histogramRedsInfo.str().data());
			ImGui::SameLine();
			ImGui::TextWrapped(m_histogramGreensInfo.str().data());
			ImGui::TextWrapped(m_histogramBluesInfo.str().data());
			ImGui::SameLine();
			ImGui::TextWrapped(m_histogramInfo.str().data());
		}

        ImGui::Dummy(ImVec2(0.0f, 5.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::SetCursorPosX(280);

        if (ImGui::Button("Close"))
        {
			m_histogramFbo.begin();
			ofClear(255, 255, 255, 0);
			m_histogramFbo.end();
			clearResultText();
            ImGui::CloseCurrentPopup();
            m_isOpen = false;
        }	

		//IDEA: add a button to copy the result

		ImGui::EndPopup();
	}
}


/**
 * Draw histogram
 */
void HistogramDialog::drawHistogram()
{
	m_histogramFbo.begin();

	ofClear(255, 255, 255, 0);
	ofSetColor(255, 255, 255);

	m_columnW = m_width / m_colorStats.totalColors;

	ofFill();
	ofDrawRectangle(m_baseX, m_height, m_width, m_height);

	m_dX = 0;
	for (int c = 0; c < INTENSITY_SPLIT; c++) {
		ofSetColor(m_colorStats.intensitySplits.at(c), 0, 0);
		ofFill();
		ofDrawRectangle(m_baseX + (m_dX++ * m_columnW), 0, m_columnW, (m_colorStats.domReds.at(c).second * m_height));
	}
	for (int c = 0; c < INTENSITY_SPLIT; c++) {
		ofSetColor(0, m_colorStats.intensitySplits.at(c), 0);
		ofFill();
		ofDrawRectangle(m_baseX + (m_dX++ * m_columnW), 0, m_columnW, (m_colorStats.domGreens.at(c).second * m_height));
	}
	for (int c = 0; c < INTENSITY_SPLIT; c++) {
		ofSetColor(0, 0, m_colorStats.intensitySplits.at(c));
		ofFill();
		ofDrawRectangle(m_baseX + (m_dX++ * m_columnW), 0, m_columnW, (m_colorStats.domBlues.at(c).second * m_height));
	}
	ofSetColor(0, 0, 0);
	ofFill();
	ofDrawRectangle(m_baseX + (m_dX++ * m_columnW), 0, m_columnW, (m_colorStats.blacksP * m_height));
	ofSetLineWidth(1);
	ofNoFill();
	ofDrawRectangle(m_baseX + (m_dX++ * m_columnW), 0, m_columnW, (m_colorStats.whitesP * m_height));
	ofSetLineWidth(0);
	ofSetColor(150, 150, 150);
	ofFill();
	ofDrawRectangle(m_baseX + (m_dX++ * m_columnW), 0, m_columnW, (m_colorStats.graysP * m_height));
	ofSetColor(245, 245, 220);
	ofFill();
	ofDrawRectangle(m_baseX + (m_dX++ * m_columnW), 0, m_columnW, (m_colorStats.midsP * m_height));

	m_histogramFbo.end();
}


/**
 * Make result (texte)
 */
void HistogramDialog::makeResultText()
{
	clearResultText();
	m_histogramRedsInfo << "--- dominant reds total : " << m_colorStats.reds << std::endl;
	for (int i = 0; i < INTENSITY_SPLIT; i++) {
		m_histogramRedsInfo << "    < " << m_colorStats.intensitySplits.at(i) << ": " << m_colorStats.domReds.at(i).first << " (" << m_colorStats.domReds.at(i).second << ")" << std::endl;
	}
	m_histogramGreensInfo << "| --- dominant greens total : " << m_colorStats.greens << std::endl;
	for (int i = 0; i < INTENSITY_SPLIT; i++) {
		m_histogramGreensInfo << "|      < " << m_colorStats.intensitySplits.at(i) << ": " << m_colorStats.domGreens.at(i).first << " (" << m_colorStats.domGreens.at(i).second << ")" << std::endl;
	}
	m_histogramBluesInfo << std::endl << "--- dominant blues total : " << m_colorStats.blues << std::endl;
	for (int i = 0; i < INTENSITY_SPLIT; i++) {
		m_histogramBluesInfo << "    < " << m_colorStats.intensitySplits.at(i) << ": " << m_colorStats.domBlues.at(i).first << " (" << m_colorStats.domBlues.at(i).second << ")" << std::endl;
	}
	m_histogramInfo << std::endl;
	m_histogramInfo << "| --- pure black : " << m_colorStats.blacks << " (" << m_colorStats.blacksP << ")" << std::endl;
	m_histogramInfo << "| --- pure white : " << m_colorStats.whites << " (" << m_colorStats.whitesP << ")" << std::endl;
	m_histogramInfo << "| --- gray scale : " << m_colorStats.grays << " (" << m_colorStats.graysP << ")" << std::endl;
	m_histogramInfo << "| --- in betweens : " << m_colorStats.mids << " (" << m_colorStats.midsP << ")" << std::endl;
	m_histogramInfo << "|" << std::endl;
	m_histogramInfo << "| Biggest occurence: " << m_colorStats.biggest << std::endl;
	m_histogramInfo << "| Among this many pixels: " << m_colorStats.pixCount << std::endl;
}

void HistogramDialog::clearResultText()
{
	m_histogramInfo.str("");
	m_histogramInfo.clear();
	m_histogramRedsInfo.str("");
	m_histogramRedsInfo.clear();
	m_histogramGreensInfo.str("");
	m_histogramGreensInfo.clear();
	m_histogramBluesInfo.str("");
	m_histogramBluesInfo.clear();
}
