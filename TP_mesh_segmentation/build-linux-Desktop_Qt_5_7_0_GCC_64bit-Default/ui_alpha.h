/********************************************************************************
** Form generated from reading UI file 'alpha.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALPHA_H
#define UI_ALPHA_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QWidget>
#include "viewer.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionLoad_points;
    QAction *actionView_points;
    QAction *actionSave_snapshot;
    QAction *actionCopy_snapshot;
    QAction *actionView_edges;
    QAction *actionParameters;
    QAction *actionSnapshot;
    QAction *actionView_alpha_shape;
    QAction *actionCompute_alpha_shape;
    QAction *actionLoad_mesh;
    QAction *actionClassification;
    QAction *actionPlane_Extraction;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    Viewer *viewer;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuAlgorithms;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(507, 388);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/cgal/icons/resources/cgal_logo.xpm"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionLoad_points = new QAction(MainWindow);
        actionLoad_points->setObjectName(QString::fromUtf8("actionLoad_points"));
        actionView_points = new QAction(MainWindow);
        actionView_points->setObjectName(QString::fromUtf8("actionView_points"));
        actionView_points->setCheckable(true);
        actionView_points->setChecked(true);
        actionSave_snapshot = new QAction(MainWindow);
        actionSave_snapshot->setObjectName(QString::fromUtf8("actionSave_snapshot"));
        actionCopy_snapshot = new QAction(MainWindow);
        actionCopy_snapshot->setObjectName(QString::fromUtf8("actionCopy_snapshot"));
        actionView_edges = new QAction(MainWindow);
        actionView_edges->setObjectName(QString::fromUtf8("actionView_edges"));
        actionView_edges->setCheckable(true);
        actionView_edges->setChecked(true);
        actionParameters = new QAction(MainWindow);
        actionParameters->setObjectName(QString::fromUtf8("actionParameters"));
        actionSnapshot = new QAction(MainWindow);
        actionSnapshot->setObjectName(QString::fromUtf8("actionSnapshot"));
        actionView_alpha_shape = new QAction(MainWindow);
        actionView_alpha_shape->setObjectName(QString::fromUtf8("actionView_alpha_shape"));
        actionView_alpha_shape->setCheckable(true);
        actionCompute_alpha_shape = new QAction(MainWindow);
        actionCompute_alpha_shape->setObjectName(QString::fromUtf8("actionCompute_alpha_shape"));
        actionLoad_mesh = new QAction(MainWindow);
        actionLoad_mesh->setObjectName(QString::fromUtf8("actionLoad_mesh"));
        actionClassification = new QAction(MainWindow);
        actionClassification->setObjectName(QString::fromUtf8("actionClassification"));
        actionPlane_Extraction = new QAction(MainWindow);
        actionPlane_Extraction->setObjectName(QString::fromUtf8("actionPlane_Extraction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        viewer = new Viewer(centralwidget);
        viewer->setObjectName(QString::fromUtf8("viewer"));
        viewer->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(viewer, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 507, 31));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuAlgorithms = new QMenu(menubar);
        menuAlgorithms->setObjectName(QString::fromUtf8("menuAlgorithms"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAlgorithms->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFile->addAction(actionLoad_points);
        menuFile->addAction(actionLoad_mesh);
        menuFile->addSeparator();
        menuFile->addAction(actionCopy_snapshot);
        menuFile->addAction(actionSave_snapshot);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuView->addAction(actionView_points);
        menuView->addAction(actionView_edges);
        menuAlgorithms->addAction(actionParameters);
        menuAlgorithms->addSeparator();
        menuAlgorithms->addAction(actionClassification);
        menuAlgorithms->addAction(actionPlane_Extraction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Alpha shapes", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionLoad_points->setText(QApplication::translate("MainWindow", "Load point set...", 0, QApplication::UnicodeUTF8));
        actionLoad_points->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionView_points->setText(QApplication::translate("MainWindow", "Points", 0, QApplication::UnicodeUTF8));
        actionView_points->setShortcut(QApplication::translate("MainWindow", "P", 0, QApplication::UnicodeUTF8));
        actionSave_snapshot->setText(QApplication::translate("MainWindow", "Save snapshot", 0, QApplication::UnicodeUTF8));
        actionCopy_snapshot->setText(QApplication::translate("MainWindow", "Copy snapshot", 0, QApplication::UnicodeUTF8));
        actionCopy_snapshot->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionView_edges->setText(QApplication::translate("MainWindow", "Edges", 0, QApplication::UnicodeUTF8));
        actionView_edges->setShortcut(QApplication::translate("MainWindow", "E", 0, QApplication::UnicodeUTF8));
        actionParameters->setText(QApplication::translate("MainWindow", "Parameters", 0, QApplication::UnicodeUTF8));
        actionParameters->setShortcut(QApplication::translate("MainWindow", "Shift+P", 0, QApplication::UnicodeUTF8));
        actionSnapshot->setText(QApplication::translate("MainWindow", "Snapshot", 0, QApplication::UnicodeUTF8));
        actionSnapshot->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionView_alpha_shape->setText(QApplication::translate("MainWindow", "Alpha shape", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionView_alpha_shape->setToolTip(QApplication::translate("MainWindow", "View alpha shape", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionView_alpha_shape->setShortcut(QApplication::translate("MainWindow", "S", 0, QApplication::UnicodeUTF8));
        actionCompute_alpha_shape->setText(QApplication::translate("MainWindow", "Classification", 0, QApplication::UnicodeUTF8));
        actionCompute_alpha_shape->setShortcut(QApplication::translate("MainWindow", "A", 0, QApplication::UnicodeUTF8));
        actionLoad_mesh->setText(QApplication::translate("MainWindow", "Load mesh", 0, QApplication::UnicodeUTF8));
        actionClassification->setText(QApplication::translate("MainWindow", "Classification", 0, QApplication::UnicodeUTF8));
        actionPlane_Extraction->setText(QApplication::translate("MainWindow", "Plane Extraction", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "&View", 0, QApplication::UnicodeUTF8));
        menuAlgorithms->setTitle(QApplication::translate("MainWindow", "Algorithms", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALPHA_H
