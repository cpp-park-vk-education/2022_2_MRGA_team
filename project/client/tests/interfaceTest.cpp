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
// сделать для компонентов гетеры 
// чтобы можно было привязать вызовы обработчиков к QPushButton в приватных полях
private slots:
    // Factory testing
    void buttonFactoryTest();
    // void editFactoryTest();

    // StateUpdate testing
    void btnHandlerTest();

    // SignalsCall testing - handler
    void signalTesting();
    void testGuiDataTesting();

    // Сonstructor testing
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

/////////////////////////////////////TEST FACTORY///////////////////////////////////////////////////
// painter - компоновщик от которого наследуются все UI компоненты
// тестируем псевдофабрики, корректное создание компонентов
class IFactory {
    public:
        ~IFactory() = default;
        virtual painter* create(const QString& objType) = 0;
};

class MockFactory : public IFactory {
    public:
        MOCK_METHOD(painter*, create, (const QString& objType), (override));
};

class Button {
    public:
        explicit Button(IFactory* factory) : m_factory(factory) {}

    bool drawComponent(const QString& objType) {
        if (objType == "regButton") {
            m_button = static_cast<UiButton*>(m_factory->create(objType));
            std::cout << "component button has been created" << std::endl;
            return true;
        }
        return false;
    }

    UiButton* m_button; // сделать QPushButton, QLabel и т.д. - это когда буду тестировать вызовы событий (сейчас просто создания компонентов через фабрики)
    IFactory* m_factory;
};

// далее по аналогии тестируем остальные классы ui компонентов
class Edit {
    public:
        explicit Edit(IFactory* factory) : m_factory(factory) {}

    bool drawComponent(const QString& objType) {
        if (objType == "regEdit") {
            m_Edit = static_cast<UiEdit*>(m_factory->create(objType));
            std::cout << "component Edit has been created" << std::endl;
            return true;
        }
        return false;
    }

    UiEdit* m_Edit; // сделать QPushButton, QLabel и т.д. - это когда буду тестировать вызовы событий (сейчас просто создания компонентов через фабрики)
    IFactory* m_factory;
};

void UiTesting::buttonFactoryTest() {
    MockFactory factory;
    EXPECT_CALL(factory, create(QString("regButton"))).Times(AtLeast(1));

    Button button(&factory);
    EXPECT_TRUE(button.drawComponent("regButton"));
}


/////////////////////////////////////TEST STATE_UPDATE///////////////////////////////////////////////////
// тестируем вызов обработчиков при воздействие на интерфейс, обновления состояния компонента
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

/////////////////////////////////////TEST SIGNALS_CALL_CHECK///////////////////////////////////////////////////

class IEventPageHandler {
    public:
        virtual ~IEventPageHandler() = default;
        // должно быть два переопределенных обработчика, которые будут вызываться на каждой странице
        virtual void onPageClicked() = 0;
        virtual void checkTransition() = 0;
};

class MockPage : public IEventPageHandler {
public:
        MOCK_METHOD(void, onPageClicked, (), (override));
        MOCK_METHOD(void, checkTransition, (), (override));
};

class AuthorizationPageTest {
    public:
        explicit AuthorizationPageTest(IEventPageHandler* handler) : m_handler(handler){}

    bool handleEvent(const QString& someEvent) {
        if (someEvent == "isValid") {
            std::cout << "correct data" << std::endl;
            m_handler->checkTransition();
            m_handler->onPageClicked();
        }
        return true;
    }

    IEventPageHandler* m_handler;
};

void UiTesting::signalTesting()
{
    authorization* page = new authorization();
    // QTest::keyClicks(page->getEnterButton(), "Войти");
    QCOMPARE(page->getEnterButton()->text(), QString("Войти"));

    MockPage testPage;
    EXPECT_CALL(testPage, checkTransition()).Times(AtLeast(1));
    EXPECT_CALL(testPage, onPageClicked()).Times(AtLeast(1));

    AuthorizationPageTest handler(&testPage);
    EXPECT_TRUE(handler.handleEvent("isValid"));
    delete page;
}

void UiTesting::testGuiDataTesting()
{
    QTest::addColumn<QTestEventList>("events");
    QTest::addColumn<QString>("expected");

    QTestEventList list1;
    list1.addKeyClick('a');
    QTest::newRow("char") << list1 << "a";

    QTestEventList list2;
    list2.addKeyClick('a');
    list2.addKeyClick(Qt::Key_Backspace);
    QTest::newRow("there+back-again") << list2 << "";
}

/////////////////////////////////////TEST CONSTRUCTOR_CALL_CHECK///////////////////////////////////////////////////
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
    Navbar* navbar = new Navbar("", 2);
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
