#ifndef __ADDDIALOG_H
#define __ADDDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(QWidget *parent = 0);

    QLineEdit *username;
    QLineEdit *password;
    QLineEdit *description;

private:
    QLabel *nameLabel;
    QLabel *passLabel;
    QLabel *desLabel;
    QPushButton *add;
    QPushButton *close;
};

#endif
