#include "new_product.h"
#include "ui_new_product.h"
#include <new_product_degree.h>
#include <new_supplier.h>
#include <QSqlDatabase>
#include <QDesktopWidget>
#include <QStyle>
#include <QMessageBox>
#include <QtSql>
#include <QDebug>
#include <QFileDialog>
#include <camera.h>

QString selected_code;
QString selected_degree;
QString selected_group;
QString selected_subgroup;
QString degreeTableView_index;
QString selected_row_cest_tableView;

new_product::new_product(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::new_product)
{
    ui->setupUi(this);

    //disable group table
    ui->tab_grade_grupo->setEnabled(false);

    //set current date in date widgets
    QDate date = QDate::currentDate();
    ui->dateBlock_mainData->setDate(date);
}

new_product::~new_product()
{
    delete ui;
}



void new_product::camera_closed(const QString result){
    QString folder = QCoreApplication::applicationDirPath() + "/images";
    QString image = folder + "/new.jpg";
    QPixmap pic (image);
    QPixmap newPic = pic.scaled(QSize(472, 354),  Qt::KeepAspectRatio);
    int w = ui->picture_label->width();
    int h = ui->picture_label->height();
    ui->picture_label->setPixmap(newPic.scaled(w,h,Qt::KeepAspectRatio));
}


void new_product::pricing_calc()
{
    double cost = ui->cost_doubleSpinBox_mainData->value();
    double profit = ui->profit_doubleSpinBox_mainData->value();
    double additional_commision = ui->additionalCommission_doubleSpinBox_mainData->value();
    double sell = cost + profit;
    double net_profit = profit - (additional_commision * sell / 100);
    ui->sellingPrice_doubleSpinBox_mainData->setValue(sell);
    ui->netProfit_doubleSpinBox_mainData->setValue(net_profit);
}


void new_product::on_doubleSpinBox_cost_mainData_valueChanged(const QString &arg1)
{
    pricing_calc();
}

void new_product::on_doubleSpinBox_profit_mainData_valueChanged(const QString &arg1)
{
    pricing_calc();
}

void new_product::on_doubleSpinBox_additional_commission_mainData_valueChanged(const QString &arg1)
{
    pricing_calc();
}

void new_product::on_newDegree_pushButton_clicked()
{
    //open degree register dialog
    new_product_degree w;
    w.setModal(true);
    w.exec();
}


void new_product::on_searchSupplier_pushButton_clicked()
{
    //------------------------------------------------------------------------------
    //search the string in the database
    qDebug() << ui->searchSupplier_lineEdit->text();
    QSqlQuery query;
    query.prepare(QString("select * from Registrations.Supplier where %1 similar to '%(%2)%'")
                  .arg("name", ui->searchSupplier_lineEdit->text()));
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    //do not ever forget to exec the query
    query.exec();
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    // define the model and hide some columns
    static QSqlQueryModel model;
    model.setQuery(query);
    ui->supplier_tableView->setModel(&model);
    model.setHeaderData(0, Qt::Horizontal, QObject::tr("Código"));
    model.setHeaderData(1, Qt::Horizontal, QObject::tr("Nome"));
    model.setHeaderData(2, Qt::Horizontal, QObject::tr("Tipo de Fornecedor"));
    model.setHeaderData(3, Qt::Horizontal, QObject::tr("CPF"));
    model.setHeaderData(4, Qt::Horizontal, QObject::tr("CNPJ"));
    model.setHeaderData(5, Qt::Horizontal, QObject::tr("Inscrição Estadual"));
    model.setHeaderData(6, Qt::Horizontal, QObject::tr("CEP"));
    model.setHeaderData(7, Qt::Horizontal, QObject::tr("Endereço"));
    model.setHeaderData(8, Qt::Horizontal, QObject::tr("Número"));
    model.setHeaderData(9, Qt::Horizontal, QObject::tr("Complemento"));
    model.setHeaderData(10, Qt::Horizontal, QObject::tr("Bairro"));
    model.setHeaderData(11, Qt::Horizontal, QObject::tr("Cidade"));
    model.setHeaderData(12, Qt::Horizontal, QObject::tr("UF"));
    model.setHeaderData(13, Qt::Horizontal, QObject::tr("Telefone Fixo"));
    model.setHeaderData(14, Qt::Horizontal, QObject::tr("Telefone Adicional"));
    model.setHeaderData(15, Qt::Horizontal, QObject::tr("Celular"));
    model.setHeaderData(16, Qt::Horizontal, QObject::tr("Observações"));
    model.setHeaderData(17, Qt::Horizontal, QObject::tr("Email"));
    ui->supplier_tableView->resizeColumnsToContents();
    //------------------------------------------------------------------------------
}


