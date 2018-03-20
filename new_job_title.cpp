#include "new_job_title.h"
#include "ui_new_job_title.h"
#include <QDebug>
#include <QTableWidget>

new_job_title::new_job_title(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::new_job_title)
{
    ui->setupUi(this);
    jobTitle_table = ui->jobTitle_tableWidget;
}

new_job_title::~new_job_title()
{
    delete ui;
}

void new_job_title::on_addTitle_pushButton_clicked()
{
    jobTitle_table->insertRow(ui->jobTitle_tableWidget->rowCount());
    int row = jobTitle_table->rowCount() - 1;
    jobTitle_table->setItem(row, name, new QTableWidgetItem(ui->name_lineEdit->text()));
    jobTitle_table->setItem(row, description, new QTableWidgetItem(ui->description_lineEdit->text()));
}

void new_job_title::on_jobTitle_tableWidget_clicked(const QModelIndex &index)
{
    jobTitle_table->removeRow(index.row());
}
