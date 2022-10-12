#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QPixmap>
#include <QLineEdit>
#include <QPushButton>
#include <QPalette>
#include <QSpacerItem>
#include <QFont>
#include <QIcon>
#include <QScrollArea>
#include <QMessageBox>
#include <QTextEdit>
#include <QTimeEdit>
#include <QCalendarWidget>
#include <QMovie>

class painter : public QWidget
{
    Q_OBJECT

public:
    painter(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // PAINTER_H