void new_product::on_supplier_tableView_clicked(const QModelIndex &index)
{
QModelIndex codeColumn = ui->supplier_tableView->model()->index(index.row(), 0, QModelIndex());
QModelIndex nameColumn = ui->supplier_tableView->model()->index(index.row(), 1, QModelIndex());
QString selected_code = ui->supplier_tableView->model()->data(codeColumn).toString();
QString selected_name = ui->supplier_tableView->model()->data(nameColumn).toString();
qDebug() << selected_code;


ui->selectedSupplier_tableWidget->insertRow(ui->selectedSupplier_tableWidget->rowCount());
int row = ui->selectedSupplier_tableWidget->rowCount() - 1;
ui->selectedSupplier_tableWidget->setItem(row, code, new QTableWidgetItem(selected_code));
ui->selectedSupplier_tableWidget->setItem(row, name, new QTableWidgetItem(selected_name));
}

void new_product::on_selectedSupplier_tableWidget_clicked(const QModelIndex &index)
{
ui->selectedSupplier_tableWidget->removeRow(index.row());
}

void new_product::on_action_registration_triggered()
{
    QSqlDatabase::database();
    QSqlQuery query;

    /*

    |Scheme    |Table    |column   |Reserved words|two words|
    |----------|---------|---------|--------------|---------|
    |Plural    |Singular |singular |UPPERCASE     |underline|
    |Capitalize|Captalize|lowercase|

    */

    //------------------------------------------------------------------------------
    //create Product table
    query.exec("CREATE EXTENSION citext;");
    query.exec("CREATE SCHEMA Registrations;");
    query.exec("CREATE TABLE Registrations.Product"
              "(colname SERIAL primary key, "
              "name CITEXT, "
              "date_register CITEXT, "
              "degree_enabled boolean, "
              "unit CITEXT, "
              "quantity CITEXT, "
              "primary_color CITEXT, "
              "secondary_color CITEXT, "
              "reference CITEXT, "
              "block boolean, "
              "date_block CITEXT, "
              "reason CITEXT, "
              "cost CITEXT, "
              "profit CITEXT, "
              "additional_commision  CITEXT, "
              "sell  CITEXT, "
              "cest CITEXT, "
              "net_profit  CITEXT)");

    //supplier link table
    query.exec("CREATE EXTENSION citext;");
    query.exec("CREATE SCHEMA Registrations;");
    query.exec("CREATE TABLE Registrations.Product_Supplier"
              "(id SERIAL primary key, "
              "supplier_code CITEXT, "
              "product_code CITEXT)");
    //------------------------------------------------------------------------------





    //------------------------------------------------------------------------------
    //insert main data
    query.prepare("INSERT INTO Registrations.Product "
                  "(name, date_register, degree_enabled, "
                  "unit, quantity, primary_color, secondary_color, "
                  " reference, block, "
                  "date_block, reason, cost, profit, "
                  "additional_commision, sell, cest, net_profit) "
                  "VALUES (:name, :date_register, "
                  ":degree_enabled, :unit, :quantity, "
                  ":primary_color, :secondary_color, "
                  ":reference, :block, :date_block, "
                  ":reason, :cost, :profit, "
                  ":additional_commision, :sell, :cest, :net_profit)");
    query.bindValue(":name", ui->name_lineEdit_mainData->text());
    query.bindValue(":date_register", ui->dateRegister_mainData->text());
    query.bindValue(":degree_enabled",ui->enableDegree_checkBox->isChecked());
    query.bindValue(":unit", ui->unit_lineEdit_mainData->text());
    query.bindValue(":quantity", ui->quantity_doubleSpinBox_mainData->text());
    //


    //if degree is enabled then get the color and bind it to the database, else set color as empity string
    if(ui->enableDegree_checkBox->isChecked()){
        query.bindValue(":primary_color", ui->primayColor_comboBox->currentText());
        query.bindValue(":secondary_color", ui->secondaryColor_comboBox->currentText());
    }
    else{
        query.bindValue(":primary_color", QString(""));
        query.bindValue(":secondary_color", QString(""));
    }
    //

    query.bindValue(":reference", ui->productReference_lineEdit_mainData->text());

    query.bindValue(":block", ui->blockProduct_checkbox_mainData->isChecked());

    //if product block is enabled then get the text, else fill the value with empity string
    if(ui->blockProduct_checkbox_mainData->isChecked()){

        query.bindValue(":date_block", ui->dateBlock_mainData->text());
    }
    else{
        query.bindValue(":date_block", QString(""));
    }
    //


    query.bindValue(":reason", ui->reason_lineEdit_mainData->text());
    query.bindValue(":cost", ui->cost_doubleSpinBox_mainData->text());
    query.bindValue(":profit", ui->profit_doubleSpinBox_mainData->text());
    query.bindValue(":additional_commision", ui->additionalCommission_doubleSpinBox_mainData->text());
    query.bindValue(":sell", ui->sellingPrice_doubleSpinBox_mainData->text());
    query.bindValue(":cest", selected_row_cest_tableView);
    query.bindValue(":net_profit", ui->netProfit_doubleSpinBox_mainData->text());
    qDebug() << query.lastError() << " from product table";
    query.exec();
    //------------------------------------------------------------------------------





    //------------------------------------------------------------------------------
    //get the last row id from Registrations.Product INSERT
    QString id = query.lastInsertId().toString();
    //------------------------------------------------------------------------------





    //------------------------------------------------------------------------------
    //degree table creation
    query.exec("CREATE EXTENSION citext;");
    query.exec("CREATE SCHEMA Registrations;");
    query.exec("CREATE TABLE Registrations.Product_Degree_Link"
              "(id SERIAL primary key, "
              "degreeID CITEXT, "
              "productID CITEXT)");
    //------------------------------------------------------------------------------



    //------------------------------------------------------------------------------
    //Product_Picture table creation
    query.exec("CREATE EXTENSION citext;");
    query.exec("CREATE SCHEMA Registrations;");
    query.exec("create table Registrations.Product_Picture"
              "(colname SERIAL primary key, "
              "name  CITEXT, "
              "image  bytea)");
    //------------------------------------------------------------------------------





    //------------------------------------------------------------------------------
    //get items from supplier table widget and insert into table Product_Supplier
    if(ui->enableDegree_checkBox->isChecked())
    {
    for (int i=0; i < ui->selectedSupplier_tableWidget->rowCount(); i++) {
    query.prepare("INSERT INTO Registrations.Product_Supplier (supplier_code, product_code) "
                  "VALUES (:supplier_code, :product_code)");
    query.bindValue(":supplier_code", ui->selectedSupplier_tableWidget->item(i, 0)->text());
    query.bindValue(":product_code", id);
    qDebug() << query.lastError() << " from supplier table";
    query.exec();
    }
    }
    //------------------------------------------------------------------------------





    //------------------------------------------------------------------------------
    //get items from degree table widget and insert into table Product_Degree_Link
    for (int i=0; i < ui->selectedDegree_tableWidget->rowCount(); i++) {
    query.prepare("INSERT INTO Registrations.Product_Degree_Link (degreeID, productID) "
                  "VALUES (:degreeID, :productID)");


    //if degree is enabled then get the text, else fill the value with empity string
    if(ui->enableDegree_checkBox->isChecked()){
    query.bindValue(":degreeID", ui->selectedDegree_tableWidget->item(i, 0)->text());
    query.bindValue(":productID", id);
    }
    else{
        query.bindValue(":degreeID", QString(""));
        query.bindValue(":productID", QString(""));
    }
    qDebug() << query.lastError() << " from degree link";
    query.exec();

    }
    //------------------------------------------------------------------------------



    //------------------------------------------------------------------------------
    // Converting image to byte array:
    QString folder = QCoreApplication::applicationDirPath() + "/images";
    QString img = folder + "/new.jpg";
    QFile* file = new QFile(img);
    file->open(QIODevice::ReadOnly);
    QByteArray image = file->readAll();
    QString encoded = QString(image.toBase64());

    //insert picture
    query.prepare("INSERT INTO Registrations.Product_Picture (name, image) "
                  "VALUES (:name, :image)");
    query.bindValue(":name", ui->name_lineEdit_mainData->text());
    query.bindValue(":image", encoded, QSql::In | QSql::Binary);
    qDebug() << query.lastError() << " from picture db";
    query.exec();
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    //dialog after save data
    QMessageBox msgBox;
    msgBox.setWindowTitle("Cadastro de Produto.");
    msgBox.setText("Produto Cadastrado com Sucesso!");
    msgBox.exec();
    //------------------------------------------------------------------------------


    //clear


    //close window after finish the registration
    this->close();
}

