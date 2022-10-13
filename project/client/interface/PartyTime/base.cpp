#include "base.h"

Base::Base(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("PartyTime");
    resize(1920, 792);


    mainLayout = new QGridLayout(this->centralWidget());

    screens = new QStackedWidget();
    screens->setObjectName("screenList");
    this->setCentralWidget(screens);

     QLabel* label = new QLabel();
     label->setText("I love balls");
     label->setFont(QFont("Times", 15));
     label->setStyleSheet("color: red; background-color: green");

     mainLayout->addWidget(screens);

     authorizationPage = new authorization();
     screens->insertWidget(0, authorizationPage);

     // QLabel *label = new QLabel(this);
     // label->setText("This is the label ");
     // label->setFont(QFont("Times", 15));
     // label->setStyleSheet("color: red; background-color: green");
     // label->setGeometry(20, 20, 400, 400);

     // add image
     // QLabel* label = new QLabel(this);
     // label->setGeometry(20, 20, 400, 400);
     // label->setStyleSheet("border-radius: 15px");
     // label->setPixmap(QPixmap(":/image/kingKong.png"));

     // add movie (Loader)
     // QLabel *label = new QLabel(this);
     // QMovie *movie = new QMovie(":/image/squaresLoader.gif");
     // label->setGeometry(250, 250, 400, 400);
     // label->setMovie(movie);
     // movie->start();
}

Base::~Base()
{
//    delete mainLayout;
//    delete screens;
//    delete authorizationPage;
}
