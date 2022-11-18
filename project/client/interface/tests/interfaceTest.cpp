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
    page->getEnterButton();
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
    delete page;
}

QTEST_MAIN(TestQString)
#include "interfaceTest.moc"

