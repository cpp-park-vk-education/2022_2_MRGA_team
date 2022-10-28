#include "base.h"

Base::Base(QWidget *parent)
    : QMainWindow(parent),
      screens(new QStackedWidget()),
      authorizationPage(new authorization()),
      registrationPage(new registration())
{
    setWindowTitle("PartyTime");
    resize(1920, 792);

    screens->setObjectName("screenList");
    this->setCentralWidget(screens);
    screens->setStyleSheet("background-color: #9a95c9");

    connect(authorizationPage->getEnterButton(), &QPushButton::clicked, this, &Base::onEnter);
    connect(authorizationPage->getRegistrationButton(), &QPushButton::clicked, this, &Base::onRegistrationPageClicked);

    connect(registrationPage->getBackButton(), &QPushButton::clicked, this, &Base::onAuthPageClicked);
    connect(registrationPage->getEnterButton(), &QPushButton::clicked, this, &Base::onRegister);


    screens->insertWidget(e_authorization, authorizationPage);
    screens->insertWidget(e_registration, registrationPage);
}

void Base::onAuthPageClicked() {
    screens->setCurrentIndex(e_authorization);
    registrationPage->emailClear();
    registrationPage->loginClear();
    registrationPage->passwordClear();
    registrationPage->passwordRepeatClear();
}

void Base::onRegister()
{
    try {
        if (registrationPage->checkUserInputData()) {
            throw "User input isn't correct !";
        }
        screens->setCurrentIndex(e_authorization);
        registrationPage->emailClear();
        registrationPage->loginClear();
        registrationPage->passwordClear();
        registrationPage->passwordRepeatClear();
    } catch (const char* exception) {
        std::cout << "Error: " << exception << "\n";
        screens->setCurrentIndex(e_registration);
    }
}

void Base::onRegistrationPageClicked() {
    screens->setCurrentIndex(e_registration);
    authorizationPage->loginClear();
    authorizationPage->passwordClear();
}

void Base::onEnter()
{
    try {
        if (authorizationPage->checkUserInputData()) {
            throw "User input isn't correct !";
        }
        screens->setCurrentIndex(e_registration);
        authorizationPage->loginClear();
        authorizationPage->passwordClear();
    } catch (const char* exception) {
        std::cout << "Error: " << exception << "\n";
        screens->setCurrentIndex(e_authorization);
    }
}

// void Base::onProfilePageClicked() {
//     screens->setCurrentIndex(e_profile);
// }

Base::~Base()
{
//    delete authorizationPage;
//    delete registrationPage;
    delete screens;
}
