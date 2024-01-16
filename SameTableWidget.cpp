#include "SameTableWidget.h"
#include "ui_SameTableWidget.h"
#include <QStandardItemModel>


SameTableWidget::SameTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SameTableWidget)
{
    _tableView = new QTableView(this);
    ui->setupUi(this);
    auto x = new CustomModel(this);
    ui->verticalLayout->addWidget(_tableView);
    _tableView->setModel(x);
    connect(ui->pushButton,&QPushButton::clicked,this,[this,x](){
        x->removeAndRegenerateRows(ui->spinBox->value(),ui->spinBox_2->value());
    });
}

SameTableWidget::~SameTableWidget()
{
    delete ui;
}
