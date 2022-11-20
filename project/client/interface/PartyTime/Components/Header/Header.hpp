#pragma once  // pragma once

#include "Label.hpp"
#include "Button.hpp"

class Header : public painter {
    Q_OBJECT
public:
    explicit Header(QWidget* parent = nullptr);
    Header(const UiLabel& _userAvatar, const UiLabel& _appLogo, const UiButton& _stateButton, bool _state);
    Header(const Header& other);
    Header& operator=(const Header&);
    ~Header();

    void setState(bool _state){headerState = _state;}
    Header* create(const QString& objectType);
private:
    QHBoxLayout* layout;
    UiLabel userAvatar;
    UiLabel appLogo;
    UiButton stateButton; // кнопки смены режима организатора на посетителя
    bool headerState; // будет несколько вариаций хедера
};
