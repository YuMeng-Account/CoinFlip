/********************************************************************************
** Form generated from reading UI file 'mainscene.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCENE_H
#define UI_MAINSCENE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainScene
{
public:
    QAction *actionkaishi;
    QAction *actionQuit;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;

    void setupUi(QMainWindow *mainScene)
    {
        if (mainScene->objectName().isEmpty())
            mainScene->setObjectName("mainScene");
        mainScene->resize(800, 600);
        mainScene->setStyleSheet(QString::fromUtf8(""));
        actionkaishi = new QAction(mainScene);
        actionkaishi->setObjectName("actionkaishi");
        actionQuit = new QAction(mainScene);
        actionQuit->setObjectName("actionQuit");
        actionQuit->setPriority(QAction::Priority::LowPriority);
        centralwidget = new QWidget(mainScene);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        mainScene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainScene);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menubar->setDefaultUp(false);
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        mainScene->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionQuit);

        retranslateUi(mainScene);

        QMetaObject::connectSlotsByName(mainScene);
    } // setupUi

    void retranslateUi(QMainWindow *mainScene)
    {
        mainScene->setWindowTitle(QCoreApplication::translate("mainScene", "mainScene", nullptr));
        actionkaishi->setText(QCoreApplication::translate("mainScene", "\345\274\200\345\247\213", nullptr));
        actionQuit->setText(QCoreApplication::translate("mainScene", "\351\200\200\345\207\272", nullptr));
        menu->setTitle(QCoreApplication::translate("mainScene", "\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainScene: public Ui_mainScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCENE_H
