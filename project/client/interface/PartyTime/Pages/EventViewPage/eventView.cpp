#include "eventView.hpp"

#include <QLabel>
#include <QToolBar>
#include <QBoxLayout>
#include <QAction>


EventViewPage::EventViewPage(QWidget *parent) : painter(parent), mainLayout(new QVBoxLayout(this))
{
    Navbar* navbarFactory = new Navbar("", 3);
    this->navbar = *navbarFactory->create("visitor");
    this->navbar.setGeometry(this->x(), this->y(), 1440, 100);
    this->navbar.setStyleSheet(this->navbar.styleSheet() + "max-height: 100px;");
    mainLayout->addWidget(&this->navbar, Qt::AlignTop | Qt::AlignCenter);


    // TODO: to do list
    QVBoxLayout* todoContainer = new QVBoxLayout();
    todoContainer->setContentsMargins(30, 0, 0, 0);
//    QLabel* pwTitle = new QLabel("My events", this);
//    todoContainer->addWidget(pwTitle, Qt::AlignTop | Qt::AlignCenter);
//    pwTitle->setAlignment(Qt::AlignCenter);
//    pwTitle->setStyleSheet("font-weight: 900; font-size: 30pt;");

    QToolBar* pToolBar = new QToolBar();
    pToolBar->setStyleSheet("background-color: #ffffff; max-width: 90px; max-height: 40px;");
    todoContainer->addWidget(pToolBar, Qt::AlignTop | Qt::AlignCenter);

    m_pActAdd = new QAction(this);
    m_pActAdd->setIcon(QIcon(":/image/addButton.png"));
    connect(m_pActAdd, &QAction::triggered, this, &EventViewPage::onAdd);

    m_pActRemove = new QAction(this);
    m_pActRemove->setIcon(QIcon(":/image/delete.svg"));
    connect(m_pActRemove, &QAction::triggered, this, &EventViewPage::onRemove);

    pToolBar->addAction(m_pActAdd);
    pToolBar->addAction(m_pActRemove);

//    QHBoxLayout* pHLayoutLabels = new QHBoxLayout();
//    todoContainer->addLayout(pHLayoutLabels, 2);

//    QLabel* plblPending = new QLabel("Pending");
//    plblPending->setStyleSheet("font-size: 20pt; font-weight: 700; color: #ffffff;");
//    pHLayoutLabels->addWidget(plblPending, Qt::AlignTop | Qt::AlignCenter);

//    QLabel* plblCompleted = new QLabel("Completed");
//    plblCompleted->setStyleSheet("font-size: 20pt; font-weight: 700; color: #ffffff;");
//    pHLayoutLabels->addWidget(plblCompleted, Qt::AlignTop | Qt::AlignCenter);

    QHBoxLayout* pHLayout = new QHBoxLayout();
    todoContainer->addLayout(pHLayout, Qt::AlignTop | Qt::AlignCenter);

    m_pwPending = new QListView(this);
    m_pwPending->setDragEnabled(true);
    m_pwPending->setAcceptDrops(true);
    m_pwPending->setDropIndicatorShown(true);
    m_pwPending->setDefaultDropAction(Qt::MoveAction);
    pHLayout->addWidget(m_pwPending);

    m_pwCompleted = new QListView(this);
    m_pwCompleted->setDragEnabled(true);
    m_pwCompleted->setAcceptDrops(true);
    m_pwCompleted->setDropIndicatorShown(true);
    m_pwCompleted->setDefaultDropAction(Qt::MoveAction);
    pHLayout->addWidget(m_pwCompleted);

    m_pwPending->setModel(new QStringListModel());
    m_pwCompleted->setModel(new QStringListModel());

//    m_pwPending->setObjectName("pendingList");
    m_pwPending->setStyleSheet("QListView { max-height: 400px; max-width: 700px; background-color: #ffffff; border-radius: 10px; font-size: 20pt; font-weight: bold; }"
     "QListView::item { background-color: #E74C3C; padding: 10%;"
     "border: 1px solid #C0392B; }"
     "QListView::item::hover { background-color: #C0392B }");

//    m_pwCompleted->setObjectName("completedList");
    m_pwCompleted->setStyleSheet("QListView { max-height: 400px; max-width: 700px; background-color: #ffffff; border-radius: 10px; font-size: 20pt; font-weight: bold; }"
     "QListView::item { background-color: #2ECC71; padding: 10%;"
     "border: 1px solid #27AE60; }"
     "QListView::item::hover { background-color: #27AE60 }");

    mainLayout->addLayout(todoContainer, Qt::AlignTop | Qt::AlignCenter);
}

void EventViewPage::onAdd()
{
    m_pwPending->model()->insertRow(m_pwPending->model()->rowCount());
    QModelIndex oIndex = m_pwPending->model()->index(
                m_pwPending->model()->rowCount() - 1, 0);

    m_pwPending->edit(oIndex);
}

void EventViewPage::onRemove()
{
    QModelIndex oIndex = m_pwPending->currentIndex();
    m_pwPending->model()->removeRow(oIndex.row());
}

EventViewPage::EventViewPage(const std::initializer_list<QString> typesList) : mainLayout(new QVBoxLayout())
{
    for (const auto& elem : typesList) {
        if (elem == "") {

        }
    }
}

EventViewPage::EventViewPage(const QString &headerType, const QString &navbarType, const QString &eventListType, const QString &footerType) : mainLayout(new QVBoxLayout())
{
    Header* headerFactory = new Header();
    this->header = *(headerFactory->create(headerType));
    delete headerFactory;
    headerFactory = nullptr;

    Navbar* navbarFactory = new Navbar();
    this->navbar = *(navbarFactory->create(navbarType));
    delete navbarFactory;
    navbarFactory = nullptr;

    EventList* eventListFactory = new EventList();
    this->eventList = *(eventListFactory->create(eventListType));
    delete eventListFactory;
    eventListFactory = nullptr;

    Footer* footerFactory = new Footer();
    this->footer = *(footerFactory->create(footerType));
    delete footerFactory;
    footerFactory = nullptr;
}

EventViewPage::~EventViewPage()
{
    delete mainLayout;
}
