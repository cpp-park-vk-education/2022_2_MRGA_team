#include "base.h"

Base::Base(QWidget *parent)
    : QMainWindow(parent),
      screens(new QStackedWidget()),
      authorizationPage(new authorization()),
      registrationPage(new registration()),
//      profilePage(new ProfilePage()),
      visitorEventListPage(new VisitorEventListPage())
{
    setWindowTitle("PartyTime");

    screens->setObjectName("generalBackground");
    this->setCentralWidget(screens);

    connect(authorizationPage->getEnterButton(), &QPushButton::clicked, this, &Base::onEnter);
    connect(authorizationPage->getRegistrationButton(), &QPushButton::clicked, this, &Base::onRegistrationPageClicked);

    connect(registrationPage->getBackButton(), &QPushButton::clicked, this, &Base::onAuthPageClicked);
    connect(registrationPage->getEnterButton(), &QPushButton::clicked, this, &Base::onRegister);

//    screens->insertWidget(e_authorization, authorizationPage);
//    screens->insertWidget(0, profilePage);
    screens->insertWidget(0, visitorEventListPage);
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

void Base::onProfilePageClicked()
{

}

void Base::onProfile()
{

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
        screens->setCurrentIndex(e_profile);
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
