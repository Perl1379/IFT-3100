/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * AssetNode class definition
 *
 *****************************************************/
#pragma once
#include "ModelNode.h"
#include "Global.h"

class AssetNode :
    public ModelNode
{
public:
    AssetNode(const std::string& p_name = "New asset", const std::string& p_fileBaseName = "");
};

