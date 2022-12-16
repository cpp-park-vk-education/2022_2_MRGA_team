#include "Edit.hpp"


UiEdit::UiEdit(QWidget *parent) : painter(parent), value(new QLineEdit()), editLayout(new QHBoxLayout(this))
{
    editLayout->addWidget(value);
}

UiEdit::UiEdit(const UiEdit &other) : painter(new QWidget)
{
    this->value->setStyleSheet(other.value->styleSheet());
    this->value->setPlaceholderText(other.value->placeholderText());
    this->editLayout->addWidget(value);
}

UiEdit &UiEdit::operator=(const UiEdit &other)
{
    this->value->setStyleSheet(other.value->styleSheet());
    this->value->setPlaceholderText(other.value->placeholderText());
    this->editLayout->addWidget(value);
    return *this;
}

UiEdit::~UiEdit()
{
    delete value;
    delete editLayout;
}

UiEdit::UiEdit(const QString &className, const QString &placeholder, const QString& editType) : value(new QLineEdit()), editLayout(new QHBoxLayout(this))
{
    value->setProperty("cssClass", className);

    if (editType == "settingsInput") {
        QPalette pal = value->palette();
        pal.setColor(QPalette::PlaceholderText, QColor(0, 0, 0, 100));
        value->setPalette(pal);
        value->setFont(QFont("Times", -1, QFont::Bold));
    }

    value->setPlaceholderText(placeholder);
    editLayout->addWidget(value);
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
        return new UiEdit("padding: 10px", "");
    }
    return new UiEdit();
}
