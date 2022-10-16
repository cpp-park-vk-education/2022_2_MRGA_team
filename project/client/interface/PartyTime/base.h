#ifndef BASE_H
#define BASE_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>
#include <string>
#include <exception>

#include "authorization.hpp"
#include "registration.hpp"
#include "profile.hpp"
//#include "settings.hpp"
#include "eventView.hpp"
#include "loading.hpp"
#include "organizer.hpp"
#include "visitor.hpp"
#include "visitorEventList.hpp"

enum pagesNumbers {
    e_authorization = 0,
    e_registration = 1,
    e_profile = 2
};


class Base : public QMainWindow
{
    Q_OBJECT

public:
    explicit Base(QWidget *parent = nullptr);
    ~Base();
private:
    QStackedWidget* screens;
    authorization* authorizationPage;
    registration* registrationPage;
//    profile* profilePage;
//    settings* settingsPage;
//    eventView* eventViewPage;
//    loading* loadingPage;
//    organizer* organizerPage;
//    visitor* visitorPage;
//    visitorEventList* visitorEventListPage;
private slots:
    void onAuthPageClicked();
    void onEnter();
    void onRegistrationPageClicked();
    void onRegister();
    // void onProfilePageClicked();
};
#endif // BASE_H
