/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *NewGameButton;
    QPushButton *ContinueButton;
    QPushButton *ExitButton;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(714, 432);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(227, 227, 227);\n"
"font: 18pt \"Snap ITC\";"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        NewGameButton = new QPushButton(centralWidget);
        NewGameButton->setObjectName(QStringLiteral("NewGameButton"));
        NewGameButton->setGeometry(QRect(520, 120, 150, 50));
        NewGameButton->setAutoFillBackground(false);
        NewGameButton->setStyleSheet(QStringLiteral("border: 1px solid orange;"));
        ContinueButton = new QPushButton(centralWidget);
        ContinueButton->setObjectName(QStringLiteral("ContinueButton"));
        ContinueButton->setEnabled(true);
        ContinueButton->setGeometry(QRect(520, 180, 150, 50));
        ContinueButton->setAutoFillBackground(false);
        ContinueButton->setStyleSheet(QStringLiteral("border: 1px solid orange;"));
        ContinueButton->setFlat(false);
        ExitButton = new QPushButton(centralWidget);
        ExitButton->setObjectName(QStringLiteral("ExitButton"));
        ExitButton->setGeometry(QRect(520, 360, 150, 50));
        QFont font;
        font.setFamily(QStringLiteral("Snap ITC"));
        font.setPointSize(18);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        ExitButton->setFont(font);
        ExitButton->setAutoFillBackground(false);
        ExitButton->setStyleSheet(QStringLiteral("border: 1px solid orange;"));
        ExitButton->setAutoDefault(false);
        ExitButton->setFlat(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 150, 441, 271));
        label->setStyleSheet(QStringLiteral("border-image: url(:/MainWindow/Recources/MainWindowBackground.jpg);"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 0, 551, 151));
        label_2->setAutoFillBackground(false);
        label_2->setStyleSheet(QStringLiteral("border-image: url(:/MainWindow/Recources/Bomberman_Title.png);"));
        MainWindow->setCentralWidget(centralWidget);
        label->raise();
        ExitButton->raise();
        label_2->raise();
        NewGameButton->raise();
        ContinueButton->raise();

        retranslateUi(MainWindow);

        ExitButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        NewGameButton->setText(QApplication::translate("MainWindow", "New Game", Q_NULLPTR));
        ContinueButton->setText(QApplication::translate("MainWindow", "Continue", Q_NULLPTR));
        ExitButton->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
