/********************************************************************************
** Form generated from reading UI file 'options.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Dialog_options
{
public:
    QDialogButtonBox *buttonBox;
    QDoubleSpinBox *alpha_spinbox;
    QLabel *label;
    QDoubleSpinBox *alpha_spinbox_2;
    QLabel *label_2;
    QLabel *label_3;
    QDoubleSpinBox *alpha_spinbox_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QDialog *Dialog_options)
    {
        if (Dialog_options->objectName().isEmpty())
            Dialog_options->setObjectName(QString::fromUtf8("Dialog_options"));
        Dialog_options->resize(362, 427);
        buttonBox = new QDialogButtonBox(Dialog_options);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(90, 370, 181, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        alpha_spinbox = new QDoubleSpinBox(Dialog_options);
        alpha_spinbox->setObjectName(QString::fromUtf8("alpha_spinbox"));
        alpha_spinbox->setGeometry(QRect(180, 70, 61, 20));
        alpha_spinbox->setDecimals(2);
        alpha_spinbox->setMaximum(9999.99);
        alpha_spinbox->setSingleStep(0.01);
        label = new QLabel(Dialog_options);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 70, 51, 16));
        alpha_spinbox_2 = new QDoubleSpinBox(Dialog_options);
        alpha_spinbox_2->setObjectName(QString::fromUtf8("alpha_spinbox_2"));
        alpha_spinbox_2->setGeometry(QRect(180, 210, 61, 20));
        alpha_spinbox_2->setDecimals(2);
        alpha_spinbox_2->setMaximum(1);
        alpha_spinbox_2->setSingleStep(0.01);
        label_2 = new QLabel(Dialog_options);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 210, 151, 20));
        label_3 = new QLabel(Dialog_options);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 250, 151, 20));
        alpha_spinbox_3 = new QDoubleSpinBox(Dialog_options);
        alpha_spinbox_3->setObjectName(QString::fromUtf8("alpha_spinbox_3"));
        alpha_spinbox_3->setGeometry(QRect(180, 250, 61, 20));
        alpha_spinbox_3->setDecimals(2);
        alpha_spinbox_3->setMaximum(999.99);
        alpha_spinbox_3->setSingleStep(0.01);
        label_4 = new QLabel(Dialog_options);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(100, 170, 171, 20));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setLineWidth(1);
        label_5 = new QLabel(Dialog_options);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(110, 30, 171, 20));
        label_5->setFont(font);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setLineWidth(1);

        retranslateUi(Dialog_options);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog_options, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog_options, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_options);
    } // setupUi

    void retranslateUi(QDialog *Dialog_options)
    {
        Dialog_options->setWindowTitle(QApplication::translate("Dialog_options", "Options", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog_options", "Beta", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dialog_options", "Maximum deviation", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dialog_options", "Maximum deviation", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dialog_options", "Plane extraction", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Dialog_options", "Classification", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog_options: public Ui_Dialog_options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
