#include "bradthread.h"
#include <bitmailcore/bitmail.h>
#include <QDebug>

BradThread::BradThread(BitMail * bitmail)
    : m_bitmail(bitmail)
    , m_fStopFlag(false)
{

}

void BradThread::run()
{
    if (!m_bitmail->StartupBrad()){
        qDebug() << "BradThread: Failed to startup brad";
        emit signalBradThDone();
        return ;
    }

    while(!m_fStopFlag){
        if( bmOk != m_bitmail->ListenBrad(1000)){
            qDebug() << "BradThread: Failed to Listen Brad Connections, break";
            break;
        }
    }

    m_bitmail->ShutdownBrad();
    qDebug() << "BradThread: Shutdown brad thread";

    emit signalBradThDone();
}

void BradThread::stop()
{
    m_fStopFlag = true;
}
