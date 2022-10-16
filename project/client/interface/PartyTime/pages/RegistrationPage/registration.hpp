#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <painter.hpp>

#define MIN_CHAR_SIZE_IN_INPUT 6
#define MIN_CHAR_SIZE_IN_PASSWORD 12

class registration : public painter
{
    Q_OBJECT
public:
    friend class Base;
    explicit registration(QWidget *parent = nullptr);
    ~registration();

    QPushButton* getBackButton();
    QPushButton* getEnterButton();

    //   validate methods
    bool isIncorrectEmail(); // daniil-zzz@mail.ru - корректный email
    bool validateLogin(); // Zela_28TP - корректный логин
    bool validatePassword(); // Pink@floY_D.2022 - надежный пароль
    bool validateRepeatPasswordField(); // Pink@floY_D.2022 - корректное повторение пароля
    bool isUserExist();

    //   warning methods
    void emailWarning();
    void loginWarning();
    void passwordWarning();
    void passwordRepeatWarning();
    void userExistWarning();

    bool checkUserInputData();

    //   clear fields methods
    void emailClear() {this->email->setText("");}
    void loginClear() {this->login->setText("");}
    void passwordClear() {this->password->setText("");}
    void passwordRepeatClear() {this->repeatPassword->setText("");}

private:
    QGridLayout* registrationMainLayout;
    QHBoxLayout* headerLayout;
    QVBoxLayout* titleLayout;
    QVBoxLayout* formLayout;
    QVBoxLayout* buttonsLayout;

    QPushButton* backButton;

    QLabel* appTitle;
    QLabel* appLogo;

    QLineEdit* email;
    QLineEdit* login;
    QLineEdit* password;
    QLineEdit* repeatPassword;

    QPushButton* enterButton;
};

#endif // REGISTRATION_H
