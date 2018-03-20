#include "new_supplier.h"
#include "ui_new_supplier.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>

new_supplier::new_supplier(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::new_supplier)
{
    ui->setupUi(this);
}

new_supplier::~new_supplier()
{
    delete ui;
}


void new_supplier::on_customerType_comboBox_mainData_currentTextChanged(const QString &text)
{
    if(text == QString("Pessoa Física"))
    {
        ui->cpf_lineEdit_mainData->setDisabled(false);
        ui->rg_lineEdit_mainData->setDisabled(false);
        ui->cnpj_lineEdit_mainData->setDisabled(true);
        ui->stateInscription_lineEdit_mainData->setDisabled(true);
    }
    else
    {
        ui->cpf_lineEdit_mainData->setDisabled(true);
        ui->rg_lineEdit_mainData->setDisabled(true);
        ui->cnpj_lineEdit_mainData->setDisabled(false);
        ui->stateInscription_lineEdit_mainData->setDisabled(false);
    }
}

void new_supplier::on_action_register_supplier_triggered()
{
    QSqlDatabase::database();
    QSqlQuery query;
    query.exec("CREATE EXTENSION citext;");
    query.exec("CREATE SCHEMA Registrations;");
    query.exec("create table Registrations.Supplier"
              "(colname SERIAL primary key, "
              "name CITEXT, "
              "customerType varchar(100), "
              "cpf varchar(100), "
              "cnpj varchar(100), "
              "state_inscription varchar(100), "
              "cep varchar(100), "
              "address CITEXT, "
              "number varchar(100), "
              "complement CITEXT, "
              "neighborhood CITEXT, "
              "city CITEXT, "
              "state CITEXT, "
              "landline_phone varchar(100), "
              "additional_phone varchar(100), "
              "cell_phone varchar(100), "
              "note CITEXT, "
              "email varchar(100))");

    //save values to customer table
    query.prepare("INSERT INTO Registrations.Supplier (name, customerType, cpf, cnpj, state_inscription, cep, address, number, complement, neighborhood, city, state, landline_phone, additional_phone, cell_phone, note, email) "
                  "VALUES (:name, :customerType, :cpf, :cnpj, :state_inscription, :cep, :address, :number, :complement, :neighborhood, :city, :state, :landline_phone, :additional_phone, :cell_phone, :note, :email)");
    query.bindValue(":name", ui->name_lineEdit_mainData->text());
    query.bindValue(":customerType", ui->customerType_comboBox_mainData->currentText());
    query.bindValue(":cpf", ui->cpf_lineEdit_mainData->text());
    query.bindValue(":cnpj", ui->cnpj_lineEdit_mainData->text());
    query.bindValue(":state_inscription", ui->stateInscription_lineEdit_mainData->text());
    query.bindValue(":cep", ui->cep_lineEdit_mainData->text());
    query.bindValue(":address", ui->address_lineEdit_mainData->text());
    query.bindValue(":number", ui->number_lineEdit_mainData->text());
    query.bindValue(":complement", ui->complement_lineEdit_mainData->text());
    query.bindValue(":neighborhood", ui->neighborhood_lineEdit_mainData->text());
    query.bindValue(":city", ui->city_lineEdit_mainData->text());
    query.bindValue(":state", ui->uf_lineEdit_mainData->text());
    query.bindValue(":landline_phone", ui->landlinePhone_lineEdit_mainData->text());
    query.bindValue(":additional_phone", ui->additionalPhone_lineEdit_mainData->text());
    query.bindValue(":cell_phone", ui->cellPhone_lineEdit_mainData->text());
    query.bindValue(":note", ui->note_addtionalInfo->toPlainText());
    query.bindValue(":email", ui->email_lineEdit_additionalInfo->text());
    query.exec();

}
