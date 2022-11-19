#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <painter.hpp>
#include <iostream>
#include <string>

#define MIN_CHAR_SIZE_IN_INPUT 6
#define MIN_CHAR_SIZE_IN_PASSWORD 12

class authorization : public painter
{
   Q_OBJECT

public:
   explicit authorization(QWidget* parent = nullptr);
   ~authorization();
   QPushButton* getEnterButton();
   QPushButton* getRegistrationButton();

//   validate methods
   bool validateLogin(); // Zela_28TP - корректный логин
   bool validatePassword(); // Pink@floY_D.2022 - надежный пароль
   bool isUserPasswordMatchUser();

//   warning methods
   void loginWarning();
   void passwordWarning();
   void userMatchWarning();

//   метод будет вызываться при клике на кнопку входа. Если данные корректны переходим к экрану регистрации
   bool checkUserInputData();

//   clear fields methods
   void loginClear() {this->login->setText("");}
   void passwordClear() {this->password->setText("");}

private:
   QGridLayout* authMainLayout;
   QVBoxLayout* titleLayout;
   QVBoxLayout* formLayout;
   QVBoxLayout* buttonsLayout;

   QLabel* appTitle;
   QLabel* appLogo;

   QLineEdit* login;
   QLineEdit* password;
   QPushButton* enterButton;
   QPushButton* registrationButton;

private slots:

};

#endif // AUTHORIZATION_H

