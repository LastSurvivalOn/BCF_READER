/********************************************************************************
** Form generated from reading UI file 'filewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEWINDOW_H
#define UI_FILEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileWindow
{
public:
    QAction *action;
    QAction *action_2;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FileWindow)
    {
        if (FileWindow->objectName().isEmpty())
            FileWindow->setObjectName("FileWindow");
        FileWindow->resize(800, 600);
        action = new QAction(FileWindow);
        action->setObjectName("action");
        action_2 = new QAction(FileWindow);
        action_2->setObjectName("action_2");
        centralwidget = new QWidget(FileWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(16);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);

        verticalLayout->addWidget(tableWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");

        horizontalLayout_2->addWidget(pushButton_6);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");

        horizontalLayout_2->addWidget(pushButton_4);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");

        horizontalLayout_2->addWidget(pushButton_5);


        verticalLayout->addLayout(horizontalLayout_2);

        FileWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FileWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        FileWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(FileWindow);
        statusbar->setObjectName("statusbar");
        FileWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(action);
        menu->addAction(action_2);

        retranslateUi(FileWindow);

        QMetaObject::connectSlotsByName(FileWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FileWindow)
    {
        FileWindow->setWindowTitle(QCoreApplication::translate("FileWindow", "MainWindow", nullptr));
        action->setText(QCoreApplication::translate("FileWindow", "\320\222\321\226\320\264\320\272\321\200\320\270\321\202\320\270", nullptr));
        action_2->setText(QCoreApplication::translate("FileWindow", "\320\241\321\202\320\262\320\276\321\200\320\270\321\202\320\270", nullptr));
        pushButton_6->setText(QCoreApplication::translate("FileWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\320\270 \321\204\320\260\320\271\320\273", nullptr));
        pushButton_3->setText(QCoreApplication::translate("FileWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\320\270 \321\200\321\217\320\264\320\276\320\272", nullptr));
        pushButton_4->setText(QCoreApplication::translate("FileWindow", "\320\222\320\270\320\264\320\260\320\273\320\270\321\202\320\270 \321\200\321\217\320\264\320\276\320\272", nullptr));
        pushButton_2->setText(QCoreApplication::translate("FileWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\320\270 \321\201\321\202\320\276\320\262\320\277\320\265\321\206\321\214", nullptr));
        pushButton_5->setText(QCoreApplication::translate("FileWindow", "\320\222\320\270\320\264\320\260\320\273\320\270\321\202\320\270 \321\201\321\202\320\276\320\262\320\277\320\265\321\206\321\214", nullptr));
        menu->setTitle(QCoreApplication::translate("FileWindow", "\320\244\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileWindow: public Ui_FileWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEWINDOW_H
