/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * AssetNode class implementation
 *
 *****************************************************/
#include "AssetNode.h"


AssetNode::AssetNode(const std::string& p_name, const std::string& p_fileBaseName) 
	: ModelNode(
		p_name,
		((p_fileBaseName != "") ? p_fileBaseName : Global::m_modelManager.getRandom(MODEL_TYPE::ASSET)),
		MODEL_TYPE::ASSET)
{
}
