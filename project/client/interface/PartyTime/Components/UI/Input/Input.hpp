#pragma once // pragma once

#include "../painter.hpp"
#include "Edit.hpp"
#include "Label.hpp"


class UiInput : public painter {
    Q_OBJECT
public:
    explicit UiInput(QWidget* parent = nullptr);
    UiInput(const UiInput& other);
    UiInput& operator=(const UiInput& other);
    ~UiInput();
    UiInput(const QString& inputType, const QString& editType, const QString& inputStyle = "horizontal"); // горизонатльный input
    UiInput(const UiLabel& _label, const UiEdit& _edit, const QString& inputStyle = "horizontal"); // вертикальный input
    UiInput(const QString& styleSheet, const UiEdit& _edit);

    UiInput* create(const QString& objectType); // паттерн псевдофабрика
    void updateState(){}; // const std::initializer_list<QString>&
private:
    UiLabel* label;
    UiEdit* edit;
    QGridLayout* layout;
};
