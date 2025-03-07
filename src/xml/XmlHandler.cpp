
#include "XmlHandler.h"


XmlHandler* XmlHandler::instancePtr = nullptr;
mutex XmlHandler::mtx;



void XmlHandler::setFilePath(string path)
{
	filePath = path;
}

XmlHandler* XmlHandler::getInstance()
{
	if (instancePtr == nullptr) {
		lock_guard<mutex> lock(mtx);
		if (instancePtr == nullptr) {
			instancePtr = new XmlHandler();
		}
	}
	return instancePtr;
}

void XmlHandler::setup()
{

}

void XmlHandler::save()
{
	XML.saveFile(filePath);
}

void XmlHandler::load(string path)
{

	if (XML.loadFile(path)) {
		// Le fichier XML a ete loader avec succes
	}
	else {
		// Le fichier XML n'existe pas
	}
	setFilePath(path);

}

void XmlHandler::createNewFile(string path)
{
	if (path.empty()) {
		path = "Default.xml";
	}
	XML.clear();
	setFilePath(path);
	if (XML.loadFile(filePath)) {
		// Le fichier XML a ete loader avec succes donc un XML existait deja. Vidons le pour qu'il soit a nouveau vide.
		XML.clear();
		save();
	}
	else {
		// Le fichier XML n'existe pas
		save();
	}
}


ofVec3f XmlHandler::getFirstCameraPosition()
{
	return ofVec3f(XML.getValue("CAMERA:FIRST:POSITION:X", 0), XML.getValue("CAMERA:FIRST:POSITION:Y", 0), XML.getValue("CAMERA:FIRST:POSITION:Z", 100));
}

ofVec3f XmlHandler::getFirstCameraOrientation()
{
	return ofVec3f(XML.getValue("CAMERA:FIRST:ORIENTATION:X", 0), XML.getValue("CAMERA:FIRST:ORIENTATION:Y", 0), XML.getValue("CAMERA:FIRST:ORIENTATION:Z", 0));
}

bool XmlHandler::getFirstCameraOrtho()
{
	return XML.getValue("CAMERA:FIRST:ORTHO", 0);
}


ofVec3f XmlHandler::getSecondCameraPosition()
{
	return ofVec3f(XML.getValue("CAMERA:SECOND:POSITION:X", 0), XML.getValue("CAMERA:SECOND:POSITION:Y", 100), XML.getValue("CAMERA:SECOND:POSITION:Z", 0));
}

ofVec3f XmlHandler::getSecondCameraOrientation()
{
	return ofVec3f(XML.getValue("CAMERA:SECOND:ORIENTATION:X", 0), XML.getValue("CAMERA:SECOND:ORIENTATION:Y", 0), XML.getValue("CAMERA:SECOND:ORIENTATION:Z", 0));
}

bool XmlHandler::getSecondCameraOrtho()
{
	return XML.getValue("CAMERA:SECOND:ORTHO", 0);
}


ofVec3f XmlHandler::getThirdCameraPosition()
{
	return ofVec3f(XML.getValue("CAMERA:THIRD:POSITION:X", 100), XML.getValue("CAMERA:THIRD:POSITION:Y", 0), XML.getValue("CAMERA:THIRD:POSITION:Z", 0));
}

ofVec3f XmlHandler::getThirdCameraOrientation()
{
	return ofVec3f(XML.getValue("CAMERA:THIRD:ORIENTATION:X", 0), XML.getValue("CAMERA:THIRD:ORIENTATION:Y", 0), XML.getValue("CAMERA:THIRD:ORIENTATION:Z", 0));
}

bool XmlHandler::getThirdCameraOrtho()
{
	return XML.getValue("CAMERA:THIRD:ORTHO", 0);
}


void XmlHandler::setFirstCameraPosition(float x, float y, float z)
{
	XML.setValue("CAMERA:FIRST:POSITION:X", x);
	XML.setValue("CAMERA:FIRST:POSITION:Y", y);
	XML.setValue("CAMERA:FIRST:POSITION:Z", z);
}

void XmlHandler::setFirstCameraOrientation(float x, float y, float z)
{
	XML.setValue("CAMERA:FIRST:ORIENTATION:X", x);
	XML.setValue("CAMERA:FIRST:ORIENTATION:Y", y);
	XML.setValue("CAMERA:FIRST:ORIENTATION:Z", z);
}

void XmlHandler::setFirstCameraOrtho(bool isOrtho)
{
	XML.setValue("CAMERA:FIRST:ORTHO", isOrtho);
}


