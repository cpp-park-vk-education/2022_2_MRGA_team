#pragma once // pragma once

#include "../painter.hpp"

class UiLoader : public painter {
    Q_OBJECT

public:
    explicit UiLoader(const QString& pathToImage, QWidget* parent = nullptr);
    UiLoader(const UiLoader& other);
    UiLoader& operator=(const UiLoader&);
    ~UiLoader();
    UiLoader(const QString& styleSheet, const QString& pathToImage);
    UiLoader(const QString& pathToImage, int labelOffsetX, int labelOffsetY, int width, int height);
    void updateState(){} // const std::initializer_list<QString>&
    UiLoader* create(const QString& objectType) {if (objectType == "") {return new UiLoader("");}return new UiLoader("");};
private:
    QLabel* loader;
    QMovie* movie;
    QVBoxLayout* layout;
};
