#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <painter.hpp>

class registration : public painter
{
    Q_OBJECT
public:
    friend class Base;
    explicit registration(QWidget *parent = nullptr);
    ~registration();

    QPushButton* getBackButton();
    QPushButton* getEnterButton();


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
