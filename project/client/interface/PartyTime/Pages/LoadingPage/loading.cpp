#include "loading.hpp"

LoadingPage::LoadingPage(QWidget *parent) : painter(parent), layout(new QVBoxLayout())
{

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
