#include "Input.hpp"


UiInput::UiInput(QWidget *parent) : painter(parent), layout(new QGridLayout())
{
    layout->addWidget(&label);
    layout->addWidget(&edit);
}

UiInput::UiInput(const UiInput &other) : painter(new QWidget)
{
    this->label = other.label;
    this->edit = other.edit;
    this->layout = other.layout;
}

UiInput &UiInput::operator=(const UiInput &other)
{
    this->label = other.label;
    this->edit = other.edit;
    this->layout = other.layout;
    return *this;
}

UiInput::~UiInput(){
    delete layout;
}

UiInput::UiInput(const UiLabel &_label, const UiEdit &_edit) : label(_label), edit(_edit), layout(new QGridLayout()) // горизонтальный layout
{
    layout->addWidget(&label, 1, 1, 1, 1);
    layout->addWidget(&edit, 1, 2, 1, 1);
}

UiInput::UiInput(const UiLabel& _label, const UiEdit& _edit, const QString& inputStyle) : label(_label), edit(_edit), layout(new QGridLayout()) {
    if (inputStyle == "vertix") {
        layout->addWidget(&label, 1, 1, 1, 1);
        layout->addWidget(&edit, 2, 1, 1, 1);
    } else {
        layout->addWidget(&label, 1, 1, 1, 1);
        layout->addWidget(&edit, 1, 2, 1, 1);
    }
}

UiInput::UiInput(const QString &styleSheet, const UiEdit &_edit) : edit(_edit), layout(new QGridLayout())
{
    edit.setStyleSheet(styleSheet);
    layout->addWidget(&edit, 1, 1, 1, 1);
}

UiInput *UiInput::create(const QString &objectType)
{
    if (objectType == "horizontalInput") {
        return new UiInput();
    }
    return new UiInput();
}
