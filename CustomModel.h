#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H
#include <QFuture>

#include <QStandardItemModel>
#include <QFont>
#include <atomic>

class CustomModel : public QStandardItemModel {
    Q_OBJECT

public:
    CustomModel(QObject *parent = nullptr);

    // API to remove all rows and regenerate random data
    void removeAndRegenerateRows(int rows = 3000,int cols = 12);


signals:
    void created(QList<QList<QStandardItem*>> allItems);
    void insertNewRow(int row);
    void setNewItem(int row,QList<QStandardItem*> items);
private:
    void setFontForColumn(int column, const QFont &font);
   static  QFont generateRandomFont();
   static  QString generateRandomText();

    // Generate random data for all rows
    void generateRandomData(int rows , int cols);
   std::atomic_bool _resumeLast = true;
   QFuture<void> _lastFuture;
};

#endif // CUSTOMMODEL_H
