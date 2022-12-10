#include "registration.hpp"
#include <iostream>

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

static bool checkForbiddenCharacters(char& curSymbol) {
    switch (curSymbol) {
        case ' ':
            return true;
        case ';':
            return true;
        case '"':
            return true;
        case '/':
            return true;
        case '?':
            return true;
        case '!':
            return true;
    }
    return false;
}

bool registration::isIncorrectEmail()
{
    std::string userEmail = this->email->text().toStdString();
    bool incorrectValue = true;

    if (userEmail.at(userEmail.size() - 3) != '.' || userEmail.at(0) == '.') {
        return incorrectValue;
    }
    if (userEmail.at(userEmail.size() - 1) == '@' || userEmail.at(0) == '@') {
        return incorrectValue;
    }

    size_t specialСharacterСounter = 0;

    for (auto& elem : userEmail) {
        if (elem >= 'A' && elem <= 'Z') {
            incorrectValue = false;
        } else if (elem >= 'a' && elem <= 'z') {
            incorrectValue = false;
        } else if (elem >= '0' && elem <= '9') {
            incorrectValue = false;
        } else if (elem == '-' || elem == '_' || elem == '.') {
            incorrectValue = false;
        } else if (elem == '@') {
            ++specialСharacterСounter;
        } else {
            return incorrectValue;
        }

        incorrectValue = true;
    }

    incorrectValue = false;

//    если данные некорректны, то функция возвращает true
    if (specialСharacterСounter != 1) {
        return true;
    }
    if (userEmail.substr(userEmail.find("@") + 1) != "mail.ru") {
        return true;
    }
    if (userEmail.find("..") != std::string::npos) {
        return true;
    }

    return incorrectValue;
}

bool registration:: validateLogin() {
    std::string userInput = this->login->text().toStdString();
    bool inCorrectValue = false;

    if (userInput.at(userInput.size() - 1) == '.') {
        inCorrectValue = true;
        return inCorrectValue;
    }

    size_t underscoreCounter = 0;

    for (auto& elem : userInput) {

        inCorrectValue = checkForbiddenCharacters(elem);

        switch(elem) {
            case '@':
                inCorrectValue = true;
                break;
            case ',':
                inCorrectValue = true;
                break;
        }

        if (inCorrectValue == true) {
            break;
        }

        if (elem == '_') {
            ++underscoreCounter;
        }
    }

    if (underscoreCounter != 1) {
        inCorrectValue = true;
    }

    if (userInput.size() < MIN_CHAR_SIZE_IN_INPUT) {
        inCorrectValue = true;
    }

    return inCorrectValue;
}

bool registration::validatePassword()
{
    std::string userInputPassword = this->password->text().toStdString();
    bool inCorrectValue = false;

    size_t numbersCounter = 0;
    size_t capsCounter = 0;
    size_t underscoreCounter = 0;
    size_t mainSimbolCounter = 0;

    for (auto& elem : userInputPassword) {
        inCorrectValue = checkForbiddenCharacters(elem);

//        обязательные символы
        if (elem == '_') {
            ++underscoreCounter;
        }

        if (elem >= 'A' && elem <= 'Z') {
            ++capsCounter;
        }

        if (elem >= '0' && elem <= '9') {
            ++numbersCounter;
        }

        if (elem == '@') {
            ++mainSimbolCounter;
        }

    }

    if (mainSimbolCounter != 1) {
        inCorrectValue = true;
    }

    if (numbersCounter == 0) {
        inCorrectValue = true;
    }

    if (capsCounter == 0) {
        inCorrectValue = true;
    }

    if (underscoreCounter == 0) {
        inCorrectValue = true;
    }

    if (userInputPassword.size() < MIN_CHAR_SIZE_IN_PASSWORD) {
        inCorrectValue = true;
    }

    return inCorrectValue;
}

bool registration::validateRepeatPasswordField()
{
    if (this->password->text().toStdString() == this->repeatPassword->text().toStdString()) {
        return false;
    }
    return true;
}

bool registration::isUserExist()
{
    std::string userEmail = this->email->text().toStdString();
    std::string userLogin = this->login->text().toStdString();

//    bool res = POST(userEmail, userLogin);
    return true;
}

void registration::emailWarning()
{
    QMessageBox::warning(this, "Warning", "Email entered incorrectly");
}

void registration::loginWarning()
{
    QMessageBox::warning(this, "Warning", "Login is invalid. Login must contain at least 6 characters without spaces(including '.' and '_' not as like the last symbol). Login can contain letters, numbers and symbols");
}

void registration::passwordWarning()
{
    QMessageBox::warning(this, "Warning", "Password is invalid or insecure. The password must be at least 12 characters long without spaces and contain letters, numbers, uppercase letters and symbols. The password must contain the characters '.', '_', '@'");
}

void registration::passwordRepeatWarning()
{
    QMessageBox::warning(this, "Warning", "Password don't match");
}

void registration::userExistWarning()
{
    QMessageBox::warning(this, "Warning", "User with such data already exists");
}

bool registration::checkUserInputData()
{
    bool isIncorrectUserData = false;

    if (this->email->text().toStdString().empty() || this->login->text().toStdString().empty()
            || this->password->text().toStdString().empty() || this->repeatPassword->text().toStdString().empty()) {
        QMessageBox::warning(this, "Warning", "Required fields to fill in!");
        isIncorrectUserData = true;
        return isIncorrectUserData;
    }

    if (isIncorrectEmail()) {
            isIncorrectUserData = true;
            this->emailWarning();
            return isIncorrectUserData;
    }

    if (validateLogin()) {
            isIncorrectUserData = true;
            this->loginWarning();
            return isIncorrectUserData;
    }

    if (validatePassword()) {
        isIncorrectUserData = true;
        this->passwordWarning();
        return isIncorrectUserData;
    }

    if (validateRepeatPasswordField()) {
        isIncorrectUserData = true;
        this->passwordRepeatWarning();
        return isIncorrectUserData;
    }

//    if (isUserExist()) {
//        isIncorrectUserData = true;
//        this->userExistWarning();
//        return isIncorrectUserData;
//    }

    return isIncorrectUserData;
}

registration::~registration() {
    delete email;
    delete login;
    delete password;
    delete repeatPassword;
    delete backButton;
    delete appTitle;
    delete appLogo;
    delete enterButton;
    delete titleLayout;
    delete buttonsLayout;
    delete headerLayout;
    delete formLayout;
    delete registrationMainLayout;
}
