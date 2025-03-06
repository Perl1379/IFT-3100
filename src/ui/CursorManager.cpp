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
	ImGui::GetForegroundDrawList()->AddImage(
		(void*)(intptr_t)m_currentCursor.getImage().getTextureData().textureID,
		mousePos,
		ImVec2(mousePos.x + m_currentCursor.getImage().getWidth(), mousePos.y + m_currentCursor.getImage().getHeight())
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