void new_product::on_newSupplier_pushButton_clicked()
{
    static new_supplier w;
    //change the window position to center
    w.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            w.size(),
            qApp->desktop()->availableGeometry()
        ));
    //open the window if allowed by the permission system.
    w.show();
}


void new_product::on_degree_tableView_clicked(const QModelIndex &index)
{
    QModelIndex idColumn = ui->degree_tableView->model()->index(index.row(), 0, QModelIndex());
    QModelIndex degreeIdColumn = ui->degree_tableView->model()->index(index.row(), 1, QModelIndex());
    QModelIndex groupIdColumn = ui->degree_tableView->model()->index(index.row(), 2, QModelIndex());
    QModelIndex subgroupIdColumn = ui->degree_tableView->model()->index(index.row(), 3, QModelIndex());
    QString selected_id = ui->degree_tableView->model()->data(idColumn).toString();
    QString selected_degreeid = ui->degree_tableView->model()->data(degreeIdColumn).toString();
    QString selected_groupid = ui->degree_tableView->model()->data(groupIdColumn).toString();
    QString selected_subgroupID = ui->degree_tableView->model()->data(subgroupIdColumn).toString();


    ui->selectedDegree_tableWidget->insertRow(ui->selectedDegree_tableWidget->rowCount());
    int row = ui->selectedDegree_tableWidget->rowCount() - 1;
    ui->selectedDegree_tableWidget->setItem(row, id, new QTableWidgetItem(selected_id));
    ui->selectedDegree_tableWidget->setItem(row, degreeid, new QTableWidgetItem(selected_degreeid));
    ui->selectedDegree_tableWidget->setItem(row, groupid, new QTableWidgetItem(selected_groupid));
    ui->selectedDegree_tableWidget->setItem(row, subgroupid, new QTableWidgetItem(selected_subgroupID));
}

