#include "Input.hpp"


UiInput::UiInput(QWidget *parent) : painter(parent), layout(new QGridLayout())
{
    UiLabel* factoryLabel = new UiLabel();
    UiEdit* factoryEdit = new UiEdit();
    this->label = factoryLabel->create("defaultLabel");
    this->edit = factoryEdit->create("defaultEdit");
    delete factoryLabel;
    delete factoryEdit;
    layout->addWidget(label);
    layout->addWidget(edit);
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

UiInput::UiInput(const QString& inputType, const QString& editType, const QString& inputStyle) : layout(new QGridLayout()) // горизонтальный layout
{
    UiLabel* factoryLabel = new UiLabel();
    UiEdit* factoryEdit = new UiEdit();
    this->label = factoryLabel->create(inputType);
    this->edit = factoryEdit->create(editType);
    if (inputStyle == "vertix") {
        layout->addWidget(label, 1, 1, 1, 1);
        layout->addWidget(edit, 2, 1, 1, 1);
    } else {
        layout->addWidget(label, 1, 1, 1, 1);
        layout->addWidget(edit, 1, 2, 1, 1);
    }
}

UiInput::UiInput(const UiLabel& _label, const UiEdit& _edit, const QString& inputStyle) : layout(new QGridLayout()) {
    *(this->label) = _label;
    *(this->edit) = _edit;
    if (inputStyle == "vertix") {
        layout->addWidget(label, 1, 1, 1, 1);
        layout->addWidget(edit, 2, 1, 1, 1);
    } else {
        layout->addWidget(label, 1, 1, 1, 1);
        layout->addWidget(edit, 1, 2, 1, 1);
    }
}

UiInput::UiInput(const QString &styleSheet, const UiEdit &_edit) : layout(new QGridLayout())
{
    *(this->edit) = _edit;
    edit->setStyleSheet(styleSheet);
    layout->addWidget(edit, 1, 1, 1, 1);
}

UiInput *UiInput::create(const QString &objectType)
{
    if (objectType == "horizontalInput") {
        return new UiInput();
    }
    return new UiInput();
}
