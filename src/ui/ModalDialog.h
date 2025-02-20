/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * ModalDialog class definition
 *
 *****************************************************/
#pragma once
#include <string>

class ModalDialog {

protected:
	std::string m_title = "Untitled";
	bool m_isOpen = false;

public:
	ModalDialog();
	void setTitle(const std::string& p_title);
	void openDialog();
	bool isOpen();
	virtual void draw();

};


