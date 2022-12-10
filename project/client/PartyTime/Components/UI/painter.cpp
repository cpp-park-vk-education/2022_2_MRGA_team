#include "painter.hpp"


painter::painter(QWidget *parent)
    : QWidget{parent}
{

}

void painter::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

MyIcon::MyIcon()
{

}

void MyIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QBrush brush = QBrush(this->pixmap());

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setBrush(brush);
    painter->drawRoundedRect(0, 0, width, heigth, radius, radius);
}
