#include "passwordmodel.h"

PasswordModel::PasswordModel(QObject *parent) : QAbstractTableModel(parent)
{}

int PasswordModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return list.size();
}

int PasswordModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return NUMBEROFCOLUMNS;
}

QVariant PasswordModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= list.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        QPair<QString, QString> pair = list.at(index.row());
        QString descrip = description.at(index.row());

        if (index.column() == 0)
        {
            return descrip;
        }
        if (index.column() == 1)
        {
            return pair.first;
        }
        else if (index.column() == 2)
        {
            return pair.second;
        }
    }
    return QVariant();
}

QVariant PasswordModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        if (section == 0)
        {
            return tr("Description");
        }
        else if (section == 1)
        {
            return tr("Username");
        }
        else if (section == 2)
            return tr("Password");
    }
    return QVariant();
}

Qt::ItemFlags PasswordModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool PasswordModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);
    int i;
    for (i=0; i<rows; i++)
    {
        QPair<QString, QString> pair("", "");
        QString descrip("");
        list.insert(position, pair);
        description.insert(position, descrip);
    }
    endInsertRows();
    return true;
}

bool PasswordModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    int i;
    for (i=0; i<rows; i++)
    {
        list.removeAt(position);
        description.removeAt(position);
    }
    endRemoveRows();
    return true;
}

bool PasswordModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        int row = index.row();
        QPair<QString, QString> pair = list.value(row);
        QString descrip = description.value(row);
        if (index.column() == 0)
        {
            descrip = value.toString();
        }
        else if (index.column() == 1)
        {
            pair.first = value.toString();
        }
        else if (index.column() == 2)
        {
            pair.second = value.toString();
        }
        else
            return false;

        description.replace(row, descrip);
        list.replace(row, pair);
        emit(dataChanged(index, index));
        return true;
    }
    return false;
}
QList<QPair<QString, QString> > PasswordModel::getList()
{
    return list;
}

QList<QString> PasswordModel::getDescription()
{
    return description;
}
