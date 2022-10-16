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

