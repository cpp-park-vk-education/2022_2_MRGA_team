#include "profile.hpp"
#include <QSvgWidget>

ProfilePage::ProfilePage(QWidget *parent) : painter(parent),
    mainLayout(new QVBoxLayout(this))
{
    this->setObjectName("profilePage");
    this->set_interface_style();

    QHBoxLayout *titleContainer = new QHBoxLayout;
    backButton = new QPushButton();
    backButton->setStyleSheet("min-width: 30px; min-height: 20px; border-image: url(:/image/back-arrow.png); background-repeat: no-repeat; background-position: center; border-style:none;");
    QLabel *titleLabel = new QLabel("Settings");
    titleLabel->setStyleSheet("font-size: 30px; color: #000000;");
    titleLabel->setContentsMargins(16, 0, 16, 0);

    titleContainer->addWidget(backButton);
    titleContainer->setContentsMargins(0, 10, 5, 25);
    titleContainer->setAlignment(Qt::AlignCenter);
    titleContainer->addWidget(titleLabel);

    QLabel* gifka = new QLabel();
    QMovie* movie = new QMovie(":/image/setting_45px.gif");
    gifka->setMovie(movie);
    movie->start();
    titleContainer->addWidget(gifka);
    mainLayout->addLayout(titleContainer, 0);


    QHBoxLayout* inputLayout = new QHBoxLayout();
    inputLayout->setContentsMargins(200, 0, 0, 0);
    mainLayout->addLayout(inputLayout, 1);

    UiLabel* newLabel = new UiLabel("profileLabel", "MyLabel");
    inputLayout->addWidget(newLabel, 1, Qt::AlignTop | Qt::AlignLeft);

    UiEdit* newEdit = new UiEdit("profileEdit", "Введите текст", "settingsInput"); // третий параметр для placeholder-a
    inputLayout->addWidget(newEdit, 5, Qt::AlignTop | Qt::AlignLeft);

    QHBoxLayout* inputLayout1 = new QHBoxLayout();
    inputLayout1->setContentsMargins(200, 0, 0, 0);
    mainLayout->addLayout(inputLayout1, 2);

    UiLabel* newLabel1 = new UiLabel("profileLabel", "MyLabel");
    inputLayout1->addWidget(newLabel1, 1, Qt::AlignTop | Qt::AlignLeft);

    UiEdit* newEdit1 = new UiEdit("profileEdit", "Введите текст", "settingsInput"); // третий параметр для placeholder-a
    inputLayout1->addWidget(newEdit1, 5, Qt::AlignTop | Qt::AlignLeft);

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

