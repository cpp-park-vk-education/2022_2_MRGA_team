#include "profile.hpp"

#include <iostream>

ProfilePage::ProfilePage(QWidget *parent) : painter(parent),
    mainLayout(new QVBoxLayout(this))
{
    this->setObjectName("profilePage");
    this->set_interface_style();

    Navbar* navbarFactory = new Navbar();
    this->navbar = *navbarFactory;
    mainLayout->addWidget(&this->navbar, 1, Qt::AlignTop);
}

ProfilePage::ProfilePage(const QString &headerType, const QString &navbarType,
                         const QString &_leftForm, const QString &_rightForm,
                         const QString &_userAvatar, const QString &_saveBtn,
                         const QString &_footer)
{
    if (headerType == " " && navbarType == "" && _leftForm == " " && _rightForm == "" && _userAvatar == "" && _saveBtn == "" && _footer == "") {}
}

ProfilePage::~ProfilePage()
{
    delete mainLayout;
}

void ProfilePage::set_interface_style()
{
//    this->setStyleSheet(stylehelper::profileBackgroundStyle());
// ПОПЫТКИ ИЗМЕНИТЬ Background у ребенка. ДОЛЖНО БЫТЬ В КОНСТРУКОРЕ
//    this->navbar.setStyleSheet("border: 1px solid black; max-width: 900px; max-height: 300px; border-radius: 20px;");
//    this->navbar.setProperty("cssClass", "large");
//    this->navbar.setStyleSheet(".large {background-color: black;}");
}
