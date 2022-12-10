#pragma once

#include "Header.hpp"
#include "Navbar.hpp"
#include "EventList.hpp"
#include "footer.hpp"
#include <../styleHelper.hpp>
#include <QListView>
#include <QStringListModel>
#include <../painter.hpp>


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

    painter* form;
    QPushButton* addButton;
    QPushButton* closeFormButton;
    QPushButton* createEventButton;

    QLineEdit* eventName;
    QLineEdit* description;
    QLineEdit* date;
    QLineEdit* time;
    QLineEdit* address;
    QLineEdit* visitors;
    QLineEdit* maxVisitors;



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
