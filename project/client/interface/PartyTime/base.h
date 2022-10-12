#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <QMainWindow>
#include <QStackedWidget>

#include "painter.hpp"
#include "authorization.hpp"

class Base : public QMainWindow
{
    Q_OBJECT

public:
    explicit Base(QWidget *parent = nullptr);
    ~Base();

private:
    QStackedWidget* screens;
    QGridLayout* mainLayout;

    authorization* authorizationPage;

};
#endif // BASE_H
