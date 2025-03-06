/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ColorConverterHSV class implementation
 *
 *****************************************************/
 #include "ColorConverterHSV.h"


/**
 * Constructor
 */
ColorConverterHSV::ColorConverterHSV() {
	m_name = "HSV";
}


/**
 * Transform a color object to RGB
 */
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
	if (hue < 60.00f) {
		r = chroma + m;
		g = x + m;
		b = m;
	} else if (hue < 120.00f) {
		r = x + m;
		g = chroma + m;
		b = m;
	} else if (hue < 180.00f) {
		r = m;
		g = chroma + m;
		b = x + m;
	} else if (hue < 240.00f) {
		r = m;
		g = x + m;
		b = chroma + m;
	} else if (hue < 300.00f) {
		r = x + m;
		g = m;
		b = chroma + m;
	} 	else if (hue < 360.00f) {
		r = chroma + m;
		g = m;
		b = x + m;
	}

	ColorRGB arc(r * 255.00f, g * 255.00f, b * 255.00f, p_currentColor.getAlpha());
	return arc;
}


/**
 * Transform a RGB object to color
 */
Color ColorConverterHSV::TransformFromRGB(ColorRGB p_currentColor) {

	float red = static_cast<float>(p_currentColor.getRed());
	float green = static_cast<float>(p_currentColor.getGreen());
	float blue = static_cast<float>(p_currentColor.getBlue());
	int alpha = p_currentColor.getAlpha();

	float maxValue = std::max({ red, green, blue });
	float minValue = std::min({ red, green, blue });
	float delta = maxValue - minValue;

	// Calculate hue
	float hueValue = 0.0f;
	if (delta > 0.0f) {
		if (maxValue == red) {
			hueValue = 60.0f * (fmod(((green - blue) / delta), 6));
		} else if (maxValue == green) {
			hueValue = 60.0f * (((blue - red) / delta) + 2);
		} else if (maxValue == blue) {
			hueValue = 60.0f * (((red - green) / delta) + 4);
		}

		// Hue is always positive
		if (hueValue < 0.0f) {
			hueValue += 360.0f;
		}
	}

	// Calculate Saturation
	float saturation = (maxValue == 0.0f) ? 0.0f : (delta / maxValue) * 100.0f;

	// Calculate Brightness
	float brightness = (maxValue / 255.0f) * 100.0f;

	Color ac(hueValue, saturation, brightness, 0.0f, alpha);

	return ac;
}


/**
 * Set color object
 */
ofFloatColor ColorConverterHSV::GetColor(Color p_currentColor) {
	return ofFloatColor::fromHsb(p_currentColor.getValue1(), p_currentColor.getValue2(), p_currentColor.getValue3(), p_currentColor.getAlpha());
}


/**
 *  Get parameters
 */
std::vector<ofParameter<int>> ColorConverterHSV::getParameters(Color currentColor) {
	std::vector<ofParameter<int>> params;
	params.push_back(ofParameter<int>("Hue", currentColor.getValue1(), 0, 360));
	params.push_back(ofParameter<int>("Saturation", currentColor.getValue2(), 0,100));
	params.push_back(ofParameter<int>("Value", currentColor.getValue3(), 0, 100));
	params.push_back(ofParameter<int>("Alpha", currentColor.getAlpha(), 0, 255));
	return params;
}