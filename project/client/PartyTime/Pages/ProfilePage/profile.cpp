#include "profile.hpp"
#include <QSvgWidget>

ProfilePage::ProfilePage(QWidget *parent) : painter(parent),
    mainLayout(new QVBoxLayout(this))
{
    QHBoxLayout *titleContainer = new QHBoxLayout;
    mainLayout->addLayout(titleContainer);
    backButton = new QPushButton();
    backButton->setStyleSheet("min-width: 30px; max-height: 20px; border-image: url(:/image/arrow_back.svg); background-repeat: no-repeat; background-position: center; border-style:none;");
    QLabel *titleLabel = new QLabel("Settings");
    titleLabel->setStyleSheet("font-size: 30px; color: #ffffff; padding-top: 15px;");
    titleLabel->setContentsMargins(16, 0, 16, 0);

    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);

    titleContainer->setContentsMargins(0, 10, 5, 10);
    titleContainer->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    QLabel* gifka = new QLabel();
    QMovie* movie = new QMovie(":/image/setting_45px.gif");
    gifka->setStyleSheet("padding-top: 15px;");
    gifka->setMovie(movie);

    QHBoxLayout* formLayout = new QHBoxLayout();
    formLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(formLayout);

    this->leftForm = new EventForm("settingsInput", 5, "settingsButton", 1);
    formLayout->addWidget(this->leftForm);
    this->rightForm = new EventForm("settingsInputRight", 5, "settingsButton", 1);
    formLayout->addWidget(this->rightForm);

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
//    for (auto& input : form->inputList) {
//        input->edit;
//    }
}