void new_product::on_cost_doubleSpinBox_mainData_valueChanged(const QString &arg1)
{
    pricing_calc();
}

void new_product::on_profit_doubleSpinBox_mainData_valueChanged(const QString &arg1)
{
    pricing_calc();
}

void new_product::on_additionalCommission_doubleSpinBox_mainData_valueChanged(const QString &arg1)
{
    pricing_calc();
}



void new_product::on_choosePicture_pushButton_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "",
                tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" )
                );
     QPixmap pic;
     pic.load(imagePath);
     ui->picture_label->setPixmap(pic);
}

void new_product::on_deleteImage_pushButton_clicked()
{
    QString img = ":/images/blank.svg";
    QPixmap picture;
    picture.load(img);

    ui->picture_label->setPixmap(picture);
}

void new_product::on_camera_pushbutton_clicked()
{
    static Camera w;
    connect(&w, SIGNAL(enteredText(QString)),this, SLOT(camera_closed(const QString)));
    w.show();
}


void new_product::on_blockProduct_checkbox_mainData_clicked(bool checked)
{
    if(checked){
        ui->dateBlock_mainData->setEnabled(true);
        ui->reason_lineEdit_mainData->setEnabled(true);
    }
    else{
        ui->dateBlock_mainData->clear();
        ui->reason_lineEdit_mainData->clear();
        ui->dateBlock_mainData->setEnabled(false);
        ui->reason_lineEdit_mainData->setEnabled(false);
    }
}

