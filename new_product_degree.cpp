#include "new_product_degree.h"
#include "ui_new_product_degree.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QMessageBox>

new_product_degree::new_product_degree(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_product_degree)
{
    ui->setupUi(this);
}

new_product_degree::~new_product_degree()
{
    delete ui;
}

void new_product_degree::on_add_pushButton_clicked()
{
    ui->DegreeTableWidget->insertRow(ui->DegreeTableWidget->rowCount());
    int row = ui->DegreeTableWidget->rowCount() - 1;
    ui->DegreeTableWidget->setItem(row, Grade, new QTableWidgetItem(ui->degree_lineEdit->text()));
    ui->DegreeTableWidget->setItem(row, Grupo, new QTableWidgetItem(ui->group_lineEdit->text()));
    ui->DegreeTableWidget->setItem(row, Subgrupo, new QTableWidgetItem(ui->subgroup_lineEdit->text()));
}

void new_product_degree::on_register_pushButton_clicked()
{
    QSqlDatabase::database();
    QSqlQuery query;

    /*

    |Scheme    |Table    |column   |Reserved words|two words|
    |----------|---------|---------|--------------|---------|
    |Plural    |Singular |singular |UPPERCASE     |underline|
    |Capitalize|Captalize|lowercase|

    */


    query.exec("CREATE EXTENSION citext;");
    query.exec("CREATE SCHEMA Registrations;");
    query.exec("CREATE TABLE Registrations.Product_Degree"
              "(colname SERIAL primary key, "
              "degreeID  CITEXT, "
              "groupID  CITEXT, "
              "subgroupID  CITEXT)");

    //Product Degree Registration
    for (int i=0; i < ui->DegreeTableWidget->rowCount(); i++) {
    query.prepare("INSERT INTO Registrations.Product_Degree (degreeID, groupID, subgroupID) "
                  "VALUES (:degreeID, :groupID, :subgroupID)");
    query.bindValue(":degreeID", ui->DegreeTableWidget->item(i, 0)->text());
    query.bindValue(":groupID", ui->DegreeTableWidget->item(i, 1)->text());
    query.bindValue(":subgroupID", ui->DegreeTableWidget->item(i, 2)->text());
    query.exec();
    }

    //mensagem após salvar os dados
    QMessageBox msgBox;
    msgBox.setWindowTitle("Cadastro de Grade.");
    msgBox.setText("Cadastro de Grade Salvo com Sucesso!");
    msgBox.exec();


    //clear


    //close window after finish the registration
    this->close();
}
