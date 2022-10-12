#include "authorization.hpp"

authorization::authorization(QWidget* parent) : painter(parent)
{
    this->setObjectName("authorizationPage");
    QGridLayout* authorization_layout = new QGridLayout(this);
    authorization_layout->setSpacing(10);

    QVBoxLayout* title_authorization_layout = new QVBoxLayout;
    QLabel* m_page_title = new QLabel("Вход");
    m_page_title->setObjectName("pageTitle");
    m_page_title->setMaximumSize(100, 100);

    authorization_layout->addWidget(m_page_title);
}

authorization::~authorization() {

}


