#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H
#include <QFuture>

#include <QStandardItemModel>
#include <QFont>
#include <atomic>

class CustomModel : public QStandardItemModel {
    Q_OBJECT
    Q_PROPERTY(QStringList roleNamesForQML READ roleNamesForQML
                   NOTIFY roleNamesForQMLChanged FINAL)

public:
    CustomModel(QObject *parent = nullptr);

    ~CustomModel();

    // API to remove all rows and regenerate random data
    Q_INVOKABLE void removeAndRegenerateRows(int rows = 3000,int cols = 12);
    Q_INVOKABLE QHash<int, QByteArray> myRoleNames() const;

    QHash<int, QByteArray> roleNames() const override
    {
        return { {Qt::DisplayRole, "display"} };
    }
    QStringList roleNamesForQML() const;

signals:
    void created(QList<QList<QStandardItem*>> allItems);
    void insertNewRow(int row);
    void setNewItem(int row,QList<QStandardItem*> items);
    void roleNamesForQMLChanged();

private:
   void setRoleNamesForQML(const QStringList &newRoleNamesForQML);
   void setFontForColumn(int column, const QFont &font);
   static  QFont generateRandomFont();
   static  QString generateRandomText();

   void stopThread();
   void updateRoleNames();
    // Generate random data for all rows
    void generateRandomData(int rows , int cols);


   std::atomic_bool _resumeLast = true;
   QFuture<void> _lastFuture;
   QStringList _roleNamesForQML;
};

#endif // CUSTOMMODEL_H
