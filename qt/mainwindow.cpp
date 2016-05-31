/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

//! [0]
#include <QtWidgets>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonValue>
#include <QJsonDocument>
#include <QByteArray>

#include <bitmailcore/bitmail.h>

#include "mainwindow.h"
//! [0]

#include "optiondialog.h"
#include "logindialog.h"
#include "main.h"

//! [1]
MainWindow::MainWindow(const QString & email, const QString & passphrase)
    : m_bitmail(new BitMail())
//! [1] //! [2]
{
    (void)email; (void)passphrase;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QHBoxLayout *mainLayout = new QHBoxLayout;
    blist = new QListWidget;
    leftLayout->addWidget(blist);
    mainLayout->addLayout(leftLayout);

    QVBoxLayout * rightLayout = new QVBoxLayout;

    mlist = new QListWidget;
    textEdit = new QTextEdit;

    QHBoxLayout * btnLayout = new QHBoxLayout;
    btnSend = new QPushButton(tr("Send"));
    btnSend->setFixedWidth(64);
    btnSend->setFixedHeight(32);
    connect(btnSend, SIGNAL(clicked()), this, SLOT(onSendBtnClicked()));

    btnLayout->addWidget(btnSend);
    btnLayout->setAlignment(btnSend, Qt::AlignLeft);

    mainLayout->addLayout(rightLayout);

    QWidget * wrap = new QWidget(this);
    wrap->setLayout(mainLayout);
    setCentralWidget(wrap);

    createActions();
    createToolBars();
    createStatusBar();

    rightLayout->addWidget(mlist);
    rightLayout->addWidget(chatToolbar);
    rightLayout->addWidget(textEdit);
    rightLayout->addLayout(btnLayout);

    connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));

#if defined(MACOSX)
    setUnifiedTitleAndToolBarOnMac(true);
#endif

    setWindowIcon(QIcon(":/images/bitmail.png"));
    setWindowTitle(tr("BitMail"));
}
//! [2]

MainWindow::~MainWindow()
{
    if (m_bitmail != NULL){
        BMQTApplication::SaveProfile(m_bitmail);
        delete m_bitmail;
        m_bitmail = NULL;
    }
}

//! [3]
void MainWindow::closeEvent(QCloseEvent *event)
//! [3] //! [4]
{
    event->accept();    
}
//! [4]

//! [17]
void MainWindow::createActions()
//! [17] //! [18]
{
    do {
        configAct = new QAction(QIcon(":/images/config.png"), tr("&Configure"), this);
        configAct->setStatusTip(tr("Configure current account"));
        connect(configAct, SIGNAL(triggered()), this, SLOT(onConfigBtnClicked()));
    }while(0);

    do {
        addAct = new QAction(QIcon(":/images/add.png"), tr("&Add"), this);
        addAct->setStatusTip(tr("Add a new buddy by certificate or certificate ID."));
    }while(0);

    do {
        inviteAct = new QAction(QIcon(":/images/invite.png"), tr("&Invite"), this);
        inviteAct->setStatusTip(tr("Invite a new friend by send a request message."));
    }while(0);

    do{
        snapAct = new QAction(QIcon(":/images/snap.png"), tr("&Snapshot"), this);
        snapAct->setStatusTip(tr("Snapshot"));
        snapAct->setEnabled(false);
    }while(0);

    do{
        fileAct = new QAction(QIcon(":/images/file.png"), tr("&File"), this);
        fileAct->setStatusTip(tr("File"));
        fileAct->setEnabled(false);
    }while(0);

    do{
        emojAct = new QAction(QIcon(":/images/emoj.png"), tr("&Emoji"), this);
        emojAct->setStatusTip(tr("Emoji"));
        emojAct->setEnabled(false);
    }while(0);

    do{
        soundAct = new QAction(QIcon(":/images/sound.png"), tr("&Sound"), this);
        soundAct->setStatusTip(tr("Sound"));
        soundAct->setEnabled(false);
    }while(0);

    do{
        videoAct = new QAction(QIcon(":/images/video.png"), tr("&Video"), this);
        videoAct->setStatusTip(tr("Video"));
        videoAct->setEnabled(false);
    }while(0);

    do{
        styleAct = new QAction(QIcon(":/images/style.png"), tr("&Font"), this);
        connect(styleAct, SIGNAL(triggered()), this, SLOT(onStyleBtnClicked()));
        styleAct->setStatusTip(tr("Font"));
    }while(0);

    do{
        colorAct = new QAction(QIcon(":/images/color.png"), tr("&Color"), this);
        connect(colorAct, SIGNAL(triggered()), this, SLOT(onColorBtnClicked()));
        colorAct->setStatusTip(tr("Color"));
    }while(0);

    do{
        liveAct = new QAction(QIcon(":/images/live.png"), tr("&Live"), this);
        liveAct->setStatusTip(tr("Live"));
        liveAct->setEnabled(false);
    }while(0);

    do{
        textAct = new QAction(QIcon(":/images/text.png"), tr("&Text"), this);
        textAct->setStatusTip(tr("Text"));
        textAct->setCheckable(true);
        connect(textAct, SIGNAL(triggered(bool)), this, SLOT(onTextBtnClicked(bool)));
    }while(0);

    do{
        payAct = new QAction(QIcon(":/images/bitcoin.png"), tr("&Pay"), this);
        payAct->setStatusTip(tr("Pay by Bitcoin"));
        connect(payAct, SIGNAL(triggered(bool)), this, SLOT(onPayBtnClicked(bool)));
    }while(0);
}
//! [24]

