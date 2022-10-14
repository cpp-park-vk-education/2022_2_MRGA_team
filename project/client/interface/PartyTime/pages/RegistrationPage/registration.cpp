#include "registration.hpp"

registration::registration(QWidget *parent)
    : painter(parent),
      registrationMainLayout(new QGridLayout(this)), headerLayout(new QHBoxLayout()), titleLayout(new QVBoxLayout()),
      formLayout(new QVBoxLayout()), buttonsLayout(new QVBoxLayout()),
      backButton(new QPushButton("назад")), appTitle(new QLabel(this)), appLogo(new QLabel(this)),
      email(new QLineEdit()), login(new QLineEdit()), password(new QLineEdit()), repeatPassword(new QLineEdit()), enterButton(new QPushButton("Зарегистрироваться"))
{    
    this->setObjectName("registration");
    registrationMainLayout->setSpacing(10);

    backButton->setObjectName("backButton");
    headerLayout->addWidget(backButton, 0);
    registrationMainLayout->addLayout(headerLayout, 0, 0, 1, 1, Qt::AlignTop | Qt::AlignLeft);

    appTitle->setObjectName("regAppTitle");
    appTitle->setText("PartyTime");
    appTitle->setFont(QFont("Times", 26));
    appTitle->setAlignment(Qt::AlignCenter);
    appTitle->setStyleSheet("color: #000000; font-weight: 1000; font-size: 48px; line-height: 59px;");

    appLogo->setObjectName("regAppLogo");
    appLogo->setGeometry(0, 0, 347, 347);
    appLogo->setStyleSheet("border-radius: 15px;");
    appLogo->setPixmap(QPixmap(":/image/tyanochka.png"));

    titleLayout->addWidget(appTitle);
    titleLayout->addWidget(appLogo);
    registrationMainLayout->addLayout(titleLayout, 1, 0, 1, 1, Qt::AlignCenter | Qt::AlignTop);

    email->setMaximumWidth(400);
    email->setObjectName("regEmail");
    QPalette pal = email->palette();
    pal.setColor(QPalette::PlaceholderText, QColor(0, 0, 0, 100));
    email->setPalette(pal);
    email->setPlaceholderText("Email");
    email->setFont(QFont("Times", -1, QFont::Bold));
    email->setStyleSheet("background-color: #babfd9; color: #fff; border-radius: 15px");

    login->setMaximumWidth(400);
    login->setObjectName("regLogin");
    login->setPalette(pal);
    login->setPlaceholderText("Login");
    login->setFont(QFont("Times", -1, QFont::Bold));
    login->setStyleSheet("background-color: #babfd9; color: #fff; border-radius: 15px");

    password->setMaximumWidth(400);
    password->setObjectName("regPassword");
    password->setPalette(pal);
    password->setPlaceholderText("Password");
    password->setEchoMode(QLineEdit::Password);
    password->setFont(QFont("Times", -1, QFont::Bold));
    password->setStyleSheet("background-color: #babfd9; color: #fff; border-radius: 15px");

    repeatPassword->setMaximumWidth(400);
    repeatPassword->setObjectName("regRepeatPassword");
    repeatPassword->setPalette(pal);
    repeatPassword->setPlaceholderText("Repeat password");
    repeatPassword->setEchoMode(QLineEdit::Password);
    repeatPassword->setFont(QFont("Times", -1, QFont::Bold));
    repeatPassword->setStyleSheet("background-color: #babfd9; color: #fff; border-radius: 15px");

    formLayout->addWidget(email);
    formLayout->addWidget(login);
    formLayout->addWidget(password);
    formLayout->addWidget(repeatPassword);
    registrationMainLayout->addLayout(formLayout, 2, 0, 1, 1, Qt::AlignCenter | Qt::AlignTop);

    buttonsLayout->setSpacing(0);
    enterButton->setObjectName("regEnterButton");
    enterButton->setMaximumWidth(200);

    buttonsLayout->addWidget(enterButton);
    registrationMainLayout->addLayout(buttonsLayout, 3, 0, 1, 1, Qt::AlignCenter | Qt::AlignTop);
}

QPushButton* registration::getBackButton()
{
    return backButton;
}

QPushButton* registration::getEnterButton()
{
    return enterButton;
}

registration::~registration() {
    delete registrationMainLayout;
    delete headerLayout;
    delete backButton;
    delete appTitle;
    delete appLogo;
    delete email;
    delete login;
    delete password;
    delete repeatPassword;
    delete enterButton;
    delete formLayout;
    delete buttonsLayout;
}
