#ifndef REALMSGBOX_H
#define REALMSGBOX_H

#include <wx/wx.h>
#include "IMsgBox.h"

/**
 * @file RealMsgBox.h
 * @brief Заголовочный файл, содержащий класс, реализующий вывод окна-сообщения.
 */


/**
 * @brief Класс, необходимый для вывода окна-сообщения.
 */
class RealMsgBox: public IMsgBox {
public:
	/**
	 * @brief метод, вызываемый аттрибутом m_msg_box класса MainFrame для создания окна-сообщения. 
	 * @param message текст, выводящийся в окне-сообщении.
	 * @param caption текст, выводящийся в верхней панели окна.
	 * @param style переменная, задающая внешний вид, значение кнопок окна-сообщения.
	 * @param parent указатель на родителя окна-сообщения.
	 * @return идентификаторы кнопок(например wxYes, wxNo), так как wxMessageBox 
	 * также их и возвращает.
	 */
	int Show(const wxString &message, const wxString &caption, int style, wxWindow *parent) override;
};

#endif