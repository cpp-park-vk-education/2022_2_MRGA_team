#include "authorization.hpp"

authorization::authorization(QWidget* parent) : painter(parent),
    authMainLayout(new QGridLayout(this)), titleLayout(new QVBoxLayout()), formLayout(new QVBoxLayout()), buttonsLayout(new QVBoxLayout()),
    appTitle(new QLabel()), appLogo(new QLabel(this)), login(new QLineEdit()), password(new QLineEdit()), enterButton(new QPushButton("Войти")),
    registrationButton(new QPushButton("Создать аккаунт"))
{
    this->setObjectName("authorizationPage");
    authMainLayout->setSpacing(10);

    appTitle->setText("PartyTime");
    appTitle->setFont(QFont("Times", 26));
    appTitle->setAlignment(Qt::AlignCenter);
    appTitle->setStyleSheet("color: #000000; font-weight: 1000; font-size: 48px; line-height: 59px;");

    appLogo->setGeometry(0, 0, 347, 347);
    appLogo->setStyleSheet("border-radius: 15px;");
    appLogo->setPixmap(QPixmap(":/image/PartyTimeLogo.png"));

    titleLayout->setContentsMargins(0, 100, 0, 0);

    titleLayout->addWidget(appTitle);
    titleLayout->addWidget(appLogo);
    authMainLayout->addLayout(titleLayout, 0, 0, 1, 1, Qt::AlignCenter);

    login->setMaximumWidth(400);
    login->setObjectName("login");

    QPalette pal = login->palette();
    pal.setColor(QPalette::PlaceholderText, QColor(0, 0, 0, 100));
    login->setPalette(pal);
    login->setPlaceholderText("Login");
    login->setFont(QFont("Times", -1, QFont::Bold));
    login->setStyleSheet("background-color: #babfd9; color: #fff; border-radius: 15px");
    QIcon icoLogin(":/image/user.png");
    login->addAction(icoLogin, QLineEdit::LeadingPosition);

    password->setMaximumWidth(400);
    password->setObjectName("password");
    password->setPalette(pal);
    password->setPlaceholderText("Password");
    password->setEchoMode(QLineEdit::Password);
    password->setFont(QFont("Times", -1, QFont::Bold));
    password->setStyleSheet("background-color: #babfd9; color: #fff; border-radius: 15px");
    QIcon icoPassword(":/image/lock.png");
    password->addAction(icoPassword, QLineEdit::LeadingPosition);

    formLayout->addWidget(login, Qt::AlignTop);
    formLayout->addWidget(password, Qt::AlignTop);

    authMainLayout->addLayout(formLayout, 1, 0, 1, 1, Qt::AlignCenter | Qt::AlignTop);

    enterButton->setObjectName("enterButton");
    enterButton->setMaximumWidth(200);

    registrationButton->setObjectName("registrationButton");
    registrationButton->setMaximumWidth(200);

    buttonsLayout->addWidget(enterButton, Qt::AlignTop);
    buttonsLayout->addWidget(registrationButton, Qt::AlignTop);

    authMainLayout->addLayout(buttonsLayout, 2, 0, Qt::AlignCenter | Qt::AlignTop);
}

authorization::~authorization() {
    delete appTitle;
    delete appLogo;
    delete login;
    delete password;
    delete enterButton;
    delete registrationButton;

    delete titleLayout;
    delete formLayout;
    delete buttonsLayout;
    delete authMainLayout;
}

QPushButton* authorization::getEnterButton() {
    return enterButton;
}

QPushButton* authorization::getRegistrationButton() {
    return registrationButton;
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

bool authorization::validateLogin() {
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

bool authorization::validatePassword()
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

bool authorization::isUserPasswordMatchUser()
{
    std::string userLogin = this->login->text().toStdString();
    std::string userPassword = this->password->text().toStdString();

//    POST(userLogin, userPassword); - если пользователь существует и пароль соотвествует логину возвращаются данные иначе возвращается nullptr допустим

    return false;
}

void authorization::loginWarning()
{
    QMessageBox::warning(this, "Warning", "Login is invalid. Login must contain at least 6 characters without spaces(including '.' and '_' not as like the last symbol). Login can contain letters, numbers and symbols");
}

void authorization::passwordWarning()
{
    QMessageBox::warning(this, "Warning", "Password is invalid or insecure. The password must be at least 12 characters long without spaces and contain letters, numbers, uppercase letters and symbols. The password must contain the characters '.', '_', '@'");
}

void authorization::userMatchWarning()
{
    QMessageBox::warning(this, "Warning", "Password doesn't match username");
}

bool authorization::checkUserInputData() {
    bool isIncorrectUserData = false;

    if (this->login->text().toStdString() == "" || this->password->text().toStdString() == "") {
        QMessageBox::warning(this, "Warning", "Required fields to fill in!");
        isIncorrectUserData = true;
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

    if (isUserPasswordMatchUser()) {
        isIncorrectUserData = true;
        this->userMatchWarning();
        return isIncorrectUserData;
    }

    return isIncorrectUserData;
}
