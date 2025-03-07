/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * FileGeneratedDialog class declaration
 *
 *****************************************************/
#pragma once
#include <ModalDialog.h>


class FileGeneratedDialog : public ModalDialog {

    private:
        std::string m_content;
        std::string m_filename;

    public:
        FileGeneratedDialog();
        void setContent(const std::string& p_content, const std::string& p_filename);
        void draw() override;
};


