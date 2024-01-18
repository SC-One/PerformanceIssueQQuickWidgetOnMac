#include "CustomQmlModel.h"

CustomQmlModel::CustomQmlModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(&m_customModel, &CustomModel::dataChanged, this, [=] {
        // Notify QML that the data has changed
        emit dataChanged(index(0, 0), index(rowCount() - 1, 0));
    });
}

int CustomQmlModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_customModel.rowCount();
}

QVariant CustomQmlModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QStandardItem *item = m_customModel.item(index.row(), index.column());
    if (!item)
        return QVariant();

    switch (role) {
    case TextRole:
        return item->text();
    case FontRole:
        return item->font();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CustomQmlModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TextRole] = "text";
    roles[FontRole] = "font";
    return roles;
}

void CustomQmlModel::removeAndRegenerateRows(int rows, int cols)
{
    m_customModel.removeAndRegenerateRows(rows, cols);
}
