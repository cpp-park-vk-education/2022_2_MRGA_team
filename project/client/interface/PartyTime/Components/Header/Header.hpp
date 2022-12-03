#pragma once  // pragma once

#include "Label.hpp"
#include "Button.hpp"

class Header : public painter {
    Q_OBJECT
public:
    explicit Header(QWidget* parent = nullptr);
    Header(const QString& userAvatarType, const QString& appLogoType, const QString& stateButtonType);
    Header(const UiLabel& _userAvatar, const UiLabel& _appLogo, const UiButton& _stateButton);
    Header(const Header& other);
    Header& operator=(const Header&);
    ~Header();

    void updateState(){}; // const std::initializer_list<QString>&
    Header* create(const QString& objectType);
private:
    QHBoxLayout* layout;
    UiLabel userAvatar;
    UiLabel appLogo;
    UiButton stateButton; // кнопки смены режима организатора на посетителя
};
