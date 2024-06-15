#ifndef IMSGBOX_H
#define IMSGBOX_H

#include <wx/wx.h>

/**
 * @file IMsgBox.h
 * @brief Заголовочный файл, содержащий класс-интерфейс.
 */

/**
 * @brief Класс-интерфейс, необходимый для создания классов, использующихся как
 * в самом приложении, так и в тестах.
 */
class IMsgBox {
  public:
    /**
     * @brief виртуальный метод, необходимый для последующего переопределения в
     * дочерних классах.
     *
     * @param message текст, выводящийся в окне-сообщении.
     *
     * @param caption текст, выводящийся в верхней панели окна.
     *
     * @param style переменная, задающая внешний вид, значение кнопок
     * окна-сообщения.
     *
     * @param parent указатель на родителя окна-сообщения.
     *
     * @return идентификаторы кнопок(например wxYes, wxNo), так как wxMessageBox
     * также их и возвращает.
     *
     */
    virtual int Show(const wxString &message, const wxString &caption,
                     int style, wxWindow *parent) = 0;
};

#endif