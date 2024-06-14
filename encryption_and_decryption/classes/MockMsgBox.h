#ifndef MOCKMSGBOX_H
#define MOCKMSGBOX_H

#include "IMsgBox.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <wx/wx.h>

/**
 * @file MockMsgBox.h
 * @brief Заголовочный файл, содержащий класс для проведения mock тестов.
 */

/**
 * @brief Класс, необходимый для имитирования функции wxMessageBox.
 */
class MockMsgBox : public IMsgBox {
  public:
    /**
     * @brief mock метод, необходимый для проведения mock тестов.
     * @param message текст, выводящийся в окне-сообщении.
     * @param caption текст, выводящийся в верхней панели окна.
     * @param style переменная, задающая внешний вид, значение кнопок
     * окна-сообщения.
     * @param parent указатель на родителя окна-сообщения.
     * @return идентификаторы кнопок(например wxYes, wxNo), так как wxMessageBox
     * также их и возвращает.
     */
    MOCK_METHOD(int, Show,
                (const wxString &message, const wxString &caption, int style,
                 wxWindow *parent),
                (override));
    class MockMsgBox : public IMsgBox {
      public:
        /**
         * @brief mock метод, необходимый для проведения mock тестов.
         * @param message текст, выводящийся в окне-сообщении.
         * @param caption текст, выводящийся в верхней панели окна.
         * @param style переменная, задающая внешний вид, значение кнопок
         * окна-сообщения.
         * @param parent указатель на родителя окна-сообщения.
         * @return тип данных: int, так как wxMessageBox также возвращает
         * значения типа int.
         */
        MOCK_METHOD(int, Show,
                    (const wxString &message, const wxString &caption,
                     int style, wxWindow *parent),
                    (override));
    };

#endif