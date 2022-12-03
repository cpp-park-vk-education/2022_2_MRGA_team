#include "styleHelper.hpp"
#include <QColor>

QString stylehelper::profileBackgroundStyle()
{
    return "#profilePage {background-image: url(:/image/MainLayout.png);"
           "}";
//    return "ProfilePage#profilePage {"
//           "background-image: url("/image/MainLayout.png");"
//     "}";
}

QString stylehelper::navbarBackgroundStyle()
{
    return "Navbar#clientNavbar {"
           "min-width: 600px;"
           "max-height: 200px;"
           "font-size: 24px;"
           "border-radius: 15px;"
           "color: #000000;"
           "background-color: rgba(79, 39, 193, 1);"
     "}";
}