void new_product::on_enableDegree_checkBox_clicked(bool checked)
{
    //enable or disable group tab in checkbox
    if(checked == true){
    ui->tab_grade_grupo->setEnabled(true);
    }
    if(checked == false){
       ui->tab_grade_grupo->setEnabled(false);
    }
}

void new_product::on_searchDegree_pushButton_clicked()
{
    //------------------------------------------------------------------------------
    //search the string in the database
    QSqlQuery query;
    QString searchFilter;
    QString filter = ui->degreeFilter_comboBox->currentText();

    //translate string
    if(filter == QString("Grade")){
        searchFilter = QString("degreeID");
    }
    if(filter == QString("Grupo")){
        searchFilter = QString("groupID");
    }

    if(filter == QString("Subgrupo")){
        searchFilter = QString("subgroupID");
    }

    if(filter == QString("Código")){
        searchFilter = QString("colname");
        query.prepare(QString("select * from Registrations.Product_Degree where %1 = '%2'")
                      .arg(searchFilter, ui->searchDegree_lineEdit->text()));
    }
    else{
    query.prepare(QString("select * from Registrations.Product_Degree where %1 similar to '%(%2)%'")
                  .arg(searchFilter, ui->searchDegree_lineEdit->text()));
    }
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    //do not ever forget to exec the query
    query.exec();
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    // define the model and hide some columns
    static QSqlQueryModel model;
    model.setQuery(query);
    ui->degree_tableView->setModel(&model);

    model.setHeaderData(0, Qt::Horizontal, QObject::tr("Código"));

    ui->degree_tableView->resizeColumnsToContents();
}



void new_product::on_cestSearch_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    //------------------------------------------------------------------------------
    //search the string in the database
    QSqlQuery query;
    QString searchFilter;
    QString filter = ui->cest_comboBox->currentText();

    //translate string
    if(filter == QString("Descrição")){
        searchFilter = QString("descricao");
        query.prepare(QString("select * from Brasil.Cest where %1 similar to '%(%2)%'")
                      .arg(searchFilter, ui->cestSearch_lineEdit->text()));
    }

    if(filter == QString("CEST")){
        searchFilter = QString("cest");
        query.prepare(QString("select * from Brasil.Cest where %1 = '%2'")
                      .arg(searchFilter, ui->cestSearch_lineEdit->text()));
    }

    if(filter == QString("NCM/SH")){
        searchFilter = QString("ncm_sh");
        query.prepare(QString("select * from Brasil.Cest where %1 = '%2'")
                      .arg(searchFilter, ui->cestSearch_lineEdit->text()));
    }
    else{

    }
    //------------------------------------------------------------------------------


    //------------------------------------------------------------------------------
    //do not ever forget to exec the query
    query.exec();
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    // define the model and hide some columns
    static QSqlQueryModel model;
    model.setQuery(query);
    ui->cest_tableView->setModel(&model);

    model.setHeaderData(0, Qt::Horizontal, QObject::tr("Item"));
    ui->cest_tableView->setColumnHidden(0, true);

    ui->cest_tableView->resizeColumnsToContents();
}

void new_product::on_cest_tableView_clicked(const QModelIndex &index)
{

    // retorna o usuário selecionado na tabela, o index é 1, portanto não há necessidade de usar o index da função
    QModelIndex id = ui->cest_tableView->model()->index(index.row(), 1, QModelIndex());
    selected_row_cest_tableView = ui->cest_tableView->model()->data(id).toString();

}
