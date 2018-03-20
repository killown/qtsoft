#include "new_customer.h"
#include "ui_new_customer.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QMessageBox>
#include <QtWidgets>
#include <camera.h>


new_customer::new_customer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::new_customer)
{
    ui->setupUi(this);
    ui->menubar->hide();
}


//set blank thumb when closing the window
void new_customer::closeEvent(QCloseEvent *event)
{
    QString img = ":/images/blank.svg";
    QPixmap picture;
    picture.load(img);
    ui->pic_label_picture->setPixmap(picture);

//

}
new_customer::~new_customer()
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



void new_customer::on_actionSalvar_Cadastro_triggered()
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
    query.exec("create table Registrations.Customer"
              "(colname SERIAL primary key, "
              "name  CITEXT, "
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
              "email varchar(100))");



    query.exec("CREATE EXTENSION citext;");
    query.exec("CREATE SCHEMA Registrations;");
    query.exec("create table Registrations.Customer_Picture"
              "(colname SERIAL primary key, "
              "name  CITEXT, "
              "image  bytea)");



    query.exec("create table Registrations.Customer_Charge_Contact"
              "(colname SERIAL primary key, "
              "name varchar(100), "
              "cep varchar(100), "
              "address CITEXT, "
              "number varchar(100), "
              "complement CITEXT, "
              "neighborhood CITEXT, "
              "city CITEXT, "
              "state CITEXT, "
              "landline_phone varchar(100), "
              "additional_phone varchar(100), "
              "cell_phone varchar(100))");

    query.exec("create table Registrations.Customer_Deliver_Contact"
              "(colname SERIAL primary key, "
              "name varchar(100), "
              "cep varchar(100), "
              "address CITEXT, "
              "number varchar(100), "
              "complement CITEXT, "
              "neighborhood CITEXT, "
              "city CITEXT, "
              "state CITEXT, "
              "landline_phone varchar(100), "
              "additional_phone varchar(100), "
              "cell_phone varchar(100))");

    //save values to customer table
    query.prepare("INSERT INTO Registrations.Customer (name, cpf, cnpj, state_inscription, cep, address, number, complement, neighborhood, city, state, landline_phone, additional_phone, cell_phone, email) "
                  "VALUES (:name, :cpf, :cnpj, :state_inscription, :cep, :address, :number, :complement, :neighborhood, :city, :state, :landline_phone, :additional_phone, :cell_phone, :email)");
    query.bindValue(":name", ui->name_lineEdit_mainData->text());
    query.bindValue(":cpf", ui->cpf_lineEdit_mainData->text());
    query.bindValue(":cnpj", ui->cnpj_lineEdit_mainData->text());
    query.bindValue(":state_inscription", ui->inscriptionState_lineEdit_mainData->text());
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
    query.bindValue(":email", ui->email_lineEdit_additionalInfo->text());
    query.exec();


    //save values to charge table
    query.prepare("INSERT INTO Registrations.Customer_Charge_Contact (name, cep, address, number, complement, neighborhood, city, state, landline_phone, additional_phone, cell_phone) "
                  "VALUES (:name, :cep, :address, :number, :complement, :neighborhood, :city, :state, :landline_phone, :additional_phone, :cell_phone)");
    query.bindValue(":name", ui->name_lineEdit_mainData->text());
    query.bindValue(":cep", ui->cep_lineEdit_charge->text());
    query.bindValue(":address", ui->address_lineEdit_charge->text());
    query.bindValue(":number", ui->number_lineEdit_charge->text());
    query.bindValue(":complement", ui->complement_lineEdit_charge->text());
    query.bindValue(":neighborhood", ui->neighborhood_lineEdit_charge->text());
    query.bindValue(":city", ui->city_lineEdit_charge->text());
    query.bindValue(":state", ui->uf_lineEdit_charge->text());
    query.bindValue(":landline_phone", ui->landlinePhone_lineEdit_charge->text());
    query.bindValue(":additional_phone", ui->additionalPhone_lineEdit_charge->text());
    query.bindValue(":cell_phone", ui->cellPhone_lineEdit_charge->text());
    query.exec();



    //save values to delive table
    query.prepare("INSERT INTO Registrations.Customer_Deliver_Contact (name, cep, address, number, complement, neighborhood, city, state, landline_phone, additional_phone, cell_phone) "
                  "VALUES (:name, :cep, :address, :number, :complement, :neighborhood, :city, :state, :landline_phone, :additional_phone, :cell_phone)");
    query.bindValue(":name", ui->name_lineEdit_mainData->text());
    query.bindValue(":cep", ui->cep_lineEdit_deliver->text());
    query.bindValue(":address", ui->address_lineEdit_deliver->text());
    query.bindValue(":number", ui->number_lineEdit_deliver->text());
    query.bindValue(":complement", ui->complement_lineEdit_deliver->text());
    query.bindValue(":neighborhood", ui->neighborhood_lineEdit_deliver->text());
    query.bindValue(":city", ui->city_lineEdit_deliver->text());
    query.bindValue(":state", ui->uf_lineEdit_deliver->text());
    query.bindValue(":landline_phone", ui->landlinePhone_lineEdit_deliver->text());
    query.bindValue(":additional_phone", ui->additionalPhone_lineEdit_deliver->text());
    query.bindValue(":cell_phone", ui->cellPhone_lineEdit_deliver->text());
    query.exec();



    // Converting image to byte array:
    QString folder = QCoreApplication::applicationDirPath() + "/images";
    QString img = folder + "/new.jpg";
    QFile* file = new QFile(img);
    file->open(QIODevice::ReadOnly);
    QByteArray image = file->readAll();
    QString encoded = QString(image.toBase64());

    //insert picture
    query.prepare("INSERT INTO Registrations.Customer_Picture (name, image) "
                  "VALUES (:name, :image)");
    query.bindValue(":name", ui->name_lineEdit_mainData->text());
    query.bindValue(":image", encoded, QSql::In | QSql::Binary);

    query.exec();
    qDebug() << query.executedQuery();
    qDebug() << query.lastError();
    qDebug() << image.toBase64();


    //mensagem após salvar os dados
    QMessageBox msgBox;
    msgBox.setWindowTitle("Cadastro de Cliente.");
    msgBox.setText(QString("Novo Cliente %1 foi Adicionado!").arg(ui->name_lineEdit_mainData->text()));
    msgBox.exec();


    //clear
    ui->pic_label_picture->clear();
    ui->name_lineEdit_mainData->clear();
    ui->cpf_lineEdit_mainData->clear();
    ui->cnpj_lineEdit_mainData->clear();
    ui->inscriptionState_lineEdit_mainData->clear();
    ui->cep_lineEdit_mainData->clear();
    ui->address_lineEdit_mainData->clear();
    ui->number_lineEdit_mainData->clear();
    ui->complement_lineEdit_mainData->clear();
    ui->neighborhood_lineEdit_mainData->clear();
    ui->city_lineEdit_mainData->clear();
    ui->uf_lineEdit_mainData->clear();
    ui->landlinePhone_lineEdit_mainData->clear();
    ui->additionalPhone_lineEdit_mainData->clear();
    ui->cellPhone_lineEdit_mainData->clear();
    ui->email_lineEdit_additionalInfo->clear();

    ui->cep_lineEdit_charge->clear();
    ui->address_lineEdit_charge->clear();
    ui->number_lineEdit_charge->clear();
    ui->complement_lineEdit_charge->clear();
    ui->neighborhood_lineEdit_charge->clear();
    ui->city_lineEdit_charge->clear();
    ui->uf_lineEdit_charge->clear();
    ui->landlinePhone_lineEdit_charge->clear();
    ui->additionalPhone_lineEdit_charge->clear();
    ui->cellPhone_lineEdit_charge->clear();

    ui->cep_lineEdit_deliver->clear();
    ui->address_lineEdit_deliver->clear();
    ui->number_lineEdit_deliver->clear();
    ui->complement_lineEdit_deliver->clear();
    ui->neighborhood_lineEdit_deliver->clear();
    ui->city_lineEdit_deliver->clear();
    ui->uf_lineEdit_deliver->clear();
    ui->landlinePhone_lineEdit_deliver->clear();
    ui->additionalPhone_lineEdit_deliver->clear();
    ui->cellPhone_lineEdit_deliver->clear();

    //close window after finish the registration
    this->close();

}