void XmlHandler::setSecondCameraPosition(float x, float y, float z)
{
	XML.setValue("CAMERA:SECOND:POSITION:X", x);
	XML.setValue("CAMERA:SECOND:POSITION:Y", y);
	XML.setValue("CAMERA:SECOND:POSITION:Z", z);
}

void XmlHandler::setSecondCameraOrientation(float x, float y, float z)
{
	XML.setValue("CAMERA:SECOND:ORIENTATION:X", x);
	XML.setValue("CAMERA:SECOND:ORIENTATION:Y", y);
	XML.setValue("CAMERA:SECOND:ORIENTATION:Z", z);
}

void XmlHandler::setSecondCameraOrtho(bool isOrtho)
{
	XML.setValue("CAMERA:SECOND:ORTHO", isOrtho);
}


void XmlHandler::setThirdCameraPosition(float x, float y, float z)
{
	XML.setValue("CAMERA:THIRD:POSITION:X", x);
	XML.setValue("CAMERA:THIRD:POSITION:Y", y);
	XML.setValue("CAMERA:THIRD:POSITION:Z", z);
}

void XmlHandler::setThirdCameraOrientation(float x, float y, float z)
{
	XML.setValue("CAMERA:THIRD:ORIENTATION:X", x);
	XML.setValue("CAMERA:THIRD:ORIENTATION:Y", y);
	XML.setValue("CAMERA:THIRD:ORIENTATION:Z", z);
}

void XmlHandler::setThirdCameraOrtho(bool isOrtho)
{
	XML.setValue("CAMERA:THIRD:ORTHO", isOrtho);
}

void XmlHandler::setNodesProperties()
{
	XML.addTag("Nodes");
	XML.pushTag("Nodes");
	for (BaseNode* child : Global::m_level.getTree()->getChildren()) {
		addNodeProperties(child);
	} 
	XML.popTag();
}

void XmlHandler::addChild(BaseNode* parent) 
{
	for (BaseNode* child : parent->getChildren()) {
		addNodeProperties(child);
	}
}

void XmlHandler::addNodeProperties(BaseNode* child) {
	int which = XML.addTag("Node");
	XML.pushTag("Node", which);
	XML.addTag("Properties");
	XML.pushTag("Properties");
	auto properties = child->getProperties();
	for (NodeProperty property : properties) {
		int x = XML.addTag("Property");
		XML.pushTag("Property", x);
		XML.addValue("Name", property.getName());
		XML.addValue("Type", property.getType());
		setNodePropertyValue(property);

		XML.popTag();
	}
	XML.popTag();
	if (!child->getChildren().empty()) {
		int x = XML.addTag("Childrens");
		XML.pushTag("Childrens", x);
		addChild(child);
		XML.popTag();
	}
	else {
		XML.addTag("Childrens");
	}

	XML.popTag();
}

void XmlHandler::setNodePropertyValue(NodeProperty property) {
	if (property.getType() == PROPERTY_TYPE::TEXT_FIELD) {
		XML.addValue("Value", std::any_cast<string> (property.getValue()));
	}

	if (property.getType() == PROPERTY_TYPE::VECTOR3) {
		auto value = std::any_cast<glm::vec3>(property.getValue());
		XML.addValue("Value", to_string(value.x) + "," + to_string(value.y) + "," + to_string(value.z));
	}

	if (property.getType() == PROPERTY_TYPE::COLOR_PICKER) {
		auto value = std::any_cast<ofFloatColor>(property.getValue());
		XML.addValue("Value", to_string(value.r) + "," + to_string(value.g) + "," + to_string(value.b) + "," + to_string(value.a));
	}

	if (property.getType() == PROPERTY_TYPE::FLOAT_FIELD) {
		XML.addValue("Value", std::any_cast<float>(property.getValue()));
	}

	if (property.getType() == PROPERTY_TYPE::LABEL) {
		XML.addValue("Value", "");
	}

	if (property.getType() == PROPERTY_TYPE::BOOLEAN_FIELD) {
		XML.addValue("Value", std::any_cast<bool>(property.getValue()));
	}

	if (property.getType() == PROPERTY_TYPE::INT_FIELD) {
		XML.addValue("Value", std::any_cast<int>(property.getValue()));
	}

	if (property.getType() == PROPERTY_TYPE::ITEM_LIST) {
		auto value = std::any_cast<std::vector<std::string>>(property.getValue());

		int initialSelection = stoi(value.back());
		int currentItem = initialSelection;

		XML.addValue("Value", currentItem);
	}
}
