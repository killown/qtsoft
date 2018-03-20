#include "localizar_cliente.h"
#include "ui_localizar_cliente.h"
#include <QSqlDatabase>
#include <QtSql>
#include <qmessagebox.h>
#include <global.h>

QString username_loggedin;





// Handles Horizontal header

localizar_cliente::localizar_cliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::localizar_cliente)
{
    ui->setupUi(this);
}

localizar_cliente::~localizar_cliente()
{
    delete ui;
}

void localizar_cliente::on_tableView_doubleClicked(const QModelIndex &index)
{
    ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

void localizar_cliente::on_tableView_clicked(const QModelIndex &index)
{

    }




void localizar_cliente::on_search_lineEdit_returnPressed()
{
    qDebug() << QDateTime::currentDateTime();

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

    //------------------------------------------------------------------------------
    // query customer through the search_lineEdit
    QSqlQuery query;
    query.prepare(QString("select * from Registrations.Customer where %1 similar to '%(%2)%'")
                  .arg(translation, ui->search_lineEdit->text()));
    query.exec();

    //------------------------------------------------------------------------------
    // define the model and hide some columns
    static QSqlQueryModel model;
    model.setQuery(query);
    ui->tableView->setModel(&model);
    ui->tableView->setColumnHidden(0, true);

    /*
    if(translation != QString("cpf")){ ui->tableView->setColumnHidden(2, true);}
    if(translation != QString("address")){ ui->tableView->setColumnHidden(6, true);}
    if(translation != QString("number")){ ui->tableView->setColumnHidden(7, true);}
    if(translation != QString("complement")){ ui->tableView->setColumnHidden(8, true);}
    if(translation != QString("neighborhood")){ ui->tableView->setColumnHidden(9, true);}
    if(translation != QString("state")){ ui->tableView->setColumnHidden(11, true);}
    if(translation != QString("landiline_phone")){ ui->tableView->setColumnHidden(12, true);}
    if(translation != QString("additional_phone")){ ui->tableView->setColumnHidden(13, true);}
    if(translation != QString("cell_phone")){ ui->tableView->setColumnHidden(14, true);}
    if(translation != QString("email")){ ui->tableView->setColumnHidden(14, true);}
    */

    /*
    ui->tableView->setColumnHidden(7, true);
    ui->tableView->setColumnHidden(8, true);
    ui->tableView->setColumnHidden(9, true);
    ui->tableView->setColumnHidden(11, true);
    ui->tableView->setColumnHidden(12, true);
    ui->tableView->setColumnHidden(13, true);
    ui->tableView->setColumnHidden(14, true);
    ui->tableView->setColumnHidden(15, true);
    model.setHeaderData(1, Qt::Horizontal, QObject::tr("Nome"));
    */
    //------------------------------------------------------------------------------
}
