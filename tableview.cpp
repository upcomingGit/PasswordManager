#include "tableview.h"
#include <QMessageBox>
#include <QFile>
#include <QDataStream>

TableView::TableView(QWidget *parent) : QTableView(parent)
{
    passModel = new PasswordModel;
    setModel(passModel);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    show();
}

void TableView::readFromFile(QString filename)
{
    QFile file(filename);
    
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return ;
    }

    QList<QPair<QString, QString> > list = passModel->getList();
    QList<QString> description = passModel->getDescription();
    QDataStream in(&file);
    in >> description >> list;

    int i;

    if (list.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Nothing exists in the file"));
        return ;
    }
    else
    {
        for (i=0; i<list.size(); i++)
        {
            QPair<QString, QString> pair = list.at(i);
            addAction(description.at(i), pair.first, pair.second);
        }
    }
}

void TableView::saveToFile(QString filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("No such file exists"), tr("Couldnt open file for writing"));
    }

    QList<QPair<QString, QString> > list = passModel->getList();
    QList<QString> description = passModel->getDescription();
    QDataStream out(&file);
    out << description << list;

    file.close();
}

void TableView::addAction()
{
    AddDialog dialog;

    if (dialog.exec())
    {
        QString description = dialog.description->text();
        QString username = dialog.username->text();
        QString password = dialog.password->text();

        addAction(description, username, password);
    }
}

void TableView::addAction(QString description, QString username, QString password)
{
    QList<QPair<QString, QString> > list = passModel->getList();
    QPair<QString, QString> pair(username, password);

    if (!list.contains(pair))
    {
        passModel->insertRows(0, 1, QModelIndex());
        QModelIndex a = passModel->index(0, 0, QModelIndex());
        passModel->setData(a, description, Qt::EditRole);
        a = passModel->index(0, 1, QModelIndex());
        passModel->setData(a, username, Qt::EditRole);
        a = passModel->index(0, 2, QModelIndex());
        passModel->setData(a, password, Qt::EditRole);
    }
    else
    {
        QMessageBox::information(this, tr("Duplicate Name"), tr("The name %1 already exists").arg(username));
    }
}

void TableView::modAction()
{
    QModelIndexList indexes = selectionModel()->selectedIndexes();
    if (indexes.isEmpty())
        return;
    QModelIndex index, index1;
    index = indexes.at(0);
    index1 = passModel->index(index.row(), 0, QModelIndex());
    QString username, password, description;
    QVariant varName = passModel->data(index1, Qt::DisplayRole);
    description = varName.toString();
    index1 = passModel->index(index.row(), 1, QModelIndex());
    varName = passModel->data(index1, Qt::DisplayRole);
    username = varName.toString();
    index1 = passModel->index(index.row(), 2, QModelIndex());
    varName = passModel->data(index1, Qt::DisplayRole);
    password = varName.toString();

    AddDialog dialog;
    dialog.setWindowTitle(tr("Edit a contact"));
    dialog.description->setText(description);
    dialog.username->setText(username);
    dialog.password->setText(password);

    if (dialog.exec())
    {
        QString descripMod = dialog.description->text();
        QString usernameMod = dialog.username->text();
        QString passwordMod = dialog.password->text();
        index1 = passModel->index(index.row(), 0, QModelIndex());
        passModel->setData(index1, descripMod, Qt::EditRole);
        index1 = passModel->index(index.row(), 1, QModelIndex());
        passModel->setData(index1, usernameMod, Qt::EditRole);
        index1 = passModel->index(index.row(), 2, QModelIndex());
        passModel->setData(index1, passwordMod, Qt::EditRole);
    }
}

void TableView::delAction()
{
    QModelIndexList indexes = selectionModel()->selectedIndexes();
    if (indexes.isEmpty())
        return;
    QModelIndex index;
    index = indexes.at(0);
    int pos = index.row();
    passModel->removeRows(pos, 1, QModelIndex());
}
