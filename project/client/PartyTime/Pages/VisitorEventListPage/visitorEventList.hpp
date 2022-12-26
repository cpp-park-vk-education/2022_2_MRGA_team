#pragma once

#include "Header.hpp"
#include "Navbar.hpp"
#include "EventList.hpp"
#include "footer.hpp"
#include "HttpConnector.hpp"
#include "PartyTimeConnector.hpp"
// конструктор, который принимает список строк, которые укзаывают какого типа navbar создавать
#include <../styleHelper.hpp>

class VisitorEventListPage : public painter {
    Q_OBJECT
    friend class Base;
public:
    explicit VisitorEventListPage(QWidget* parent = nullptr);
    VisitorEventListPage(const std::initializer_list<QString> typesList);
    VisitorEventListPage(const QString& headerType, const QString& navbarType,
                  const QString& eventListType, const QString& footerType);
    ~VisitorEventListPage();

    // дата, время
    std::string getDate(const std::string& dateTime);
    std::string getTime(const std::string& dateTime);
    EventList* getEventList() {return eventList;}

private:
    QVBoxLayout* mainLayout;
    Header header;
    Navbar navbar;
    EventList* eventList;
    Footer footer;

    QComboBox *comboBox;
    QPushButton *hideButton; // Click on which we will hide the specified element
    QLineEdit *lineEdit;     // LineEdit, in which we will set the element to hide
    QListView *listView;     // pointer to the list of elements

    std::shared_ptr<PartyTimeConnector> party;

private slots:
    void hideRow();
    void updateEvents();
    void subsrcibeHandler(unsigned int _eventId);
    void leaveEventHandler(unsigned int _eventId);

signals:
    void updateEventsSignal();
};
