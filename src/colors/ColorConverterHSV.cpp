#include "ColorConverterHSV.h"

ColorConverterHSV::ColorConverterHSV() {
	m_name = "HSV";
}

ColorRGB ColorConverterHSV::TransformToRGB(Color p_currentColor) {
	float hue = p_currentColor.getValue1();
	float saturation = p_currentColor.getValue2() / 100.00f;
	float value = p_currentColor.getValue3() / 100.00f;
	float ligthness = abs(2 * value - 1);
	float chroma = value * saturation;
	float x = chroma * (1 - abs(fmod(hue / 60, 2) - 1));
	float m = value - chroma;
	float r = 0.00f;
	float g = 0.00f;
	float b = 0.00f;
	if (hue < 60.00f)
	{
		r = chroma + m;
		g = x + m;
		b = m;
	}
	else if (hue < 120.00f)
	{
		r = x + m;
		g = chroma + m;
		b = m;
	}
	else if (hue < 180.00f)
	{
		r = m;
		g = chroma + m;
		b = x + m;
	}
	else if (hue < 240.00f)
	{
		r = m;
		g = x + m;
		b = chroma + m;
	}
	else if (hue < 300.00f)
	{
		r = x + m;
		g = m;
		b = chroma + m;
	}
	else if (hue < 360.00f)
	{
		r = chroma + m;
		g = m;
		b = x + m;
	}

	ColorRGB arc(r * 255.00f, g * 255.00f, b * 255.00f, p_currentColor.getAlpha());
	return arc;
}

Color ColorConverterHSV::TransformFromRGB(ColorRGB p_currentColor) {
	int red = p_currentColor.getRed();
	int green = p_currentColor.getGreen();
	int blue = p_currentColor.getBlue();
	int alpha = p_currentColor.getAlpha();

	float maxValue = std::max({ red, green, blue });
	float minValue = std::min({ red, green, blue });
	float maxMin = maxValue - minValue;

	minValue = maxMin / maxValue;
	float value = maxValue / static_cast<float>(255) * 100;
	minValue = minValue * 100;

	float hueValue = 0;
	int maxValueInt = (int)maxValue;

	if (maxValueInt == red)
	{
		hueValue = (green - blue) / maxMin;
	}
	else if (maxValueInt == green) {
		hueValue = (blue - red) / maxMin + 2;
	}
	else if (maxValueInt == blue) {
		hueValue = (red - green) / maxMin + 4;
	}
	hueValue = 60 * hueValue;
	Color ac(hueValue, minValue, value, 0.0f, alpha);

	return ac;
}

ofFloatColor ColorConverterHSV::GetColor(Color p_currentColor) {
	return ofFloatColor::fromHsb(p_currentColor.getValue1(), p_currentColor.getValue2(), p_currentColor.getValue3(), p_currentColor.getAlpha());
}

std::vector<ofParameter<int>> ColorConverterHSV::getParameters(Color currentKnightColor) {
	std::vector<ofParameter<int>> params;
	params.push_back(ofParameter<int>("Hue", currentKnightColor.getValue1(), 0, 360));
	params.push_back(ofParameter<int>("Saturation", currentKnightColor.getValue2(), 0,100));
	params.push_back(ofParameter<int>("Value", currentKnightColor.getValue3(), 0, 100));
	params.push_back(ofParameter<int>("Alpha", currentKnightColor.getAlpha(), 0, 255));
	return params;
}