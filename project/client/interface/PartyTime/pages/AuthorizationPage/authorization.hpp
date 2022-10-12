#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <painter.hpp>

class authorization : public painter
{
   Q_OBJECT

public:
   explicit authorization(QWidget* parent = nullptr);
   ~authorization();
   QPushButton* get_enter_button();
   QPushButton* get_registration_button();

private:
   QLabel *logo;
   QLabel* appTitle;

   QLineEdit* login;
   QLineEdit* password;
   QPushButton* enterButton;
   QPushButton* registrationButton;

private slots:
};

#endif // AUTHORIZATION_H

