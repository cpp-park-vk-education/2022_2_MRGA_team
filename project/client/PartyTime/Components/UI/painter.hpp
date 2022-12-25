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
#include <QMovie>
#include <QSpacerItem>
#include <QFont>
#include <QIcon>
#include <QScrollArea>
#include <QMessageBox>
#include <QTextEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QCalendarWidget>
#include <QComboBox>
#include <QJsonObject>
#include <QLinearGradient>
#include <QVariant>
#include <QGraphicsPixmapItem>
#include <QJsonDocument>
#include <QSizePolicy>
#include <QtWidgets/QtWidgets>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QMediaPlayer>
#include <QUrl>
#include <vector>
#include <map>

class painter : public QWidget
{
    Q_OBJECT

public:
    explicit painter(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);

};

class MyIcon : public QGraphicsPixmapItem
{

public:
    explicit MyIcon();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option = nullptr, QWidget *widget = nullptr) override;
private:
    quint32 width   = 106;
    quint32 heigth  = 80;
    quint32 radius  = 10;

};

#endif // PAINTER_H
