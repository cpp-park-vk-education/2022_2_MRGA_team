#pragma once

#include "Label.hpp"
#include "Button.hpp"

class Footer : public painter {
    Q_OBJECT

public:
    explicit Footer(QWidget* parent = nullptr);
    Footer(const Footer& other);
    Footer& operator=(const Footer& other);
    ~Footer();
    void redraw() {}
    Footer *create(const QString& typeObject);
private:
    QHBoxLayout* mainLayout;
    QVBoxLayout* firstCol;
    QVBoxLayout* secondCol;
    QVBoxLayout* thirdCol;

    // 1-ая колонка
    UiLabel contactInfo;
    UiButton email;
    UiButton phoneNumber;
    UiLabel legalInfo;
    // 2-ая колонка
    std::vector<QString> developersInfo;
    // 3-я колонка
    std::vector<UiButton*> partnersLogoList;
};