void new_customer::camera_closed(const QString teste){
    QString folder = QCoreApplication::applicationDirPath() + "/images";
    QString image = folder + "/new.jpg";
    QPixmap pic (image);
    QPixmap newPic = pic.scaled(QSize(472, 354),  Qt::KeepAspectRatio);
    int w = ui->pic_label_picture->width();
    int h = ui->pic_label_picture->height();
    ui->pic_label_picture->setPixmap(newPic.scaled(w,h,Qt::KeepAspectRatio));
}

void new_customer::on_takepic_pushbutton_mainData_clicked()
{

    static Camera w;
    connect(&w, SIGNAL(enteredText(QString)),this, SLOT(camera_closed(const QString)));
    w.show();
}


void new_customer::on_cep_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2)
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

       if(ui->cep_lineEdit_charge->text().length() == 0){
       ui->address_lineEdit_charge->setText(log_nome_str);
       }

       if(ui->cep_lineEdit_deliver->text().length() == 0){
       ui->address_lineEdit_deliver->setText(log_nome_str);
       }

       //uf
       ui->uf_lineEdit_mainData->setText(ufe_sg_str);

       if(ui->cep_lineEdit_charge->text().length() == 0){
       ui->uf_lineEdit_charge->setText(ufe_sg_str);
       }

       if(ui->cep_lineEdit_deliver->text().length() == 0){
       ui->uf_lineEdit_deliver->setText(ufe_sg_str);
       }

       // define cep in charge and deliver tab

       if(ui->cep_lineEdit_charge->text().length() == 0){
       ui->cep_lineEdit_charge->setText(ui->cep_lineEdit_mainData->text());
       }

       if(ui->cep_lineEdit_deliver->text().length() == 0){
       ui->cep_lineEdit_deliver->setText(ui->cep_lineEdit_mainData->text());
       }
   }
   //msgBox.setText(bairro_str);
   //msgBox.exec();
   QSqlQuery bairro_query(QString("SELECT * FROM cep.log_bairro where bai_nu_sequencial = %1").arg(bairro_str));
   int bai_no  ;
   while (bairro_query.next()) {
       QString bai_no_str = bairro_query.value(bai_no).toString();

       //neighborhood
       ui->neighborhood_lineEdit_mainData->setText(bai_no_str);

       if(ui->cep_lineEdit_charge->text().length() == 0){
       ui->neighborhood_lineEdit_charge->setText(bai_no_str);
       }

       if(ui->cep_lineEdit_deliver->text().length() == 0){
       ui->neighborhood_lineEdit_deliver->setText(bai_no_str);
       }
   }


   QSqlQuery cidade_query(QString("SELECT * FROM cep.log_localidade where loc_nu_sequencial = %1").arg(loc_nu_sequencial_str));
   int loc_nosub  = cidade_query.record().indexOf("loc_nosub");
   while (cidade_query.next()) {
       QString loc_nosub_str  = cidade_query.value(loc_nosub).toString();
       ui->city_lineEdit_mainData->setText(loc_nosub_str);

       if(ui->cep_lineEdit_charge->text().length() == 0){
       ui->city_lineEdit_charge->setText(loc_nosub_str);
       }

       if(ui->cep_lineEdit_deliver->text().length() == 0){
       ui->city_lineEdit_deliver->setText(loc_nosub_str);
       }
   }

   //qry->prepare(a);
   //qry->exec();
   //model.setQuery(*qry);

   //
   //ui->tableView->setModel(&model);
}


