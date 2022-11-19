#pragma once // pragma once

#include "painter.hpp"

class UiButton : public painter {
    Q_OBJECT

public:
    explicit UiButton(QWidget* parent = nullptr);
    UiButton(const UiButton& other);
    UiButton& operator=(const UiButton&);
    ~UiButton();
    UiButton(const QString& styleSheet, const QString& btnText = nullptr, const QFont& font = QFont()); // создание стилизованной кнопки с текстом
    UiButton(const QString& styleSheet, int width, int height, int coordX, int coordY); // создание кнопки с заданным расположением и геометрией в layout-e
    UiButton(const QString& styleSheet, const QString& text,const QIcon& backgroundImage, size_t width, size_t height); // создание кнопки с текстом и картинкой

    UiButton* create(const QString& objectType); // паттерн псевдофабрика
private:
    QPushButton* button;
    QHBoxLayout* btnLayout;
};
