#include "visitorEventList.hpp"
#include <iostream>

VisitorEventListPage::VisitorEventListPage(QWidget *parent) : painter(parent), mainLayout(new QVBoxLayout(this)), comboBox(new QComboBox(this)),
    hideButton(new QPushButton("Search", this)),
    lineEdit(new QLineEdit(this))
{
    // задаем id страницы
    this->setObjectName("visitorPage");

    // создаем фабрики
    Navbar* navbarFactory = new Navbar("", 3);
    this->navbar = *navbarFactory->create("visitor");
    this->navbar.setGeometry(this->x(), this->y(), 1440, 100);

    // DropDownMenu
    QGridLayout *comboBoxLayout = new QGridLayout(this);
    comboBoxLayout->setContentsMargins(30, 0, 25, 0);
    comboBox->setObjectName("eventCategories");

    hideButton->setProperty("cssClass", "searchButton");
    hideButton->setFixedWidth(200);

    QPalette pal = lineEdit->palette();
    pal.setColor(QPalette::PlaceholderText, QColor(0, 0, 0, 100));
    lineEdit->setMaximumWidth(800);
    lineEdit->setProperty("cssClass", "comboBoxEdit");
    lineEdit->setPalette(pal);
    lineEdit->setPlaceholderText("Event name");
    lineEdit->setFont(QFont("Times", -1, QFont::Bold));
    lineEdit->setStyleSheet("background-color: #babfd9; color: #fff; border-radius: 15px");


    comboBoxLayout->addWidget(comboBox, 0, 0, 1, 2);
    comboBoxLayout->addWidget(hideButton, 0, 1, 1, 1);
    comboBoxLayout->addWidget(lineEdit, 0, 2, 1, 1);

    listView = new QListView(comboBox);
    listView->setStyleSheet("QListView::item {                              \
                             margin-bottom: 10px; color: #ffffff; border-bottom: 2px solid white; font-size: 16px;}  \
                             QListView::item:selected {                     \
                             border-bottom: 2px solid rgba(164, 115, 18, 1);    \
                             color: rgba(164, 115, 18, 1); font-size: 16px;}                                \
                             QListView::item:checked {                      \
                             margin-bottom: 30px; background-color: green;                       \
                             color: green; font-size: 16px;}"
                             );

    comboBox->setProperty("cssClaas", "comboBoxList");
    comboBox->setFixedWidth(200);
    comboBox->setView(listView);
    comboBox->addItem("All events");
    comboBox->addItem("Сlub events");
    comboBox->addItem("Home events");
    comboBox->addItem("Сoncerts");

    connect(hideButton, &QPushButton::clicked, this, &VisitorEventListPage::hideRow);


    mainLayout->addWidget(&this->navbar, 0, Qt::AlignCenter | Qt::AlignTop);
    mainLayout->addLayout(comboBoxLayout, Qt::AlignTop | Qt::AlignCenter);
    mainLayout->addWidget(new EventList(), 2, Qt::AlignTop | Qt::AlignCenter);
}

VisitorEventListPage::VisitorEventListPage(const std::initializer_list<QString> typesList) : mainLayout(new QVBoxLayout())
{
    for (const auto& elem : typesList) {
        if (elem == "") {

        }
    }
}

VisitorEventListPage::VisitorEventListPage(const QString &headerType, const QString &navbarType, const QString &eventListType, const QString &footerType) : mainLayout(new QVBoxLayout())
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

VisitorEventListPage::~VisitorEventListPage()
{
    //    delete mainLayout;
}

void VisitorEventListPage::hideRow()
{
    std::vector<std::string> headers;

//    listView->setRowHidden(lineEdit->text().toInt(), true);
}
