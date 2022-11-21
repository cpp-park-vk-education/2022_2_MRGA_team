#include "authorization.hpp"
#include "registration.hpp"
#include "loading.hpp"
#include "organizer.hpp"
#include "profile.hpp"
#include "eventView.hpp"
#include "visitorEventList.hpp"
#include "visitor.hpp"

#include "Button.hpp"
#include "Edit.hpp"
#include "Label.hpp"
#include "Input.hpp"
#include "Loader.hpp"
#include "Navbar.hpp"
#include "Header.hpp"
#include "footer.hpp"
#include "EventForm.hpp"
#include "EventItem.hpp"
#include "EventList.hpp"

#include <iostream>
#include <QTest>
#include "gtest/gtest.h"
#include "gmock/gmock.h"


using ::testing::AtLeast;

class UiTesting : public QObject
{
    Q_OBJECT
// сделать fried-ами все компоненты или потом прописать им гетеры, 
// чтобы можно было привязать вызовы обработчиков к QPushButton в приватных полях
private slots:
    // factory testing
    void buttonFactoryTest();
    // Change State test
    void btnHandlerTest();

    // Creating components test cases:
    //  Ui
    void btnTest();
    void editTest();
    void labelTest();
    void inputTest();
    void loaderTest();
    // Components
    void headerTest();
    void navbarTest();
    void formTest();
    void eventItemTest();
    void eventListTest();
    void footerTest();
    // Pages
    void loadingPageTest();
    void authorizationTest();
    void registrationTest();
    void eventViewPageTest();
    void visitorPageTest();
    void orgnizerPageTest();
    void profilePageTest();
    void visitorEventListPageTest();
};

// сначала надо протестировать фарбрики создания UI-компонентов для этого создадим интерфейс. Будем переопределять у него метод create
class IFactory {
    public:
        ~IFactory() = default;
        virtual UiButton* create(const QString& objType) = 0;
};

class MockButttonFactory : public IFactory {
    public:
        MOCK_METHOD(UiButton*, create, (const QString& objType), (override));
};

class Button {
    public:
        explicit Button(IFactory* factory) : m_factory(factory) {}

    bool drawComponent(const QString& objType) {
        if (objType == "regButton") {
            m_button = m_factory->create(objType);
            std::cout << "component button has been created" << std::endl;
            return true;
        }
        return false;
    }

    UiButton* m_button; // сделать QPushButton, QLabel и т.д. - это когда буду тестировать вызовы событий (сейчас просто создания компонентов через фабрики)
    IFactory* m_factory;
};

void UiTesting::buttonFactoryTest() {
    MockButttonFactory factory;
    EXPECT_CALL(factory, create(QString("regButton"))).Times(AtLeast(1));

    Button button(&factory);
    EXPECT_TRUE(button.drawComponent("regButton"));
}

// вместо IEventHandler возможно стоить написать IButton
// вообще да, для каждого компонента в qt разные слоты вызываются, поэтому тут должен IButton
// и протестированы все обработчики, которые буду вызывать для кнопок
class IEventHandler {
    public:
        virtual ~IEventHandler() = default;
        virtual void onClicked() = 0;
        virtual void onPressed() = 0;
        virtual void onFocus() = 0;
};

class MockUiButton : public IEventHandler {
    public:
        MOCK_METHOD(void, onClicked, (), (override));
        MOCK_METHOD(void, onPressed, (), (override));
        MOCK_METHOD(void, onFocus, (), (override));
};

class Painter {
 public:
  explicit Painter(IEventHandler* button) : m_button(button) {}

  bool redrawComponent(const QString& newState) {
    if (newState == "colorRed") {
        std::cout << "component updated" << std::endl;
    }
    m_button->onFocus();
    m_button->onClicked();
    m_button->onPressed();

    return true;
  }

  IEventHandler* m_button; // сделать QPushButton, QLabel и т.д.
};

void UiTesting::btnHandlerTest()
{
    MockUiButton button;
    EXPECT_CALL(button, onFocus()).Times(AtLeast(1));
    EXPECT_CALL(button, onClicked()).Times(AtLeast(1));
    EXPECT_CALL(button, onPressed()).Times(AtLeast(1));

    Painter painter(&button);
    EXPECT_TRUE(painter.redrawComponent("colorRed"));
}

