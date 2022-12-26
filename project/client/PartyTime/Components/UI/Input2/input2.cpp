#include "input2.hpp"

information_field::information_field(QString header, QWidget* parent) : painter(parent)
{
    // установим id-ик для стилизации виджета и его размеры
    this->setObjectName("information_field_background");
    this->setMinimumWidth(400);
    this->setMinimumHeight(60);
    this->setMaximumHeight(60);

    QHBoxLayout* information_field_layout = new QHBoxLayout(this);
    information_field_layout->setSpacing(20);

    m_header = new QLabel(header);
    m_header->setMinimumWidth(150);     // установим минимальное ширину header для выравнивания всех value
    m_header->setObjectName("header");

    m_value = new QLineEdit;
    m_value->setObjectName("value");

    // применяем стили
    this->set_interface_style();

    information_field_layout->addWidget(m_header, Qt::AlignLeft);
    information_field_layout->addWidget(m_value, Qt::AlignLeft);
}

information_field::~information_field()
{

}

void information_field::set_interface_style()
{
    // return this->setStyleSheet(stylehelper::get_information_field_background());
}

