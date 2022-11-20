#pragma once

#include "Header.hpp"
#include "Navbar.hpp"
#include "EventList.hpp"
#include "footer.hpp"

class OrganizerPage : public painter {
    Q_OBJECT
public:
    explicit OrganizerPage(QWidget* parent = nullptr);
    // конструктор, который принимает список строк, которые укзаывают какого типа navbar создавать
    OrganizerPage(const std::initializer_list<QString> typesList);
    OrganizerPage(const QString& headerType, const QString& navbarType,
                  const QString& eventListType, const QString& footerType);
//    OrganizerPage(const OrganizerPage&) = delete;
//    OrganizerPage& operator=(const OrganizerPage&) = delete;
    ~OrganizerPage();
    void redraw() {};
private:
    QVBoxLayout* mainLayout;
    Header header;
    Navbar navbar;
    EventList eventList;
    Footer footer;
};
