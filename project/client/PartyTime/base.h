#ifndef BASE_H
#define BASE_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>
#include <string>
#include <exception>
#include <memory>

#include "authorization.hpp"
#include "registration.hpp"
#include "profile.hpp"
#include "eventView.hpp"
#include "loading.hpp"
#include "organizer.hpp"
#include "visitor.hpp"
#include "visitorEventList.hpp"
#include "settings.hpp"

enum pagesNumbers {
    e_authorization = 0,
    e_registration = 1,
    e_main = 2,
    e_events = 3,
    e_profile = 4,
    e_settings = 5
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
    ProfilePage profilePage;
    EventViewPage* myEvents;
    LoadingPage* loadingPage;
    OrganizerPage* organizerPage;
    VisitorPage* visitorPage;
    VisitorEventListPage* visitorEventListPage;
    settings* settingsPage;

private slots:
    void onAuthPageClicked();
    void onEnter();
    void onRegistrationPageClicked();
    void onRegister();
    void onProfilePageClicked();
    void getPrev();
    void onEventViewPageClicked();
    void onVisitorEventListPageClicked();
    void onSettingsPageClicked();
};

#endif // BASE_H
