#pragma once // pragma once

#include "Label.hpp"

class LoadingPage : public painter {
    Q_OBJECT

public:
    explicit LoadingPage(QWidget* parent);
    LoadingPage(const QString& loaderType = "default", const QString& messageType = "default");
    ~LoadingPage();

    void redraw(){}

private:
    QVBoxLayout* layout;
    UiLabel loader;
    UiLabel message;
};
