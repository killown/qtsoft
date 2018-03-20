#include "change_customer.h"
#include "ui_change_customer.h"
#include <QSqlDatabase>
#include <QtSql>
#include <qmessagebox.h>

change_customer::change_customer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_customer)
{
    ui->setupUi(this);
}

change_customer::~change_customer()
{
    delete ui;
}



void change_customer::on_tableView_clicked(const QModelIndex &index)
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    QString row=ui->tableView->model()->data(index).toString();
    qDebug() << index;
    QMessageBox msgBox;

    // Multiple rows can be selected
    for(int i=0; i< selection.count(); i++)
    {
        QSqlDatabase::database();
        QModelIndex index = selection.at(i);
        QModelIndex id = ui->tableView->model()->index(index.row(), 0, QModelIndex());
        qDebug() << id.row();

        QString selected_row =  ui->tableView->model()->data(id).toString();
        qDebug() << selected_row;
        QSqlQuery query;
        query.prepare(QString("SELECT * FROM Registrations.Customer where id = %1").arg(selected_row));
        if(query.exec()){
            while(query.next()){
            ui->nome_lineEdit->setText(query.value(1).toString());
            ui->cpf_lineEdit->setText(query.value(2).toString());
            ui->cnpj_lineEdit->setText(query.value(3).toString());
            ui->insc_estadual_lineEdit->setText(query.value(4).toString());
            ui->cep_lineEdit->setText(query.value(5).toString());
            ui->endereco_lineEdit->setText(query.value(6).toString());
            ui->numero_lineEdit->setText(query.value(7).toString());
            ui->complemento_lineEdit->setText(query.value(8).toString());
            ui->bairro_lineEdit->setText(query.value(9).toString());
            ui->cidade_lineEdit->setText(query.value(10).toString());
            ui->estado_lineEdit->setText(query.value(11).toString());
            ui->telefone1_lineEdit->setText(query.value(12).toString());
            ui->telefone2_lineEdit->setText(query.value(13).toString());
            ui->celular_lineEdit->setText(query.value(14).toString());
            ui->email_lineEdit->setText(query.value(15).toString());
            }

        }
        else{

        }


        }


    }


void change_customer::on_localizar_lineEdit_returnPressed()
{
    static QSqlQueryModel model;
    static QSqlDatabase db = QSqlDatabase::database();
    QMessageBox msgBox;
    QSqlQuery query;





    //------------------------------------------------------------------------------
    //need to translate combobox from portuguese to english to use it in sql query
    QString translation;
    if (ui->comboBox->currentText() == "Nome"){
        translation = "name";
    }
    if (ui->comboBox->currentText() == "CPF"){
        translation = "cpf";
    }
    if (ui->comboBox->currentText() == "CNPJ"){
        translation = "cnpj";
    }

    if (ui->comboBox->currentText() == "CEP"){
        translation = "cep";
    }

    if (ui->comboBox->currentText() == "Endereço"){
        translation = "address";
    }
    if (ui->comboBox->currentText() == "Bairro"){
        translation = "neighborhood";
    }
    if (ui->comboBox->currentText() == "Telefone Fixo"){
        translation = "landline_phone";
    }

    if (ui->comboBox->currentText() == "Telefone Adicional"){
        translation = "additional_phone";
    }
    if (ui->comboBox->currentText() == "Celular"){
        translation = "cell_phone";
    }
    if (ui->comboBox->currentText() == "Email"){
        translation = "email";
    }



    query.prepare(QString("select * from Registrations.Customer where %1 similar to '%(%2)%'").arg(translation, ui->localizar_lineEdit->text()));
    query.exec();
    model.setQuery(query);


    ui->tableView->setModel(&model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setColumnHidden(6, true);
    ui->tableView->setColumnHidden(7, true);
    ui->tableView->setColumnHidden(8, true);
    ui->tableView->setColumnHidden(9, true);
    ui->tableView->setColumnHidden(12, true);
    ui->tableView->setColumnHidden(13, true);
    ui->tableView->setColumnHidden(14, true);
    ui->tableView->setColumnHidden(15, true);

    bool ok = db.open();
    if(ok != true)
    {
        //QMessageBox::information(this,"Connection","Connection Failed!") ;
    }
    else
    {
        //QMessageBox::information(this,"Connection","Connection OK!") ;
        //QMessageBox::information(this,"Information","This Message box is needed in       order to see the rendered tableview!") ;


}
}
