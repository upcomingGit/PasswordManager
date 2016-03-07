#include "adddialog.h"

#include <QGridLayout>

AddDialog::AddDialog(QWidget *parent) : QDialog(parent)
{
    nameLabel = new QLabel("Username");
    passLabel = new QLabel("Password");
    add = new QPushButton("Add");
    close = new QPushButton("Close");

    username = new QLineEdit;
    password = new QLineEdit;

    setWindowTitle("Add a password entry");

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(username, 0, 1);
    gLayout->addWidget(passLabel, 1, 0);
    gLayout->addWidget(password, 1, 1);

    QHBoxLayout *boxLayout = new QHBoxLayout;

    boxLayout->addWidget(add);
    boxLayout->addWidget(close);

    gLayout->addLayout(boxLayout, 2, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(add, SIGNAL(clicked()), this, SLOT(accept()));
    connect(close, SIGNAL(clicked()), this, SLOT(reject()));
}
