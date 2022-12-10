#pragma once // pragma once

#include "../painter.hpp"
#include <../styleHelper.hpp>
#include "Button.hpp"

class Navbar : public painter {
    Q_OBJECT
    friend class UiButton;
    friend class Navbar;
    friend class ProfilePage;

public:
    explicit Navbar(const QString& styleSheet = nullptr, size_t navbarSize = 0, QWidget* parent = nullptr);
    Navbar(const QString& mainBtnType, const QString& profileBtnType, const QString& eventsBtnType);
    Navbar(const UiButton& _mainBtn, const UiButton& _profileBtn, const UiButton& _eventsBtn); // констрктор для создания navbara visitor-a
    Navbar(const UiButton& _mainBtn, const UiButton& _profileBtn); // конструктор для создания Navbar-a organizer-a
    Navbar(const Navbar& other);
    Navbar& operator=(const Navbar&);
    ~Navbar();

    Navbar *create(const QString& objectType);

    void updateState(){}; // const std::initializer_list<QString>&
    UiButton* getMainButton() {return &mainButton;}
    UiButton* getProfileButton() {return &profileButton;}
    UiButton* getEventsButton() {return &eventsButton;}

private:
    QHBoxLayout* layout;
    UiButton mainButton;
    UiButton profileButton;
    UiButton eventsButton;
};
