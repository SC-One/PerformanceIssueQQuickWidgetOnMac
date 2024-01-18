#ifndef CUSTOMQMLMODEL_H
#define CUSTOMQMLMODEL_H

#include <QAbstractListModel>
#include "CustomModel.h"

class CustomQmlModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum CustomRoles {
        TextRole = Qt::UserRole + 1,
        FontRole
    };

    explicit CustomQmlModel(QObject *parent = nullptr);

    // Required QAbstractListModel functions
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Expose your CustomModel functions to QML
    Q_INVOKABLE void removeAndRegenerateRows(int rows, int cols);

private:
    CustomModel m_customModel;
};

#endif // CUSTOMQMLMODEL_H
