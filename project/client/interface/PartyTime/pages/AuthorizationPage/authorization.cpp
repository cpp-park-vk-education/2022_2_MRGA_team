#include "authorization.hpp"

authorization::authorization(QWidget* parent) : painter(parent),
    authMainLayout(new QGridLayout(this)), titleLayout(new QVBoxLayout()), formLayout(new QVBoxLayout()), buttonsLayout(new QVBoxLayout()),
    appTitle(new QLabel(this)), appLogo(new QLabel(this)), login(new QLineEdit()), password(new QLineEdit()), enterButton(new QPushButton("Войти")),
    registrationButton(new QPushButton("Создать аккаунт"))
{
    this->setObjectName("authorizationPage");
    authMainLayout->setSpacing(10);

    appTitle->setObjectName("appTitle");
    appTitle->setText("PartyTime");
    appTitle->setFont(QFont("Times", 26));
    appTitle->setAlignment(Qt::AlignCenter);
    appTitle->setStyleSheet("color: #000000; font-weight: 1000; font-size: 48px; line-height: 59px;");

    appLogo->setObjectName("appLogo");
    appLogo->setGeometry(0, 0, 347, 347);
    appLogo->setStyleSheet("border-radius: 15px;");
    appLogo->setPixmap(QPixmap(":/image/tyanochka.png"));

    titleLayout->addWidget(appTitle);
    titleLayout->addWidget(appLogo);

    authMainLayout->addLayout(titleLayout, 0, 0, 1, 1, Qt::AlignCenter);

    formLayout->setSpacing(8);

    login->setMaximumWidth(400);
    login->setObjectName("login");

    QPalette pal = login->palette();
    pal.setColor(QPalette::PlaceholderText, QColor(0, 0, 0, 100));
    login->setPalette(pal);
    login->setPlaceholderText("Login");
    login->setFont(QFont("Times", -1, QFont::Bold));
    login->setStyleSheet("background-color: #babfd9; color: #fff; border-radius: 15px");

    password->setMaximumWidth(400);
    password->setObjectName("password");
    password->setPalette(pal);
    password->setPlaceholderText("Password");
    password->setEchoMode(QLineEdit::Password);
    password->setFont(QFont("Times", -1, QFont::Bold));
    password->setStyleSheet("background-color: #babfd9; color: #fff; border-radius: 15px");

    formLayout->addWidget(login);
    formLayout->addWidget(password);

    authMainLayout->addLayout(formLayout, 1, 0, 1, 1, Qt::AlignCenter);

    buttonsLayout->setSpacing(0);

    enterButton->setObjectName("enterButton");
    enterButton->setMaximumWidth(200);

    registrationButton->setObjectName("registrationButton");
    registrationButton->setMaximumWidth(200);

    buttonsLayout->addWidget(enterButton);
    buttonsLayout->addWidget(registrationButton);

    authMainLayout->addLayout(buttonsLayout, 2, 0, 1, 1, Qt::AlignCenter | Qt::AlignTop);

}

authorization::~authorization() {
    delete appLogo;
    delete appTitle;
    delete login;
    delete password;
    delete enterButton;
    delete registrationButton;
    delete authMainLayout;
    delete titleLayout;
    delete formLayout;
    delete login;
    delete password;
    delete buttonsLayout;
    delete enterButton;
    delete registrationButton;
}

QPushButton* authorization::getEnterButton() {
    return enterButton;
}

QPushButton *authorization::getRegistrationButton() {
    return registrationButton;
}

