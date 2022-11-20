#include "profile.hpp"

ProfilePage::ProfilePage(QWidget *parent) : painter(parent)
{

}

ProfilePage::ProfilePage(const QString &headerType, const QString &navbarType,
                         const QString &_leftForm, const QString &_rightForm,
                         const QString &_userAvatar, const QString &_saveBtn,
                         const QString &_footer)
{
    Header* headerFactory = new Header();
    this->header = *(headerFactory->create(headerType));
    delete headerFactory;
    headerFactory = nullptr;

    Navbar* navbarFactory = new Navbar();
    this->navbar = *(navbarFactory->create(navbarType));
    delete navbarFactory;
    navbarFactory = nullptr;

    if (_leftForm == " " && _rightForm == "" &&
            _userAvatar == "" && _saveBtn == "" && _footer == "") {

    }
}

ProfilePage::~ProfilePage()
{

}
