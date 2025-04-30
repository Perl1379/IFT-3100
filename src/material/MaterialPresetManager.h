/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * MaterialPresetManager class declaraction
 *
 *****************************************************/
 #pragma once
#include <vector>

#include "MaterialPreset.h"

class MaterialPresetManager {

private:
    std::vector<MaterialPreset> m_presets;

    public:
    MaterialPresetManager();

    void init();
    std::vector<MaterialPreset>* getPresets();


};