void new_customer::on_landlinePhone_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2)
{

    //check if the phone is already in deliver and charge lineEdit, if not, then set it from mainData
    //without it, when mainData is changed will also change both deliver and charge

    //landline phone
    if(ui->landlinePhone_lineEdit_charge->text().length() != 14){
        QString phone = ui->landlinePhone_lineEdit_mainData->text();
        ui->landlinePhone_lineEdit_charge->setText(phone);
     }
    if(ui->landlinePhone_lineEdit_deliver->text().length() != 14){
        QString phone = ui->landlinePhone_lineEdit_mainData->text();
        ui->landlinePhone_lineEdit_deliver->setText(phone);
     }

    //
}


void new_customer::on_cellPhone_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2)
{
    //check if the phone is already in deliver and charge lineEdit, if not, then set it from mainData
    //without it, when mainData is changed will also change both deliver and charge
    //cell phone
    if(ui->cellPhone_lineEdit_charge->text().length() != 14){
        QString phone = ui->cellPhone_lineEdit_mainData->text();
        ui->cellPhone_lineEdit_charge->setText(phone);
     }
    if(ui->cellPhone_lineEdit_deliver->text().length() != 14){
        QString phone = ui->cellPhone_lineEdit_mainData->text();
        ui->cellPhone_lineEdit_deliver->setText(phone);
     }

    //
}

void new_customer::on_additionalPhone_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2)
{
    //check if the phone is already in deliver and charge lineEdit, if not, then set it from mainData
    //without it, when mainData is changed will also change both deliver and charge
    //additional phone
    if(ui->additionalPhone_lineEdit_charge->text().length() != 14){
        QString phone = ui->additionalPhone_lineEdit_mainData->text();
        ui->additionalPhone_lineEdit_charge->setText(phone);
     }
    if(ui->additionalPhone_lineEdit_deliver->text().length() != 14){
        QString phone = ui->additionalPhone_lineEdit_mainData->text();
        ui->additionalPhone_lineEdit_deliver->setText(phone);
     }

    //
}

void new_customer::on_number_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2)
{

    //if cep is changed, don't change the number
    if(ui->cep_lineEdit_mainData->text() == ui->cep_lineEdit_charge->text()){
        QString number = ui->number_lineEdit_mainData->text();
        ui->number_lineEdit_charge->setText(number);
     }
    if(ui->cep_lineEdit_mainData->text() == ui->cep_lineEdit_deliver->text()){
        QString number = ui->number_lineEdit_mainData->text();
        ui->number_lineEdit_deliver->setText(number);
     }
}


