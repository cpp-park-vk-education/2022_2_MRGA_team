#include "profile.hpp"

#include <iostream>


ProfilePage::ProfilePage(QWidget *parent) : painter(parent),
    mainLayout(new QVBoxLayout(this))
{
    this->setObjectName("profilePage");
    this->set_interface_style();

    QHBoxLayout *titleContainer = new QHBoxLayout;
    backButton = new QPushButton();
    backButton->setStyleSheet("min-width: 20px; min-height: 20px; border-image: url(:/image/arrow_back.svg); background-repeat: no-repeat; background-position: center; border-style:none;");
    QLabel *titleLabel = new QLabel("Main");
    titleLabel->setStyleSheet("font-size: 30px; color: #ffffff;");
    titleLabel->setContentsMargins(16, 0, 16, 0);

    titleContainer->addWidget(backButton);
    titleContainer->setContentsMargins(0, 10, 5, 25);
    titleContainer->setAlignment(Qt::AlignLeft);
    titleContainer->addWidget(titleLabel);

    QLabel* gifka = new QLabel();
    QMovie* movie = new QMovie(":/image/setting_45px.gif");
    gifka->setMovie(movie);
    movie->start();
    titleContainer->addWidget(gifka);

//    Navbar* navbarFactory = new Navbar("", 3);
//    this->navbar = *navbarFactory->create("visitor");
//    this->navbar.setGeometry(this->x(), this->y(), 1440, 100);
//    mainLayout->addWidget(&this->navbar, 1, Qt::AlignTop | Qt::AlignCenter);
    mainLayout->addLayout(titleContainer, 0);


    QHBoxLayout* inputLayout = new QHBoxLayout();

    UiLabel* newLabel = new UiLabel("profileLabel", "MyLabel");
    inputLayout->addWidget(newLabel, Qt::AlignTop | Qt::AlignLeft);

    UiEdit* newEdit = new UiEdit("profileEdit", "Введите текст", "settingsInput");
    inputLayout->addWidget(newEdit, Qt::AlignTop | Qt::AlignLeft);

    mainLayout->addLayout(inputLayout);

    connect(backButton, &QPushButton::clicked, this, &ProfilePage::onBackPressed);
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

}

void ProfilePage::onBackPressed()
{
    emit back();
}

//void ProfilePage::back() {

//}

