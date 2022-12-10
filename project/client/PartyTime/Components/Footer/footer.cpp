#include "footer.hpp"

Footer::Footer(QWidget *parent) : painter(parent)
{

}

Footer::Footer(const Footer &other) : painter(new QWidget)
{
    this->mainLayout = other.mainLayout;
}

Footer &Footer::operator=(const Footer &other)
{
    this->mainLayout = other.mainLayout;
    return *this;
}

Footer::~Footer()
{

}

Footer *Footer::create(const QString &typeObject)
{
    if (typeObject == "default") {
        return new Footer();
    }
    return new Footer();
}
