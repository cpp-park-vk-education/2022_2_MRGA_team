#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <painter.hpp>

class authorization : public painter
{
   Q_OBJECT

public:
   explicit authorization(QWidget* parent = nullptr);
   ~authorization();
   QPushButton* getEnterButton();
   QPushButton* getRegistrationButton();

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

