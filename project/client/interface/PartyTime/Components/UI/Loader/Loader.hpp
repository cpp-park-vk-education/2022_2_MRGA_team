#pragma once // pragma once

#include "painter.hpp"

class UiLoader : public painter {
    Q_OBJECT

public:
    explicit UiLoader(const QString& pathToImage, QWidget* parent = nullptr);
    UiLoader(const UiLoader& other);
    UiLoader& operator=(const UiLoader&);
    ~UiLoader();
    UiLoader(const QString& styleSheet, const QString& pathToImage);
    UiLoader(const QString& pathToImage, int labelOffsetX, int labelOffsetY, int width, int height);

private:
    QLabel* loader;
    QMovie* movie;
    QVBoxLayout* layout;
};

//class UiLabel : public painter {
//    Q_OBJECT

//public:
//    explicit UiLabel(QWidget* parent = nullptr);
//    UiLabel(const UiLabel& other);
//    UiLabel& operator=(const UiLabel&);
//    ~UiLabel();
//    UiLabel(const QString& styleSheet, const QPixmap& labelImage, int width = 0, int height = 0, int coordX = 0, int coordY = 0);   // декорирование картинка с позиционированием
//    UiLabel(const QString& styleSheet, const QFont& font = QFont(), int width = 0, int height = 0, int coordX = 0, int coordY = 0);                                // стилизованный текст с позициоированием
//    UiLabel(const QString& styleSheet, QMovie* movie);                                                                        // конструтор для анимации, напрмиер для Loader-a

//    UiLabel* create(const QString& objectType); // паттерн псевдофабрика

//private:
//    QLabel* label;
//    QHBoxLayout* labelLayout;
//};
