#include "loading.hpp"

LoadingPage::LoadingPage(QWidget *parent) : painter(parent), layout(new QVBoxLayout())
{
    QLabel* gifka = new QLabel();
    QMovie* movie = new QMovie(":/image/setting_45px.gif");
    gifka->setStyleSheet("padding-top: 15px;");
    gifka->setMovie(movie);
}

LoadingPage::LoadingPage(const QString &loaderType, const QString &messageType) : layout(new QVBoxLayout())
{
    UiLabel* labelFactory = new UiLabel();
    this->loader = *(labelFactory->create(loaderType));
    this->message = *(labelFactory->create(messageType));

    layout->addWidget(&loader);
    layout->addWidget(&message);
}

LoadingPage::~LoadingPage()
{
    delete layout;
}

#include "loading.hpp"
