#include "footer.hpp"

Footer::Footer(QWidget *parent) : painter(parent)
{

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
