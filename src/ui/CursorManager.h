#pragma once
#include <vector>
#include <string>
#include "Cursor.h"
class CursorManager
{
private:
	std::vector<Cursor> m_availableCursors;
	Cursor m_currentCursor;

public:
	CursorManager();
	void setup();
	void addCursor(const std::string& p_cursor);
	void draw();
	void change(const std::string& p_cursor);
	const Cursor getCursor() const;
};

