// #include <gtest/gtest.h>
#include <authorization.hpp>
// #include <QApplication>
#include <QTest>

class TestQString: public QObject
{
    Q_OBJECT
    friend authorization;
private slots:
    void toUpper();
};

void TestQString::toUpper()
{
    authorization* page = new authorization();
    // QPushButton btn = page->getEnterButton();
    // btn.setText("Other");
    QString str = "Hello";
    QCOMPARE(page->getEnterButton()->text(), QString("Войти"));
    QCOMPARE(str.toUpper(), QString("HELLO"));

    delete page;
    // delete btn;
}

QTEST_MAIN(TestQString)
#include "interfaceTest.moc"

