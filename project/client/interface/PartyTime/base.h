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
//    std::shared_ptr<PostService> postRequestHandler;
private slots:
    void onAuthPageClicked();
    void onEnter(); // check validation function
    void onRegistrationPageClicked();
    void onRegister(); // check validation function
    // void onProfilePageClicked();
    // void onProfile();
    // void onSettingsPageClicked();
    // void onSettings();
    // void onEventViewPageClicked();
    // void onEvent();
    // void onLoadingPageClicked();
    // void onLoading();
    // void onVisitorPageClicked();
    // void onVisitor();
    // void onOrganizerPageClicked();
    // void onOrganizer();
    // void onVisitorEventListPageClicked();
    // void onVisitorEventList();
    // void headerRedraw();
    // void navbarRedraw();
    // void formRedraw();
    // void eventListRedraw();
    // void eventItemRedraw();
    // void footerRedraw();
};
#endif // BASE_H
