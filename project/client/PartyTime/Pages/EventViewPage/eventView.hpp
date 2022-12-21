#pragma once

#include "Header.hpp"
#include "Navbar.hpp"
#include "EventForm.hpp"
#include "EventList.hpp"
#include "footer.hpp"
#include <../styleHelper.hpp>
#include <QListView>
#include <QStringListModel>
#include <../painter.hpp>
#include "HttpConnector.hpp"
#include "PartyTimeConnector.hpp"


class EventViewPage : public painter {
    Q_OBJECT

    friend class Base;
    friend class painter;
public:
    explicit EventViewPage(QWidget* parent = nullptr);
    // конструктор, который принимает список строк, которые укзаывают какого типа navbar создавать
    EventViewPage(const std::initializer_list<QString> typesList);
    EventViewPage(const QString& headerType, const QString& navbarType,
                  const QString& eventListType, const QString& footerType);
    ~EventViewPage();
    void redraw() {}; // параметр const std::initisializer_list<QSting>

private:
    QVBoxLayout* mainLayout;
    Header header;
    Navbar navbar;
    EventList* eventList;
    Footer footer;

    EventForm* form1;
    painter* form;
    QPushButton* addButton;         // кнопка, которая открывает форму
    QPushButton* closeFormButton;   // кнопка, которая закрывает форму
    QPushButton* createEventButton; // кнопка, которая находится в форме

    QLineEdit* eventName;
    QLineEdit* description;
    QDateEdit* date;
    QTimeEdit* time;
    QLineEdit* address;
//    QLineEdit* visitors;
    QLineEdit* maxVisitors;
    std::shared_ptr<PartyTimeConnector> party;

protected slots:
    void onAdd();
    void onRemove();
    void onCreate();

//signals:
//    void addItem() {}
//    void deleteItem() {}

private:
    QListView* m_pwPending = nullptr;
    QListView* m_pwCompleted = nullptr;

    QAction* m_pActAdd = nullptr;
    QAction* m_pActRemove = nullptr;
};
