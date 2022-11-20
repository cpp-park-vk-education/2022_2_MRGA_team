#pragma once // pragma once

#include "../painter.hpp"
#include "Button.hpp"

class Navbar : public painter {
    Q_OBJECT
    friend UiButton;
public:
    explicit Navbar(size_t navbarSize = 2, QWidget* parent = nullptr);
    Navbar(const UiButton& _mainBtn, const UiButton& _profileBtn, const UiButton& _eventsBtn, bool _state = true); // констрктор для создания navbara visitor-a
    Navbar(const UiButton& _mainBtn, const UiButton& _profileBtn, bool _state = true); // конструктор для создания Navbar-a organizer-a
    Navbar(const Navbar& other);
    Navbar& operator=(const Navbar&);
    ~Navbar();

    Navbar *create(const QString& objectType);

    bool getState(){return true;}
    void setState(){};

private:
    QHBoxLayout* layout;
    UiButton mainButton;
    UiButton profileButton;
    UiButton eventsButton;
    bool stateNavbar; // для внешних компонентов и дальнейшей перерисовки
};
