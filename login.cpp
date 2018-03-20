#include "login.h"
#include "ui_login.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QMessageBox>
#include <qtsoft_mainwindow.h>
#include <global.h>
#include <encrypt.h>
#include <connect_database.h>

QSqlDatabase database;

QSqlQuery login::createDatabase(){
    qDebug() << "ta na hora de funcionar?";
    QSqlQuery query;
    query.exec("CREATE DATABASE erp");
    //new login table
    query.exec("SELECT * FROM Usuarios.Login where Usuario = 'admin'");
    if(!query.next()){
        query.exec("CREATE EXTENSION citext;");
        query.exec("CREATE SCHEMA Usuarios;");
        query.exec("create table Usuarios.Login "
                  "(colname SERIAL primary key, "
                  "Usuario  CITEXT, "
                  "Senha  CITEXT, "
                  "Acesso varchar(9))");

        query.prepare("INSERT INTO Usuarios.Login (Usuario, Senha, Acesso) "
                      "VALUES (:Usuario, :Senha, :Acesso)");
        query.bindValue(":Usuario", "admin");
        query.bindValue(":Senha", "9c30f8eb9076a70d8244ed838fbdecc76a398954ad57fd940dfab479ccdf3f443d82e6f21c36f71bc04d11878cb895629366051a920a0c04df6cc443c8c230ad");
        query.bindValue(":Acesso", "total");
        query.exec();
        return query;
    }
    return query;
}


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    createDatabase();
    database = connect_db();

    if(database.open()){
          ui->db_label->setText("Banco de Dados Conectado.");
    }
    else{
          ui->db_label->setText("Banco de Dados Desconectado.");
          static QSqlDatabase db = QSqlDatabase::database();
    }

}

login::~login()
{
    delete ui;
}


void login::on_entrar_pushButton_clicked()
{
    /*
     * supposing the DB was stopped for some reason and the login screen is still open, the user keep trying to login
     * after the administrator tells the user the server has already started he will receive login error
     * so check_db_connection will check if the database is available and then start the connection.
    */


    //admin default password
    QString teste_salt_password = QString("%1%2").arg("admin", "55555555555555555555555555555555555555555555555555");
    QString blah = QString(QCryptographicHash::hash((teste_salt_password.toLatin1().data()),QCryptographicHash::Sha3_512).toHex());
    qDebug() << blah;
    //


    //permission system
    QMessageBox msgBox;
    QSqlQuery query;
    query.exec("CREATE DATABASE erp");
    //new login table
    query.exec("SELECT * FROM Usuarios.Login where Usuario = 'admin'");
    if(!query.next()){
        query.exec("CREATE EXTENSION citext;");
        query.exec("CREATE SCHEMA Usuarios;");
        query.exec("create table Usuarios.Login "
                  "(colname SERIAL primary key, "
                  "Usuario  CITEXT, "
                  "Senha  CITEXT, "
                  "Acesso varchar(9))");

        query.prepare("INSERT INTO Usuarios.Login (Usuario, Senha, Acesso) "
                      "VALUES (:Usuario, :Senha, :Acesso)");
        query.bindValue(":Usuario", "admin");
        query.bindValue(":Senha", "34e90453f07620b4518462f837de3697cebddc00934d9a9827bb7c95b46d3d5db0fa4d4a45b31319fa5e65e6e55eecf7bf9bc8879e3bb156b44cb7726badad56");
        query.bindValue(":Acesso", "total");
        query.exec();

        query.clear();
    }



    QByteArray username = ui->usuario_lineEdit->text().toLatin1().data();
    QByteArray password = ui->senha_lineEdit->text().toLatin1().data();





    //salt for SHA
    QString salt =  "55555555555555555555555555555555555555555555555555";
    QString salt_password = ui->senha_lineEdit->text() + salt;
    //encrypt for Sha3_512
    QString password_sha = encrypt(salt_password.toLatin1().data());
    qDebug() << password_sha;
    //
    query.exec(QString("select * from Usuarios.Login where Usuario = '%1' AND Senha = '%2'").arg(username, password_sha));

    if (query.next()) {
        username_loggedin = ui->usuario_lineEdit->text();
        static QTSOFT_MainWindow w;
        w.show();
        login::close();
    }
    else{
        msgBox.setText("Usuário ou Senha incorretos");
        msgBox.exec();
        return;
    }
    //


}
