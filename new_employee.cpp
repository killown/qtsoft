#include "new_employee.h"
#include "ui_new_employee.h"
#include <qdebug.h>
#include <QTableWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>
#include <QDateEdit>
#include <allow_or_not.h>
#include <new_job_title.h>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QtSql>

new_employee::new_employee(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::new_employee)
{
    ui->setupUi(this);
    ui->addmissionDate_dateEdit->setDate(QDate::currentDate());


    //dependents QtableWidget
    m_pTableWidget = ui->dependent_detableWidget_dependents;
}

new_employee::~new_employee()
{
    delete ui;
}

void new_employee::on_gender_comboBox_mainData_currentTextChanged(const QString &arg1)
{
    //clear the marital status and then add a list based on the gender
    if(ui->gender_comboBox_mainData->currentText() == QString("Feminino")){
            qDebug() << "pois é mano flw";
            QStringList feminino;
            feminino << "Solteira" << "Casada" << "Divorciada" << "Viúva";
            ui->marital_statux_comboBox_mainData->clear();
            ui->marital_statux_comboBox_mainData->addItems(feminino);
    }


    if(ui->gender_comboBox_mainData->currentText() == QString("Masculino")){
            qDebug() << "pois é mano flw";
            QStringList masculino;
            masculino << "Solteiro" << "Casado" << "Divorciado" << "Viúvo";
            ui->marital_statux_comboBox_mainData->clear();
            ui->marital_statux_comboBox_mainData->addItems(masculino);
    //------------------------------------------------------------------------------
    }
}

void new_employee::on_newDependent_pushButton_dependents_clicked()
{
    m_pTableWidget->insertRow(m_pTableWidget->rowCount());
    int row = m_pTableWidget->rowCount() - 1;
    m_pTableWidget->setItem(row, Dependente, new QTableWidgetItem(ui->name_lineEdit_dependents->text()));
    QString date = ui->birthDate_dateEdit_dependents->date().toString();
    m_pTableWidget->setItem(row, DataDeNascimento, new QTableWidgetItem(date) );

}

void new_employee::on_dependent_detableWidget_dependents_clicked(const QModelIndex &index)
{
    qDebug() << index;
    m_pTableWidget->removeRow(index.row());

}

void new_employee::on_pushButton_clicked()
{
    //sistema de permissão
    QStringList lista;
    // allow_or_not espera uma lista com o nome da função no index 0 e a ação da mensagem no index 1
    lista << Q_FUNC_INFO << "Cadastrar Cliente";
    // a função retorna true para liberado e falso para acesso negado.
    if (!allow_or_not(lista)){return;}
    // final do sistema de permissão

    //abre a janela depois de verificada a permissão
    static new_job_title w;
    w.show();
}

void new_employee::on_cep_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2)
{
    qDebug() << " ta aqui?";
    QSqlDatabase::database();
    static QSqlQueryModel model;
    QString bairro_str;
    QString loc_nu_sequencial_str;


   //QSqlQuery* qry=new QSqlQuery(db);
   //QString a = QString("select log_nome from cep.log_logradouro where cep similar to '%1'").arg(ui->cep_lineEdit->text());

   QSqlQuery query(QString("SELECT * FROM cep.log_logradouro where cep = '%1'").arg(ui->cep_lineEdit_mainData->text()));
   int log_nome = query.record().indexOf("log_nome");
   int ufe_sg = query.record().indexOf("ufe_sg");
   int bai_nu_sequencial_ini  = query.record().indexOf("bai_nu_sequencial_ini");
   int loc_nu_sequencial = query.record().indexOf("loc_nu_sequencial");
   while (query.next()) {
       QString log_nome_str = query.value(log_nome).toString();
       QString ufe_sg_str = query.value(ufe_sg).toString();
       loc_nu_sequencial_str = query.value(loc_nu_sequencial).toString();
       bairro_str = query.value(bai_nu_sequencial_ini).toString();

       //address
       ui->address_lineEdit_mainData->setText(log_nome_str);

       //uf
       ui->uf_lineEdit_mainData->setText(ufe_sg_str);


   }
   //msgBox.setText(bairro_str);
   //msgBox.exec();
   QSqlQuery bairro_query(QString("SELECT * FROM cep.log_bairro where bai_nu_sequencial = %1").arg(bairro_str));
   int bai_no  = bairro_query.record().indexOf("bai_no");
   while (bairro_query.next()) {
       QString bai_no_str = bairro_query.value(bai_no).toString();

       //neighborhood
       ui->neighborhood_lineEdit_mainData->setText(bai_no_str);
   }


   QSqlQuery cidade_query(QString("SELECT * FROM cep.log_localidade where loc_nu_sequencial = %1").arg(loc_nu_sequencial_str));
   int loc_nosub  = cidade_query.record().indexOf("loc_nosub");
   while (cidade_query.next()) {
       QString loc_nosub_str  = cidade_query.value(loc_nosub).toString();
       ui->city_lineEdit_mainData->setText(loc_nosub_str);

   }

}
