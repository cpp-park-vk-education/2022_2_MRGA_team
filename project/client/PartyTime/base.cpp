#include "base.h"
#include <QSvgWidget>

Base::Base(QWidget *parent)
    : QMainWindow(parent),
      screens(new QStackedWidget()),
      authorizationPage(new authorization()),
      registrationPage(new registration()),
      profilePage(),
      myEvents(new EventViewPage),
      visitorEventListPage(new VisitorEventListPage()),
      settingsPage(new settings),
      party(PartyTimeConnector::default_implementation("0.0.0.0", "8081"))
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
    connect(visitorEventListPage->navbar.getEventsButton()->getButton(),  &QPushButton::clicked, this, &Base::onEventViewPageClicked);
    connect(visitorEventListPage->navbar.getLogoutButton()->getButton(),  &QPushButton::clicked, this, &Base::onAuthPageClicked);
    connect(visitorEventListPage->comboBox, &QComboBox::currentTextChanged, this, &Base::onVisitorEventListPageClicked);

    // профиль
    connect(profilePage.navbar.getMainButton()->getButton(),  &QPushButton::clicked, this, &Base::onVisitorEventListPageClicked);
    connect(profilePage.navbar.getEventsButton()->getButton(),  &QPushButton::clicked, this, &Base::onEventViewPageClicked);
    connect(profilePage.navbar.getLogoutButton()->getButton(),  &QPushButton::clicked, this, &Base::onAuthPageClicked);
    connect(&profilePage, &ProfilePage::back, this, &Base::getPrev);

    // мои ивенты
    connect(myEvents->navbar.getMainButton()->getButton(),  &QPushButton::clicked, this, &Base::onVisitorEventListPageClicked);
    connect(myEvents->navbar.getProfileButton()->getButton(),  &QPushButton::clicked, this, &Base::onProfilePageClicked);
    connect(myEvents->navbar.getLogoutButton()->getButton(),  &QPushButton::clicked, this, &Base::onAuthPageClicked);

    screens->insertWidget(e_authorization, authorizationPage);
    screens->insertWidget(e_registration, registrationPage);
    screens->insertWidget(e_events, myEvents);
    screens->insertWidget(e_main, visitorEventListPage);
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
    }
    catch (const char* exception) {
        std::cout << "Error: " << exception << "\n";
        screens->setCurrentIndex(e_registration);
        return;
    }

        // структура user-a
        User curUser = {this->registrationPage->getNickNameText().toStdString(),
                    this->registrationPage->getPasswordText().toStdString(),
                    this->registrationPage->getEmailText().toStdString(),
                    this->registrationPage->getBirthDateText().toStdString(),};

        // зарегистрировали
        auto resultat = party->auth->signup(curUser);

        // Ошибка
        if (resultat.result.failed()) {
            std::cout << resultat.result.message() << std::endl;
            QMessageBox errorForm;
            errorForm.setText(QString::fromStdString(resultat.result.message()));
            errorForm.exec();
            return;
        }


        std::cout << "User id: " << curUser.id << std::endl;

        screens->setCurrentIndex(e_main);
        registrationPage->emailClear();
        registrationPage->loginClear();
        registrationPage->passwordClear();
        registrationPage->passwordRepeatClear();
        registrationPage->birthDateClear();
}

void Base::onProfilePageClicked()
{

    screens->setCurrentIndex(e_profile);
}

void Base::getPrev()
{
    screens->setCurrentIndex(e_main);
}

void Base::onEventViewPageClicked()
{
    screens->setCurrentIndex(e_events);


}

void Base::onVisitorEventListPageClicked()
{
    screens->setCurrentIndex(e_main);
    visitorEventListPage->eventList->clearEventList();
    visitorEventListPage->updateEvents();
    std::cout << visitorEventListPage->comboBox->currentText().toStdString() << std::endl;
}

void Base::onSettingsPageClicked()
{
    screens->setCurrentIndex(e_settings);
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
    } catch (const char* exception) {
            std::cout << "Error: " << exception << "\n";
            screens->setCurrentIndex(e_authorization);
            return;
    }

    // структура user-a
    User curUser(this->authorizationPage->getNickName(), this->authorizationPage->getPassword(), "", ""); // TODO: не должно быть пустых полей

    // запрос на авторизацию
    auto resultat = party->auth->login(curUser);

    // Ошибка
    if (resultat.result.failed()) {
        std::cout << resultat.result.message() << std::endl;
        QMessageBox errorForm;
        errorForm.setText(QString::fromStdString(resultat.result.message()));
        errorForm.exec();
        return;
    }

    screens->setCurrentIndex(e_main);
    authorizationPage->loginClear();
    authorizationPage->passwordClear();
}

Base::~Base()
{
    delete authorizationPage;
    delete registrationPage;
    delete screens;
}
