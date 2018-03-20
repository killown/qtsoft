#include "cadastrar_cliente.h"
#include "ui_cadastrar_cliente.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QMessageBox>
#include <iostream>
#include <boost/format.hpp>
#include <boost/current_function.hpp>


void permission(){


}

cadastrar_cliente::cadastrar_cliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cadastrar_cliente)
{
    ui->setupUi(this);
}

cadastrar_cliente::~cadastrar_cliente()
{
    delete ui;
}




        //static QSqlQueryModel model;

        //QSqlQuery* qry=new QSqlQuery(db);
        //qry->prepare("select * from cep.log_logradouro where cep similar to '%(01156050)%'");
        //qry->exec();
        //model.setQuery(*qry);

        //ui->tableView->setModel(&model);    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
        //db.setHostName("127.0.0.1");
        //db.setDatabaseName("cep");
        //db.setUserName("postgres");
        //db.setPassword("223722");
        //.setPort(5432);

        //bool ok = db.open();
        //if(ok != true)
        //{
            //QMessageBox::information(this,"Connection","Connection Failed!") ;
        //}
        //else
        //{
            //QMessageBox::information(this,"Connection","Connection OK!") ;
        //QMessageBox::information(this,"Information","This Message box is needed in       order to see the rendered tableview!") ;





void cadastrar_cliente::on_cep_lineEdit_returnPressed()
{


    }


void cadastrar_cliente::on_cep_lineEdit_textChanged(const QString &arg1)
{
    ui->cep_lineEdit->setValidator( new QIntValidator(0, 9999999, this) );
}

void cadastrar_cliente::on_confirmar_cadastro_pushButton_clicked()
{
    QSqlDatabase::database();
    QSqlQuery query;

    query.exec("CREATE EXTENSION citext;");
    query.exec("CREATE SCHEMA Cadastros;");
    query.exec("create table Cadastros.Cliente"
              "(colname SERIAL primary key, "
              "nome  CITEXT, "
              "cpf varchar(100), "
              "cnpj varchar(100), "
              "insc_estadual varchar(100), "
              "cep varchar(100), "
              "endereco CITEXT, "
              "numero varchar(100), "
              "complemento CITEXT, "
              "bairro CITEXT, "
              "cidade CITEXT, "
              "estado CITEXT, "
              "telefone1 varchar(100), "
              "telefone2 varchar(100), "
              "celular varchar(100), "
              "email varchar(100))");
    query.prepare("INSERT INTO Cadastros.Cliente (nome, cpf, cnpj, insc_estadual, cep, endereco, numero, complemento, bairro, cidade, estado, telefone1, telefone2, celular, email) "
                  "VALUES (:nome, :cpf, :cnpj, :insc_estadual, :cep, :endereco, :numero, :complemento, :bairro, :cidade, :estado, :telefone1, :telefone2, :celular, :email)");
    query.bindValue(":nome", ui->nome_lineEdit->text());
    query.bindValue(":cpf", ui->cpf_lineEdit->text());
    query.bindValue(":cnpj", ui->cnpj_lineEdit->text());
    query.bindValue(":insc_estadual", ui->insc_estadual_lineEdit->text());
    query.bindValue(":cep", ui->cep_lineEdit->text());
    query.bindValue(":endereco", ui->endereco_lineEdit->text());
    query.bindValue(":numero", ui->numero_lineEdit->text());
    query.bindValue(":complemento", ui->complemento_lineEdit->text());
    query.bindValue(":bairro", ui->bairro_lineEdit->text());
    query.bindValue(":cidade", ui->cidade_lineEdit->text());
    query.bindValue(":estado", ui->estado_lineEdit->text());
    query.bindValue(":telefone1", ui->telefone1_lineEdit->text());
    query.bindValue(":telefone2", ui->telefone2_lineEdit->text());
    query.bindValue(":celular", ui->celular_lineEdit->text());
    query.bindValue(":email", ui->email_lineEdit->text());

    query.exec();

    //mensagem após salvar os dados
    QMessageBox msgBox;
    msgBox.setWindowTitle("Cadastro de Cliente.");
    msgBox.setText(QString("Novo Cliente %1 foi Adicionado!").arg(ui->nome_lineEdit->text()));
    msgBox.exec();
    //
}

void cadastrar_cliente::on_cep_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    QSqlDatabase::database();
    static QSqlQueryModel model;
    QString bairro_str;
    QString loc_nu_sequencial_str;


   //QSqlQuery* qry=new QSqlQuery(db);
   //QString a = QString("select log_nome from cep.log_logradouro where cep similar to '%1'").arg(ui->cep_lineEdit->text());

   QSqlQuery query(QString("SELECT * FROM cep.log_logradouro where cep = '%1'").arg(ui->cep_lineEdit->text()));
   int log_nome = query.record().indexOf("log_nome");
   int ufe_sg = query.record().indexOf("ufe_sg");
   int bai_nu_sequencial_ini  = query.record().indexOf("bai_nu_sequencial_ini");
   int loc_nu_sequencial = query.record().indexOf("loc_nu_sequencial");
   while (query.next()) {
       QString log_nome_str = query.value(log_nome).toString();
       QString ufe_sg_str = query.value(ufe_sg).toString();
       loc_nu_sequencial_str = query.value(loc_nu_sequencial).toString();
       bairro_str = query.value(bai_nu_sequencial_ini).toString();
       ui->endereco_lineEdit->setText(log_nome_str);
       ui->estado_lineEdit->setText(ufe_sg_str);

   }
   //msgBox.setText(bairro_str);
   //msgBox.exec();
   QSqlQuery bairro_query(QString("SELECT * FROM cep.log_bairro where bai_nu_sequencial = %1").arg(bairro_str));
   int bai_no  = bairro_query.record().indexOf("bai_no");
   while (bairro_query.next()) {
       QString bai_no_str = bairro_query.value(bai_no).toString();
       ui->bairro_lineEdit->setText(bai_no_str);
   }


   QSqlQuery cidade_query(QString("SELECT * FROM cep.log_localidade where loc_nu_sequencial = %1").arg(loc_nu_sequencial_str));
   int loc_nosub  = cidade_query.record().indexOf("loc_nosub");
   while (cidade_query.next()) {
       QString loc_nosub_str  = cidade_query.value(loc_nosub).toString();
       ui->cidade_lineEdit->setText(loc_nosub_str);
   }

   //qry->prepare(a);
   //qry->exec();
   //model.setQuery(*qry);

   //
   //ui->tableView->setModel(&model);
}
