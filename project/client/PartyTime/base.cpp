#include "base.h"
#include <QSvgWidget>

Base::Base(QWidget *parent)
    : QMainWindow(parent),
      screens(new QStackedWidget()),
      authorizationPage(new authorization()),
      registrationPage(new registration()),
      profilePage(),
      myEvents(new EventViewPage),
      visitorEventListPage(new VisitorEventListPage())
{
    setWindowTitle("PartyTime");

    screens->setObjectName("generalBackground");
    this->setCentralWidget(screens);

    // авторизация
    connect(authorizationPage->getEnterButton(), &QPushButton::clicked, this, &Base::onEnter);
    connect(authorizationPage->getRegistrationButton(), &QPushButton::clicked, this, &Base::onRegistrationPageClicked);

    // регистрация
    connect(registrationPage->getBackButton(), &QPushButton::clicked, this, &Base::onAuthPageClicked);
    connect(registrationPage->getEnterButton(), &QPushButton::clicked, this, &Base::onRegister);

    // главная
    connect(visitorEventListPage->navbar.getMainButton()->getButton(),  &QPushButton::clicked, this, &Base::onVisitorEventListPageClicked);
    connect(visitorEventListPage->navbar.getProfileButton()->getButton(),  &QPushButton::clicked, this, &Base::onProfilePageClicked);
    connect(visitorEventListPage->navbar.getEventsButton()->getButton(),  &QPushButton::clicked, this, &Base::onEventViewPageClicked);

    // профиль
    connect(profilePage.navbar.getMainButton()->getButton(),  &QPushButton::clicked, this, &Base::onVisitorEventListPageClicked);
    connect(profilePage.navbar.getProfileButton()->getButton(),  &QPushButton::clicked, this, &Base::onProfilePageClicked);
    connect(profilePage.navbar.getEventsButton()->getButton(),  &QPushButton::clicked, this, &Base::onEventViewPageClicked);
    connect(&profilePage, &ProfilePage::back, this, &Base::getPrev);

    // мои ивенты
    connect(myEvents->navbar.getMainButton()->getButton(),  &QPushButton::clicked, this, &Base::onVisitorEventListPageClicked);
    connect(myEvents->navbar.getProfileButton()->getButton(),  &QPushButton::clicked, this, &Base::onProfilePageClicked);
    connect(myEvents->navbar.getEventsButton()->getButton(),  &QPushButton::clicked, this, &Base::onEventViewPageClicked);

    screens->insertWidget(e_authorization, authorizationPage);
    screens->insertWidget(e_registration, registrationPage);
    screens->insertWidget(e_main, visitorEventListPage);
    screens->insertWidget(e_profile, &profilePage);
    screens->insertWidget(e_events, myEvents);
//    screens->insertWidget(0, visitorEventListPage);
//    screens->insertWidget(1, &profilePage);
//    screens->insertWidget(2, myEvents);
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
//    screens->setCurrentIndex(e_profile);
//    screens->setCurrentIndex(1);
    screens->setCurrentIndex(e_profile);
}

void Base::getPrev()
{
    screens->setCurrentIndex(screens->currentIndex() - 1);
}

void Base::onEventViewPageClicked()
{
//    screens->setCurrentIndex(2);
    screens->setCurrentIndex(e_events);
}

void Base::onVisitorEventListPageClicked()
{
    screens->setCurrentIndex(e_main);
//    screens->setCurrentIndex(0);
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

Base::~Base()
{
    delete authorizationPage;
    delete registrationPage;
    delete screens;
}
