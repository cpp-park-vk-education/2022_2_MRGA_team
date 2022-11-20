#pragma once

#include "Header.hpp"
#include "Navbar.hpp"
#include "EventList.hpp"
#include "footer.hpp"

class EventViewPage : public painter {
    Q_OBJECT
public:
    explicit EventViewPage(QWidget* parent = nullptr);
    // конструктор, который принимает список строк, которые укзаывают какого типа navbar создавать
    EventViewPage(const std::initializer_list<QString> typesList);
    EventViewPage(const QString& headerType, const QString& navbarType,
                  const QString& eventListType, const QString& footerType);
//    EventViewPage(const EventViewPage&) = delete;
//    EventViewPage& operator=(const EventViewPage&) = delete;
    ~EventViewPage();
    void redraw() {};
private:
    QVBoxLayout* mainLayout;
    Header header;
    Navbar navbar;
    EventList eventList;
    Footer footer;
};