void new_customer::on_complement_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2)
{
    //if cep is changed, don't change the number
    if(ui->cep_lineEdit_mainData->text() == ui->cep_lineEdit_charge->text()){
        QString complement = ui->complement_lineEdit_mainData->text();
        ui->complement_lineEdit_charge->setText(complement);
     }
    if(ui->cep_lineEdit_mainData->text() == ui->cep_lineEdit_charge->text()){
        QString complement = ui->complement_lineEdit_mainData->text();
        ui->complement_lineEdit_deliver->setText(complement);
     }
}

void new_customer::on_cep_lineEdit_charge_cursorPositionChanged(int arg1, int arg2)
{
    QSqlDatabase::database();
    static QSqlQueryModel model;
    QString bairro_str;
    QString loc_nu_sequencial_str;

   QSqlQuery query(QString("SELECT * FROM cep.log_logradouro where cep = '%1'")
                   .arg(ui->cep_lineEdit_charge->text()));
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
       ui->address_lineEdit_charge->setText(log_nome_str);

       //uf
       ui->uf_lineEdit_charge->setText(ufe_sg_str);

   }

   QSqlQuery bairro_query(QString("SELECT * FROM cep.log_bairro where bai_nu_sequencial = %1").arg(bairro_str));
   int bai_no  = bairro_query.record().indexOf("bai_no");
   while (bairro_query.next()) {
       QString bai_no_str = bairro_query.value(bai_no).toString();

       //neighborhood
       ui->neighborhood_lineEdit_charge->setText(bai_no_str);
   }


   QSqlQuery cidade_query(QString("SELECT * FROM cep.log_localidade where loc_nu_sequencial = %1").arg(loc_nu_sequencial_str));
   int loc_nosub  = cidade_query.record().indexOf("loc_nosub");
   while (cidade_query.next()) {
       QString loc_nosub_str  = cidade_query.value(loc_nosub).toString();
       ui->city_lineEdit_charge->setText(loc_nosub_str);

   }

   // clear number and complement
   ui->complement_lineEdit_charge->setText("");
   ui->number_lineEdit_charge->setText("");

}

void new_customer::on_cep_lineEdit_deliver_cursorPositionChanged(int arg1, int arg2)
{
    QSqlDatabase::database();
    static QSqlQueryModel model;
    QString bairro_str;
    QString loc_nu_sequencial_str;

   QSqlQuery query(QString("SELECT * FROM cep.log_logradouro where cep = '%1'").arg(ui->cep_lineEdit_deliver->text()));
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
       ui->address_lineEdit_deliver->setText(log_nome_str);

       //uf
       ui->uf_lineEdit_deliver->setText(ufe_sg_str);

   }

   QSqlQuery bairro_query(QString("SELECT * FROM cep.log_bairro where bai_nu_sequencial = %1").arg(bairro_str));
   int bai_no  = bairro_query.record().indexOf("bai_no");
   while (bairro_query.next()) {
       QString bai_no_str = bairro_query.value(bai_no).toString();

       //neighborhood
       ui->neighborhood_lineEdit_deliver->setText(bai_no_str);
   }


   QSqlQuery cidade_query(QString("SELECT * FROM cep.log_localidade where loc_nu_sequencial = %1").arg(loc_nu_sequencial_str));
   int loc_nosub  = cidade_query.record().indexOf("loc_nosub");
   while (cidade_query.next()) {
       QString loc_nosub_str  = cidade_query.value(loc_nosub).toString();
       ui->city_lineEdit_deliver->setText(loc_nosub_str);

   }

   // clear number and complement
   ui->complement_lineEdit_deliver->setText("");
   ui->number_lineEdit_deliver->setText("");
}






//cep input format
void new_customer::on_cep_lineEdit_mainData_textChanged(const QString &arg1)
{
    ui->cep_lineEdit_mainData->setValidator( new QIntValidator(9,99999999, this) );
}

void new_customer::on_cep_lineEdit_charge_textChanged(const QString &arg1)
{
     ui->cep_lineEdit_charge->setValidator( new QIntValidator(9,99999999, this) );
}



void new_customer::on_pushButton_2_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "",
                tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" )
                );
     QPixmap pic;
     pic.load(imagePath);
     ui->pic_label_picture->setPixmap(pic);

}





void new_customer::on_remove_pushButton_picture_clicked()
{
    QString img = ":/images/blank.svg";
    QPixmap picture;
    picture.load(img);

    ui->pic_label_picture->setPixmap(picture);
}

void new_customer::on_addCustomer_pushButton_link_clicked()
{

}
