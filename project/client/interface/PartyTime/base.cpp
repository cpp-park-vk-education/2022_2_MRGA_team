#include "base.h"

Base::Base(QWidget *parent)
    : QMainWindow(parent),
      screens(new QStackedWidget()),
      authorizationPage(new authorization()),
      registrationPage(new registration())
{
    setWindowTitle("PartyTime");
    resize(1920, 792);
//    QGridLayout* main_layout = new QGridLayout(this->centralWidget());

    screens->setObjectName("screenList");
    this->setCentralWidget(screens);
    screens->setStyleSheet("background-color: #9a95c9");
//    main_layout->addWidget(screens);
//    main_layout->setColumnMinimumWidth(200, 1000);

    connect(authorizationPage->getEnterButton(), &QPushButton::clicked, this, &Base::onRegistrationPageClicked);
    connect(authorizationPage->getRegistrationButton(), &QPushButton::clicked, this, &Base::onRegistrationPageClicked);

    connect(registrationPage->getBackButton(), &QPushButton::clicked, this, &Base::onAuthPageClicked);
    connect(registrationPage->getEnterButton(), &QPushButton::clicked, this, &Base::onAuthPageClicked);


    screens->insertWidget(e_authorization, authorizationPage);
    screens->insertWidget(e_registration, registrationPage);
}

void Base::onAuthPageClicked() {
    screens->setCurrentIndex(e_authorization);
}

void Base::onRegistrationPageClicked() {
    screens->setCurrentIndex(e_registration);
}

void Base::onProfilePageClicked() {
    screens->setCurrentIndex(e_profile);
}

Base::~Base()
{
    delete screens;
    delete authorizationPage;
}
