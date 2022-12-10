#pragma once // pragma once

#include "Label.hpp"
#include <../styleHelper.hpp>

class LoadingPage : public painter {
    Q_OBJECT

public:
    explicit LoadingPage(QWidget* parent);
    LoadingPage(const QString& loaderType = "default", const QString& messageType = "default");
    ~LoadingPage();

    void redraw() {}; // параметр const std::initisializer_list<QSting>

private:
    QVBoxLayout* layout;
    UiLabel loader;
    UiLabel message;
};
