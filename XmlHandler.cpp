
#include "XmlHandler.h"

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
		// Le fichier XML a été loader avec succès
	}
	else {
		// Le fichier XML n'existe pas
	}
	setFilePath(path);

}

void XmlHandler::createNewFile(string path)
{
	setFilePath(path);
	if (XML.loadFile(filePath)) {
		// Le fichier XML a été loader avec succès donc un XML existait déjà. Vidons le pour qu'il soit à nouveau vide.
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


ofVec3f XmlHandler::getSecondCameraPosition()
{
	return ofVec3f(XML.getValue("CAMERA:SECOND:POSITION:X", 0), XML.getValue("CAMERA:SECOND:POSITION:Y", 100), XML.getValue("CAMERA:SECOND:POSITION:Z", 0));
}

ofVec3f XmlHandler::getSecondCameraOrientation()
{
	return ofVec3f(XML.getValue("CAMERA:SECOND:ORIENTATION:X", 0), XML.getValue("CAMERA:SECOND:ORIENTATION:Y", 0), XML.getValue("CAMERA:SECOND:ORIENTATION:Z", 0));
}


ofVec3f XmlHandler::getThirdCameraPosition()
{
	return ofVec3f(XML.getValue("CAMERA:THIRD:POSITION:X", 100), XML.getValue("CAMERA:THIRD:POSITION:Y", 0), XML.getValue("CAMERA:THIRD:POSITION:Z", 0));
}

ofVec3f XmlHandler::getThirdCameraOrientation()
{
	return ofVec3f(XML.getValue("CAMERA:THIRD:ORIENTATION:X", 0), XML.getValue("CAMERA:THIRD:ORIENTATION:Y", 0), XML.getValue("CAMERA:THIRD:ORIENTATION:Z", 0));
}


void XmlHandler::setFirstCameraPosition(int x, int y, int z)
{
	XML.setValue("CAMERA:FIRST:POSITION:X", x);
	XML.setValue("CAMERA:FIRST:POSITION:Y", y);
	XML.setValue("CAMERA:FIRST:POSITION:Z", z);
}

void XmlHandler::setFirstCameraOrientation(int x, int y, int z)
{
	XML.setValue("CAMERA:FIRST:ORIENTATION:X", x);
	XML.setValue("CAMERA:FIRST:ORIENTATION:Y", y);
	XML.setValue("CAMERA:FIRST:ORIENTATION:Z", z);
}


void XmlHandler::setSecondCameraPosition(int x, int y, int z)
{
	XML.setValue("CAMERA:SECOND:POSITION:X", x);
	XML.setValue("CAMERA:SECOND:POSITION:Y", y);
	XML.setValue("CAMERA:SECOND:POSITION:Z", z);
}

void XmlHandler::setSecondCameraOrientation(int x, int y, int z)
{
	XML.setValue("CAMERA:SECOND:ORIENTATION:X", x);
	XML.setValue("CAMERA:SECOND:ORIENTATION:Y", y);
	XML.setValue("CAMERA:SECOND:ORIENTATION:Z", z);
}


void XmlHandler::setThirdCameraPosition(int x, int y, int z)
{
	XML.setValue("CAMERA:THIRD:POSITION:X", x);
	XML.setValue("CAMERA:THIRD:POSITION:Y", y);
	XML.setValue("CAMERA:THIRD:POSITION:Z", z);
}

void XmlHandler::setThirdCameraOrientation(int x, int y, int z)
{
	XML.setValue("CAMERA:THIRD:ORIENTATION:X", x);
	XML.setValue("CAMERA:THIRD:ORIENTATION:Y", y);
	XML.setValue("CAMERA:THIRD:ORIENTATION:Z", z);
}
