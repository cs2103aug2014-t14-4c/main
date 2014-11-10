/********************************************************************************
//@author generated
//
// Form generated from reading UI file 'whattodo.ui'
//
// Created by: Qt User Interface Compiler version 5.3.2
//
// WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHATTODO_H
#define UI_WHATTODO_H

#include <QtCore/QVariant>
#include <QtDeclarative/QDeclarativeView>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WhatToDoClass
{
public:
    QWidget *centralWidget;
    QDeclarativeView *background;
    QDeclarativeView *buttonRedo;
    QDeclarativeView *buttonUndo;
    QDeclarativeView *buttonAgendaview;
    QDeclarativeView *buttonCalendarview;
    QWebView *displayAgendaviewFloat;
    QTextEdit *commandLine;
    QDeclarativeView *messageFeedback;
    QWebView *displayAgendaviewTimed;
    QTextEdit *statusBar;
    QTextEdit *commandSearch;
    QFrame *calendarframe;
    QPushButton *calendarbtn_prev;
    QPushButton *calendarbtn_next;

    void setupUi(QMainWindow *WhatToDoClass)
    {
        if (WhatToDoClass->objectName().isEmpty())
            WhatToDoClass->setObjectName(QStringLiteral("WhatToDoClass"));
        WhatToDoClass->resize(959, 692);
        centralWidget = new QWidget(WhatToDoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        background = new QDeclarativeView(centralWidget);
        background->setObjectName(QStringLiteral("background"));
        background->setGeometry(QRect(-1, -1, 962, 693));
        background->setSource(QUrl("UI Files/Background.qml"));
        buttonRedo = new QDeclarativeView(centralWidget);
        buttonRedo->setObjectName(QStringLiteral("buttonRedo"));
        buttonRedo->setGeometry(QRect(460, 10, 78, 46));
        buttonRedo->setSource(QUrl("UI Files/Button_Redo.qml"));
        buttonUndo = new QDeclarativeView(centralWidget);
        buttonUndo->setObjectName(QStringLiteral("buttonUndo"));
        buttonUndo->setGeometry(QRect(380, 10, 78, 46));
        buttonUndo->setSource(QUrl("UI Files/Button_Undo.qml"));
        buttonAgendaview = new QDeclarativeView(centralWidget);
        buttonAgendaview->setObjectName(QStringLiteral("buttonAgendaview"));
        buttonAgendaview->setGeometry(QRect(20, 10, 91, 46));
        buttonAgendaview->setSource(QUrl("UI Files/Button_Agendaview.qml"));
        buttonCalendarview = new QDeclarativeView(centralWidget);
        buttonCalendarview->setObjectName(QStringLiteral("buttonCalendarview"));
        buttonCalendarview->setGeometry(QRect(120, 10, 92, 46));
        buttonCalendarview->setSource(QUrl("UI Files/Button_Calendarview.qml"));
        displayAgendaviewFloat = new QWebView(centralWidget);
        displayAgendaviewFloat->setObjectName(QStringLiteral("displayAgendaviewFloat"));
        displayAgendaviewFloat->setGeometry(QRect(35, 80, 334, 480));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(displayAgendaviewFloat->sizePolicy().hasHeightForWidth());
        displayAgendaviewFloat->setSizePolicy(sizePolicy);
        displayAgendaviewFloat->setUrl(QUrl(QStringLiteral("about:blank")));
        commandLine = new QTextEdit(centralWidget);
        commandLine->setObjectName(QStringLiteral("commandLine"));
        commandLine->setGeometry(QRect(34, 594, 891, 37));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(9);
        commandLine->setFont(font);
        commandLine->setFrameShape(QFrame::NoFrame);
        messageFeedback = new QDeclarativeView(centralWidget);
        messageFeedback->setObjectName(QStringLiteral("messageFeedback"));
        messageFeedback->setGeometry(QRect(50, 440, 320, 155));
        messageFeedback->setFocusPolicy(Qt::NoFocus);
        messageFeedback->setInteractive(false);
        messageFeedback->setSource(QUrl("UI Files/Msgbox_Feedback.qml"));
        displayAgendaviewTimed = new QWebView(centralWidget);
        displayAgendaviewTimed->setObjectName(QStringLiteral("displayAgendaviewTimed"));
        displayAgendaviewTimed->setGeometry(QRect(394, 80, 535, 481));
        displayAgendaviewTimed->setUrl(QUrl(QStringLiteral("about:blank")));
        statusBar = new QTextEdit(centralWidget);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setGeometry(QRect(30, 640, 891, 37));
        statusBar->setFont(font);
        statusBar->setFrameShape(QFrame::NoFrame);
        statusBar->setReadOnly(true);
        commandSearch = new QTextEdit(centralWidget);
        commandSearch->setObjectName(QStringLiteral("commandSearch"));
        commandSearch->setGeometry(QRect(630, 16, 301, 35));
        commandSearch->setFont(font);
        commandSearch->setFrameShape(QFrame::NoFrame);
        calendarframe = new QFrame(centralWidget);
        calendarframe->setObjectName(QStringLiteral("calendarframe"));
        calendarframe->setGeometry(QRect(20, 70, 921, 508));
        calendarframe->setFrameShape(QFrame::StyledPanel);
        calendarframe->setFrameShadow(QFrame::Raised);
        calendarbtn_prev = new QPushButton(centralWidget);
        calendarbtn_prev->setObjectName(QStringLiteral("calendarbtn_prev"));
        calendarbtn_prev->setGeometry(QRect(220, 10, 61, 41));
        calendarbtn_next = new QPushButton(centralWidget);
        calendarbtn_next->setObjectName(QStringLiteral("calendarbtn_next"));
        calendarbtn_next->setGeometry(QRect(290, 10, 61, 41));
        WhatToDoClass->setCentralWidget(centralWidget);
        calendarbtn_next->raise();
        calendarframe->raise();
        calendarbtn_prev->raise();
        background->raise();
        buttonRedo->raise();
        buttonUndo->raise();
        buttonAgendaview->raise();
        buttonCalendarview->raise();
        displayAgendaviewFloat->raise();
        commandLine->raise();
        displayAgendaviewTimed->raise();
        statusBar->raise();
        commandSearch->raise();
        messageFeedback->raise();

        retranslateUi(WhatToDoClass);

        QMetaObject::connectSlotsByName(WhatToDoClass);
    } // setupUi

    void retranslateUi(QMainWindow *WhatToDoClass)
    {
        WhatToDoClass->setWindowTitle(QApplication::translate("WhatToDoClass", "WhatToDo", 0));
        commandLine->setHtml(QApplication::translate("WhatToDoClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Calibri'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        statusBar->setHtml(QApplication::translate("WhatToDoClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Calibri'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Status:</p></body></html>", 0));
        calendarbtn_prev->setText(QApplication::translate("WhatToDoClass", "First", 0));
        calendarbtn_next->setText(QApplication::translate("WhatToDoClass", "Next", 0));
    } // retranslateUi

};

namespace Ui {
    class WhatToDoClass: public Ui_WhatToDoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHATTODO_H
