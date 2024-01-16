#ifndef SAMETABLEWIDGET_H
#define SAMETABLEWIDGET_H

#include <QTableView>

#include <QWidget>
#include "CustomModel.h"

namespace Ui {
class SameTableWidget;
}

class SameTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SameTableWidget(QWidget *parent = nullptr);
    ~SameTableWidget();

private:
    Ui::SameTableWidget *ui;
    QTableView* _tableView;
};

#endif // SAMETABLEWIDGET_H
