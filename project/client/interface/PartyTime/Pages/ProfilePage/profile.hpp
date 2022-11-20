#pragma once // pragma once

#include "EventForm.hpp"
#include "Button.hpp"
#include "Label.hpp"

#include "Header.hpp"
#include "Navbar.hpp"
#include "footer.hpp"

class ProfilePage : public painter {
    Q_OBJECT

public:
    explicit ProfilePage(QWidget* parent);
    ProfilePage(const QString& _header = "default", const QString& _navbar = "default",
                const QString& _leftForm = "default", const QString& _rightForm = "default",
                const QString& _userAvatar = "default", const QString& _saveBtn = "default", const QString& _footer = "default");
    ~ProfilePage();

    void redraw() {}; // параметр const std::initisializer_list<QSting>
private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* contentLayout;
    QVBoxLayout* leftSide;
    QVBoxLayout* rightSide;

    Header header;
    Navbar navbar;
    EventForm leftForm;
    EventForm rightForm;

    UiLabel userAvatar;
    UiButton saveButton;

    Footer footer;
};
