#pragma once

#include "Header.hpp"
#include "Navbar.hpp"
#include "EventList.hpp"
#include "footer.hpp"

class VisitorPage : public painter {
    Q_OBJECT
public:
    explicit VisitorPage(QWidget* parent = nullptr);
    // конструктор, который принимает список строк, которые укзаывают какого типа navbar создавать
    VisitorPage(const std::initializer_list<QString> typesList);
    VisitorPage(const QString& headerType, const QString& navbarType,
                  const QString& eventListType, const QString& footerType);
//    VisitorPage(const VisitorPage&) = delete;
//    VisitorPage& operator=(const VisitorPage&) = delete;
    ~VisitorPage();
    void redraw() {};
private:
    QVBoxLayout* mainLayout;
    Header header;
    Navbar navbar;
    EventList eventList;
    Footer footer;
};
