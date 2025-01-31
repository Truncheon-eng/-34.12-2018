#ifndef APP_H
#define APP_H

#include <wx/wx.h>

/**
 * @file App.h
 *
 * @brief Заголовочный файл, содержащий описание класса приложения.
 */

/**
 * @brief Класс, который отвечает за инициализацию приложения, создание главного
 * окна(при использовании класса MainFrame) и запуск цикла обработки событий.
 */

class App : public wxApp {
  public:
    /**
     * @brief Метод, вызываемый при запуске GUI приложения. В нём создаётся
     * главное окно, выводимое на экран.
     *
     * @return true, если инициализация и создание окна прошло успешно,
     * false - в противном случае.
     */
    bool OnInit();
};

#endif