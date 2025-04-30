/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * LevelPersistence class definition
 *
 *****************************************************/
#pragma once
#include <Level.h>
#include <LightSource.h>
#include <ofXml.h>

class LevelPersistence {

private:

    void saveNode(ofXml & xml, BaseNode * node);
    void loadNode(ofXml & xml, BaseNode * node);

public:
    static ofFloatColor stringToColor(const std::string &str);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};
