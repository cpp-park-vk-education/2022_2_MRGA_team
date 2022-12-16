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

    // нужные
    UiInput(const QString& className, const QString& inputName); // className пробрасывается дальше в UiEdit и UiLabel

    UiInput(const QString& inputType, const QString& editType, const QString& inputStyle); // горизонатльный input
    UiInput(const UiLabel& _label, const UiEdit& _edit, const QString& inputStyle = "horizontal"); // вертикальный input
    UiInput(const QString& styleSheet, const UiEdit& _edit); // QString cssStyle либо id, там уже все что хотим задаем. Надо для изображения записать еще.
    // и для loader, для стилизованного input-a, реализовать UiLabel, UiEdit.

    UiInput* create(const QString& objectType); // паттерн псевдофабрика
    void updateState(){}; // const std::initializer_list<QString>&
private:
    UiLabel* label;
    UiEdit* edit;
    QGridLayout* layout;
};
