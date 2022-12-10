 #pragma once // pragma once

#include "EventForm.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include <../styleHelper.hpp>
#include "Header.hpp"
#include "Navbar.hpp"
#include "footer.hpp"

class ProfilePage : public painter {
    Q_OBJECT
    friend class Base;
public:
    explicit ProfilePage(QWidget* parent = nullptr);
    ProfilePage(const QString& _header, const QString& _navbar,
                const QString& _leftForm = "default", const QString& _rightForm = "default",
                const QString& _userAvatar = "default", const QString& _saveBtn = "default", const QString& _footer = "default"); // параметр const std::initisializer_list<QSting>
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
    UiButton* saveButton;

    Footer footer;
    QAudioOutput* m_audioOuput;
    QFile* m_musicPath;

    void set_interface_style();

private slots:
//    void onBackPressed();

signals:
    void back(); // int numberOfPrevPage

};
