#include "CursorManager.h"
#include <imgui.h>

CursorManager::CursorManager()
{

}

void CursorManager::setup()
{
	addCursor("cursor");
	addCursor("hand");
	addCursor("move");
	addCursor("rotate");
	addCursor("scale");
	change("cursor");
}

void CursorManager::addCursor(const std::string& p_cursor)
{
	Cursor c = Cursor(p_cursor);
	m_availableCursors.push_back(c);
}

void CursorManager::draw()
{
	ImVec2 mousePos = ImGui::GetMousePos();
	int offsetX = mousePos.x - m_currentCursor.getTexture().getWidth()/2;
	int offsetY = mousePos.y - m_currentCursor.getTexture().getHeight() / 2;
	ImGui::GetForegroundDrawList()->AddImage(
		(void*)(intptr_t)m_currentCursor.getTexture().getTextureData().textureID,
		ImVec2(offsetX,offsetY),
		ImVec2(offsetX + m_currentCursor.getTexture().getWidth(), offsetY + m_currentCursor.getTexture().getHeight())
	);
}

void CursorManager::change(const std::string& p_cursor)
{
	for (Cursor c : m_availableCursors) {
		if (c.getName() == p_cursor) {
			m_currentCursor = c;
			break;
		}
	}
}

const Cursor CursorManager::getCursor() const
{
	return m_currentCursor;
	// TODO: insert return statement here
}
