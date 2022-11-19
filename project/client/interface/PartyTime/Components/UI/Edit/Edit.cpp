#include "Edit.hpp"


UiEdit::UiEdit(QWidget *parent) : painter(parent), value(new QLineEdit()), editLayout(new QHBoxLayout(this))
{

}

UiEdit::UiEdit(const UiEdit &other) : painter(new QWidget)
{
    value = other.value;
    editLayout->addWidget(value);
    editLayout = other.editLayout;
}

UiEdit &UiEdit::operator=(const UiEdit &other)
{
    value = other.value;
    return *this;
}

UiEdit::~UiEdit()
{
    delete value;
    delete editLayout;
}

UiEdit::UiEdit(const QString &styleSheet, const QString &placeHolder, const QFont &font)
{
    value->setStyleSheet(styleSheet);
    value->setText(placeHolder);
    value->setFont(font);
    editLayout->addWidget(value);
}

UiEdit::UiEdit(const QString &styleSheet, int width, int height, int coordX, int coordY)
{
    value->setGeometry(coordX, coordY, width, height);
    value->setStyleSheet(styleSheet);
    editLayout->addWidget(value);
}

UiEdit *UiEdit::create(const QString &objectType)
{
    if (objectType == "regEdit") {
        return new UiEdit("padding: 10px");
    }
    return new UiEdit();
}