//! [29] //! [30]
void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("Profile"));
    fileToolBar->addAction(configAct);

    editToolBar = addToolBar(tr("Buddies"));
    editToolBar->addAction(addAct);
    editToolBar->addAction(inviteAct);

    chatToolbar = addToolBar(tr("Chat"));
    chatToolbar->addAction(textAct);
    chatToolbar->addAction(styleAct);
    chatToolbar->addAction(colorAct);
    chatToolbar->addAction(emojAct);
    chatToolbar->addAction(snapAct);
    chatToolbar->addAction(fileAct);
    chatToolbar->addAction(soundAct);
    chatToolbar->addAction(videoAct);
    chatToolbar->addAction(liveAct);
    chatToolbar->addAction(payAct);
    chatToolbar->setIconSize(QSize(24,24));
}
//! [30]

//! [32]
void MainWindow::createStatusBar()
//! [32] //! [33]
{
    statusBar()->showMessage(tr("Ready"));
}
//! [33]


//! [48]
QString MainWindow::strippedName(const QString &fullFileName)
//! [48] //! [49]
{
    return QFileInfo(fullFileName).fileName();
}
//! [49]

void MainWindow::onStyleBtnClicked()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, textEdit->font());
    if (ok){
        textEdit->setFont(font);
    }
    return ;
}

void MainWindow::onColorBtnClicked()
{
    QColor color = QColorDialog::getColor(Qt::green, this, tr("Select Color"), QColorDialog::DontUseNativeDialog);
    textEdit->setTextColor(color);
    textEdit->setAutoFillBackground(true);
    return ;
}

void MainWindow::onTextBtnClicked(bool fchecked)
{
    styleAct->setEnabled(!fchecked);
    colorAct->setEnabled(!fchecked);
    //emojAct->setEnabled(!fchecked);
    //snapAct->setEnabled(!fchecked);
    //soundAct->setEnabled(!fchecked);
    //videoAct->setEnabled(!fchecked);
    //fileAct->setEnabled(!fchecked);
    return ;
}

void MainWindow::onStrangerBtnClicked(bool fchecked)
{
    if (fchecked){

    }
    return ;
}

void MainWindow::onSendBtnClicked()
{
    return ;
}

void MainWindow::onPayBtnClicked()
{
    return ;
}

void MainWindow::onConfigBtnClicked()
{
    OptionDialog optDialog(false, this);
    optDialog.SetEmail(QString::fromStdString(m_bitmail->GetEmail()));
    optDialog.SetNick(QString::fromStdString(m_bitmail->GetCommonName()));
    optDialog.SetPassphrase(QString::fromStdString(m_bitmail->GetPassphrase()));
    optDialog.SetBits(m_bitmail->GetBits());

    optDialog.SetSmtpUrl(QString::fromStdString(m_bitmail->GetTxUrl()));
    optDialog.SetSmtpLogin(QString::fromStdString(m_bitmail->GetTxLogin()));
    optDialog.SetSmtpPassword(QString::fromStdString(m_bitmail->GetTxPassword()));

    optDialog.SetImapUrl(QString::fromStdString(m_bitmail->GetRxUrl()));
    optDialog.SetImapLogin(QString::fromStdString(m_bitmail->GetRxLogin()));
    optDialog.SetImapPassword(QString::fromStdString(m_bitmail->GetRxPassword()));
    optDialog.SetImapAllowStranger(m_bitmail->AllowStranger());

    if (QDialog::Accepted != optDialog.exec()){
        return ;
    }
    return ;
}

//! [15]
void MainWindow::documentWasModified()
//! [15] //! [16]
{

}
//! [16]