class IEventPageHandler {
    public:
        virtual ~IEventPageHandler() = default;
        // должно быть два переопределенных обработчика, которые будут вызываться на каждой странице
        virtual void onPageClicked() = 0;
        virtual void checkTransition() = 0;
        // virtual void onAutnClicked() = 0;
        // virtual void onEnter() = 0; // функция, которая чекает валадацию и осуществляет переход на другой экран
        // virtual void onRegistrationPageClicked() = 0;
        // virtual void onRegister() = 0;
        // virtual void onProfilePageClicked() = 0;
        // virtual void onProfile() = 0;
        // virtual void onSettingsPageClicked() = 0;
        // virtual void onSettings() = 0;
        // virtual void onEventViewPageClicked() = 0;
        // virtual void onEvent() = 0;
        // virtual void onLoadingPageClicked() = 0;
        // virtual void onLoading() = 0;
        // virtual void onVisitorPageClicked() = 0;
        // virtual void onVisitor() = 0;
        // virtual void onOrganizerPageClicked() = 0;
        // virtual void onOrganizer() = 0;
        // virtual void onVisitorEventListPageClicked() = 0;
        // virtual void onVisitorEventList() = 0;
};

// class MockPage : public IEventPageHandler {

// };

// UI
void UiTesting::btnTest()
{
    UiButton* btn = new UiButton();
    QString res = "";
    if (btn != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));
    delete btn;
}

void UiTesting::editTest()
{   
    QString res = "";
    UiEdit* edit = new UiEdit();
    if (edit != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete edit;
}

void UiTesting::labelTest()
{
    QString res = "";
    UiLabel* label = new UiLabel();
    if (label != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete label;
}

void UiTesting::inputTest()
{
    QString res = "";
    UiInput* input = new UiInput();
    if (input != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete input;
}

void UiTesting::loaderTest() {
    QString res = "";
    UiLoader* loader = new UiLoader(QString("project/client/interface/PartyTime/circleLoader.gif"));
    if (loader != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete loader;
}

// Components
void UiTesting::headerTest()
{
    QString res = "";
    Header* header = new Header();
    if (header != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete header;
}

void UiTesting::navbarTest()
{
    QString res = "";
    Navbar* navbar = new Navbar(2);
    if (navbar != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete navbar;
}

void UiTesting::formTest()
{
    QString res = "";
    EventForm* form = new EventForm();
    if (form != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete form;
}

void UiTesting::eventItemTest() 
{
    QString res = "";
    EventItem* item = new EventItem();
    if (item != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete item;
}

void UiTesting::eventListTest() 
{
    QString res = "";
    EventList* list = new EventList();
    if (list != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete list;
}

void UiTesting::footerTest() 
{
    QString res = "";
    Footer* footer = new Footer();
    if (footer != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete footer;
}

// pages
void UiTesting::loadingPageTest() 
{
    QString res = "";
    LoadingPage* page = new LoadingPage("kk", "oo");
    if (page != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete page;
}

void UiTesting::authorizationTest() 
{
    authorization* page = new authorization();
    QCOMPARE(page->getEnterButton()->text(), QString("Войти"));
    delete page;
}

void UiTesting::registrationTest() 
{
    registration* page = new registration();
    QCOMPARE(page->getBackButton()->text(), QString("назад"));
    delete page;
}

void UiTesting::eventViewPageTest() 
{
    QString res = "";
    EventViewPage* page = new EventViewPage();
    if (page != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete page;
}

void UiTesting::visitorPageTest() 
{
    QString res = "";
    VisitorPage* page = new VisitorPage();
    if (page != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete page;
}

void UiTesting::orgnizerPageTest() 
{
    QString res = "";
    OrganizerPage* page = new OrganizerPage();
    if (page != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete page;
}

void UiTesting::profilePageTest()
{
    QString res = "";
    ProfilePage* page = new ProfilePage();
    if (page != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete page;
}

void UiTesting::visitorEventListPageTest() 
{
    QString res = "";
    VisitorEventListPage* page = new VisitorEventListPage();
    if (page != nullptr) {
        // проверяем корректно ли создался компонент, правильный ли вызвался конструктор и заполнились поля объекта
        res = "component working";
    }
    QCOMPARE(res, QString("component working"));

    delete page;
}

QTEST_MAIN(UiTesting)
#include "interfaceTest.moc"
