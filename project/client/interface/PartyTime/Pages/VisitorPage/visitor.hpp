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
    ~VisitorPage();
    void redraw() {}; // параметр const std::initisializer_list<QSting>
private:
    QVBoxLayout* mainLayout;
    Header header;
    Navbar navbar;
    EventList eventList;
    Footer footer;
};
