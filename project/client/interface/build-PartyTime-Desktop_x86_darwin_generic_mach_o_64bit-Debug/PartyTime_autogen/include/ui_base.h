/********************************************************************************
** Form generated from reading UI file 'base.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASE_H
#define UI_BASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Base
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Base)
    {
        if (Base->objectName().isEmpty())
            Base->setObjectName(QString::fromUtf8("Base"));
        Base->resize(800, 600);
        centralwidget = new QWidget(Base);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Base->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Base);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        Base->setMenuBar(menubar);
        statusbar = new QStatusBar(Base);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Base->setStatusBar(statusbar);

        retranslateUi(Base);

        QMetaObject::connectSlotsByName(Base);
    } // setupUi

    void retranslateUi(QMainWindow *Base)
    {
        Base->setWindowTitle(QCoreApplication::translate("Base", "Base", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Base: public Ui_Base {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASE_H
