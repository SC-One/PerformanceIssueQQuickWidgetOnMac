#include "CustomModel.h"
#include <QRandomGenerator>
#include <QtConcurrent>
#include<QThread>

CustomModel::CustomModel(QObject *parent) : QStandardItemModel(parent) {

    qRegisterMetaType<QList<QList<QStandardItem*>>>("QList<QList<QStandardItem*>>");
    qRegisterMetaType<QList<QStandardItem*>>("QList<QStandardItem*>");

    for (int col = 2; col < columnCount(); col += 3) {
        setFontForColumn(col, generateRandomFont());
    }
    // Fill the model with random data in parallel
    connect(this, &CustomModel::created, this, [this](QList<QList<QStandardItem*>> allItems) {
        auto const rows = allItems.size();
        auto  const cols = allItems.size()>0 ? allItems[0].size() : 0;
        // Set the items to the model
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                setItem(row, col, allItems[row][col]);
            }
        }
    });
    connect(this,&CustomModel::insertNewRow ,this,[this](int row){
        insertRow(row);
    });
    connect(this,&CustomModel::setNewItem , this,
            [this](int row, QList<QStandardItem*> items){
//        qDebug()<<rowCount();
        for (int col = 0; col < items.size(); ++col) {
            setItem(row, col, items[col]);
        }
    });
}

void CustomModel::removeAndRegenerateRows(int rows , int cols) {
    removeRows(0, rowCount());
    generateRandomData(rows, cols);
}

void CustomModel::setFontForColumn(int column, const QFont &font) {
    for (int row = 0; row < rowCount(); ++row) {
        QStandardItem *item = new QStandardItem();
        item->setFont(font);
        setItem(row, column, item);
    }
}

QFont CustomModel::generateRandomFont() {
    QFont font;
    font.setBold(QRandomGenerator::global()->generate() % 2 == 0);
    font.setItalic(QRandomGenerator::global()->generate() % 2 == 0);
    font.setPointSize(QRandomGenerator::global()->bounded(8, 16));
    return font;
}

QString CustomModel::generateRandomText() {
    const QString chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    const int length = QRandomGenerator::global()->bounded(5, 15);

    QString randomText;
    for (int i = 0; i < length; ++i) {
        randomText.append(chars.at(QRandomGenerator::global()->bounded(chars.length())));
    }

    return randomText;
}

void CustomModel::generateRandomData(int rows ,int cols) {
    _resumeLast = false;
    _lastFuture.waitForFinished();
    _resumeLast = true;
    _lastFuture = QtConcurrent::run([=]() {
        for (int row = 0; (row < rows) && _resumeLast; ++row) {
            QList<QStandardItem*> rowItems;
            emit insertNewRow(row);

            for (int col = 0; col < cols; ++col) {
                QStandardItem *item = new QStandardItem(CustomModel::generateRandomText());
                rowItems.append(item);

                // Set custom font for every 3rd column
                if ((col - 2) % 3 == 0) {
                    item->setFont(CustomModel::generateRandomFont());
                }
            }
            if(!_resumeLast)
                break;
            QThread::msleep(10);
            emit setNewItem(row,rowItems);
        }
    });
}
