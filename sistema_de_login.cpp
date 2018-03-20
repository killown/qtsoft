#include <iostream>
#include <string>
#include "ui_sistema_de_login.h"
#include <sistema_de_login.h>
#include <qmessagebox.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QDebug>
#include <insert_permission.h>
#include <encrypt.h>
#include <global.h>

sistema_de_login::sistema_de_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sistema_de_login)
{
    ui->setupUi(this);

}

sistema_de_login::~sistema_de_login()
{
    delete ui;
}

void sistema_de_login::on_cadastrar_pushButton_clicked()
{
        QSqlDatabase::database();
        QSqlQuery query;
        qDebug() << "asdfasdfasdfasdf";
        QString usuario = ui->usuario_lineEdit->text();


        query.exec(QString("SELECT * FROM Usuarios.Login where Usuario = '%1'").arg(ui->usuario_lineEdit->text()));


        if(query.next()){
            qDebug() << "usuário já existe";
            QMessageBox msgBox;
            msgBox.setText("Por Favor, Tente Outro Usuário.");
            msgBox.setWindowTitle("Usuário já existe.");
            msgBox.exec();
            return;
        }
        query.clear();

        query.prepare("INSERT INTO Usuarios.Login (Usuario, Senha, Acesso) "
                      "VALUES (:Usuario, :Senha, :Acesso)");

        //se o checkbox estiver selecionado garante acesso total ao usuário
        QString acesso;
        if(ui->administrador_checkBox->isChecked()){
            acesso = "total";
        }
        else{
            acesso = "limitado";
        }

        //salt para o hash SHA
        QString salt =  "55555555555555555555555555555555555555555555555555";
        QString senha_salt = ui->senha_lineEdit->text() + salt;
        //encrypt para Sha3_512
        QString senha = encrypt(senha_salt.toLatin1().data());
        //

        query.bindValue(":Usuario", usuario);
        query.bindValue(":Senha", senha);
        query.bindValue(":Acesso", acesso);
        query.exec();
        qDebug() << query.executedQuery() << "  aaee";

        if(ui->localizar_cliente_checkBox->isChecked()){
            QStringList lista;
            lista << ui->usuario_lineEdit->text() << "void QTSOFT_MainWindow::on_localizar_cliente_action_triggered()";
            insert_permission(lista);
            }

        if(ui->cadastrar_usuario_checkBox->isChecked()){
            QStringList lista;
            lista << ui->usuario_lineEdit->text() << "void QTSOFT_MainWindow::on_cadastrar_usuario_action_triggered()";
            insert_permission(lista);
            }

        if(ui->editar_cliente_checkBox->isChecked()){
            QStringList lista;
            lista << ui->usuario_lineEdit->text() << "void QTSOFT_MainWindow::on_editar_cliente_action_triggered()";
            insert_permission(lista);
            }

        if(ui->cadastrar_cliente_checkBox->isChecked()){
            QStringList lista;
            lista << ui->usuario_lineEdit->text() << "void QTSOFT_MainWindow::on_cadastrar_cliente_action_triggered()";
            insert_permission(lista);
            }

        //mensagem após salvar os dados
        QMessageBox msgBox;
        msgBox.setWindowTitle("Novo Usuário.");
        msgBox.setText(QString("Usuário %1 foi adicionado ao sistema!").arg(usuario));
        msgBox.exec();
        ui->usuario_lineEdit->clear();
        ui->senha_lineEdit->clear();
        //

}

void sistema_de_login::on_administrador_checkBox_toggled(bool checked)
{
    if(ui->administrador_checkBox->isChecked()){
        ui->tabWidget->hide();
        ui->permissoes_de_acesso_label->hide();
        QSize size(727, 100);
        resize(size);
    }
    else{
        ui->tabWidget->show();
        ui->permissoes_de_acesso_label->show();
        QSize size(727, 347);
        resize(size);
    }
}
