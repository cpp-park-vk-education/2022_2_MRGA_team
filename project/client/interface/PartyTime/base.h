#ifndef BASE_H
#define BASE_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>

#include "authorization.hpp"


class Base : public QMainWindow
{
    Q_OBJECT

public:
    Base(QWidget *parent = nullptr);
    ~Base();
private:
    QGridLayout* mainLayout;
    QStackedWidget* screens;
    authorization* authorizationPage;
};
#endif // BASE_H
