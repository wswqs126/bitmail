#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>

class QLineEdit;
class QPlainTextEdit;
class QPushButton;
class BitMail;
class QTextEdit;

namespace Ui {
class MessageDialog;
}

class MessageDialog : public QDialog
{
    Q_OBJECT

public:
    enum {
        ViewGroup = QDialog::Accepted + QDialog::Rejected,
    };

    explicit MessageDialog(BitMail * btimail, QWidget *parent = 0);
    ~MessageDialog();

    void SetFrom(const QString & qsFrom);
    QString GetFrom() const;

    void SetCertID(const QString & qsCertID);
    QString GetCertID() const;

    void SetMessage(const QString & qsMessage);
    QString GetMessage() const;

    void SetCert(const QString & qsCert);
    QString GetCert() const;

    void EnableMakeFriend(bool fEnable);

    void groupId(const QString & qsGroupId);
    QString groupId() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_btnMakeFriend_clicked();

    void on_btnViewGroup_clicked();

signals:
    void signalAddFriend(const QString & email);
    void signalViewGroup(const QString & gid);

private:
    Ui::MessageDialog *ui;
    BitMail * m_bitmail;

    QLineEdit * m_leFrom;
    QLineEdit * m_leCertID;
    QTextEdit * m_ptxtMessage;
    QPlainTextEdit * m_ptxtCert;
    QPushButton * m_btnMakeFriend;
    QLineEdit * m_leGroupId;
};
#endif // MESSAGEDIALOG_H
