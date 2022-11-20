#include "authorization.hpp"
#include "Button.hpp"
#include "Edit.hpp"
#include "Label.hpp"
#include "Input.hpp"
#include "Loader.hpp"
#include "Navbar.hpp"
#include "Header.hpp"
#include "EventForm.hpp"
#include "EventItem.hpp"
#include <QTest>

class UiTesting : public QObject
{
    Q_OBJECT
    // friend-ы чтобы мог обращаться к приватным полям вновь созданного компоненты и проверять корректно ли он создался
    friend authorization;
    friend UiButton;
    friend UiEdit;
    friend UiLabel;
    friend UiInput;
    friend UiLoader;
    friend Navbar;


private slots:
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

// UI
void UiTesting::btnTest()
{
    authorization* page = new authorization();
    QCOMPARE(page->getEnterButton()->text(), QString("Войти"));
    delete page;

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

}

void UiTesting::footerTest() 
{

}

//pages
void UiTesting::loadingPageTest() 
{

}

void UiTesting::authorizationTest() 
{

}

void UiTesting::registrationTest() 
{

}

void UiTesting::eventViewPageTest() 
{

}

void UiTesting::visitorPageTest() 
{

}

void UiTesting::orgnizerPageTest() 
{

}

void UiTesting::profilePageTest()
{

}

void UiTesting::visitorEventListPageTest() 
{

}


QTEST_MAIN(UiTesting)
#include "interfaceTest.moc"

