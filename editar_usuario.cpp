#include "editar_usuario.h"
#include "ui_editar_usuario.h"
#include <QSqlDatabase>
#include <QtSql>
#include <qdebug.h>
#include <insert_permission.h>
#include <permission_list.h>
#include <global.h>
#include <encrypt.h>
#include <qmessagebox.h>

QString selected_row;
int index_login_tableView;
static QSqlQueryModel model;
QSortFilterProxyModel proxyModel;

editar_usuario::editar_usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editar_usuario)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.exec();
    query.clear();
    query.prepare("select * from Usuarios.Login cat");
    query.exec();
    qDebug() << query.next();
    model.setQuery(query);
    proxyModel.setSourceModel(&model);
    ui->login_tableView->setModel( &proxyModel);
    proxyModel.sortColumn();
    ui->login_tableView->setColumnHidden(0, true);
    ui->login_tableView->setColumnHidden(2, true);

}

editar_usuario::~editar_usuario()
{
    delete ui;
}

void editar_usuario::on_login_tableView_clicked(const QModelIndex &index)
{
    QSqlDatabase::database();
    QSqlQuery query;
    index_login_tableView = index.row();

    /*query.exec(QString("SELECT * FROM Usuarios.Login where Usuario = '%1'").arg(ui->pesquisar_lineEdit->text()));*/

  /*  //não continua a função em caso do usuário não ser encontrado
    if(!query.next()){
        return;
    }
*/
    // retorna o usuário selecionado na tabela, o index é 1, portanto não há necessidade de usar o index da função
    QModelIndex id = ui->login_tableView->model()->index(index.row(), 1, QModelIndex());
    selected_row = ui->login_tableView->model()->data(id).toString();


    //verifica se o usuário é do tipo administrador
    query.exec(QString("select * from Usuarios.Login where Acesso = 'total' AND Usuario = '%1'").arg(selected_row));
    if (query.next()){
        ui->tabWidget->hide();
        ui->permissoes_label->hide();
        ui->administrador_checkBox->setChecked(true);
        QSize size(310, 392);
        resize(size);
        query.clear();
    }
    else{
        ui->tabWidget->show();
        ui->permissoes_label->show();
        ui->administrador_checkBox->setChecked(false);
        QSize size(1057, 392);
        resize(size);
    }
    //

    // Multiple rows can be selected
    query.prepare(QString("SELECT * FROM Permissoes.Permissao where Usuario = '%1'").arg(selected_row));

    // remove a seleção do checkbox para quando clicar em um novo usuário não manter a seleção anterior
    ui->localizar_cliente_checkBox->setChecked(false);
    ui->cadastrar_usuario_checkBox->setChecked(false);
    ui->cadastrar_cliente_checkBox->setChecked(false);
    ui->editar_cliente_checkBox->setChecked(false);
    ui->editar_usuario_checkBox->setChecked(false);


    if(query.exec()){
            while(query.next()){

                if (query.value(2).toString() == on_localizar_cliente_action_triggered){
                        ui->localizar_cliente_checkBox->setChecked(true);

                 }
                if (query.value(2).toString() == on_cadastrar_usuario_action_triggered){
                        ui->cadastrar_usuario_checkBox->setChecked(true);

                 }
                if (query.value(2).toString() == on_cadastrar_cliente_action_triggered){
                        ui->cadastrar_cliente_checkBox->setChecked(true);

                 }
                if (query.value(2).toString() == on_editar_cliente_action_triggered){
                        ui->editar_cliente_checkBox->setChecked(true);

                 }

                if (query.value(2).toString() == on_editar_usuario_action_triggered){
                        ui->editar_usuario_checkBox->setChecked(true);

                 }

            }

        }
}
void editar_usuario::on_pesquisar_lineEdit_returnPressed()
{
    QSqlDatabase::database();
    QSqlQuery query;
    static QSqlQueryModel model;
    qDebug() << "asdfasdfasdfasdf";


    query.exec(QString("SELECT * FROM Usuarios.Login where Usuario = '%1'").arg(ui->pesquisar_lineEdit->text()));


    model.setQuery(query);
    ui->login_tableView->setModel(&model);
}


void atualizar_modelo(){
    QSqlQuery query;
    query.prepare("select * from login cat");
    query.exec();
    model.setQuery(query);
}

void editar_usuario::on_salvar_pushButton_clicked()
{
    QString vazio;
    if (selected_row == vazio) {
            return;
    }

    QSqlDatabase::database();
    QSqlQuery query;

    //salt para o hash SHA
    QString salt =  "55555555555555555555555555555555555555555555555555";
    if (ui->senha_lineEdit->text() != vazio){
    QString senha_salt = ui->senha_lineEdit->text() + salt;
    //encrypt para Sha3_512
    QString senha = encrypt(senha_salt.toLatin1().data());
    //

    query.exec(QString("update Usuarios.Login set Senha = '%1' where Usuario = '%2'").arg(senha, selected_row));
    query.clear();
    }



    //se o checkbox estiver selecionado, gravar a função no db permissao se não estiver selecionado remove a função do db
    if(ui->localizar_cliente_checkBox->isChecked()){

        QStringList lista;
        //procura se a permissão já existe no banco de dados
        query.exec(QString("SELECT * FROM Permissoes.Permissao where Usuario = '%1' AND PermissaoID = '%2'").arg(selected_row, on_localizar_cliente_action_triggered));
        //se não existe permissão, então adicionar.
        qDebug() << selected_row << " uauauauau";
        if(!query.next()){
            QStringList lista;
            //usuário selecionado em editar_usuario::on_login_tableView_clicked, função para permissão
            lista << selected_row << on_localizar_cliente_action_triggered;
            insert_permission(lista);
            qDebug() << "asdfasdfasdfasdfa asdf a sdf  asd fas df as df asdf";
        }


        }

    else{
         //se o checkbox não está selecionado então deletar a permissão do banco de dados.
         query.exec(QString("DELETE FROM Permissoes.Permissao where Usuario = '%1' AND PermissaoID = '%2'").arg(selected_row, on_localizar_cliente_action_triggered));
         }

    //se o checkbox estiver selecionado, gravar a função no db permissao se não estiver selecionado remove a função do db
    if(ui->cadastrar_usuario_checkBox->isChecked()){
        QStringList lista;
        query.exec(QString("SELECT * FROM Permissoes.Permissao where Usuario = '%1' AND PermissaoID = '%2'").arg(selected_row, on_cadastrar_usuario_action_triggered));
        if(!query.next()){
            QStringList lista;
            lista << selected_row << on_cadastrar_usuario_action_triggered;
            insert_permission(lista);

               }
        }
        else{
        query.exec(QString("DELETE FROM Permissoes.Permissao where Usuario = '%1' AND PermissaoID = '%2'").arg(selected_row, on_cadastrar_usuario_action_triggered));
         }


    //se o checkbox estiver selecionado, gravar a função no db permissao se não estiver selecionado remove a função do db
    if(ui->editar_cliente_checkBox->isChecked()){
        QStringList lista;
        query.exec(QString("SELECT * FROM Permissoes.Permissao where Usuario = '%1' AND PermissaoID = '%2'").arg(selected_row, on_editar_cliente_action_triggered));
        if(!query.next()){
            QStringList lista;
            lista << selected_row << on_editar_cliente_action_triggered;
            insert_permission(lista);


        }
    }
    else{
        query.exec(QString("DELETE FROM Permissoes.Permissao where Usuario = '%1' AND PermissaoID = '%2'").arg(selected_row, on_editar_cliente_action_triggered));
    }


    //se o checkbox estiver selecionado, gravar a função no db permissao se não estiver selecionado remove a função do db
    if(ui->cadastrar_cliente_checkBox->isChecked()){
        QStringList lista;
        query.exec(QString("SELECT * FROM Permissoes.Permissao where Usuario = '%1' AND PermissaoID = '%2'").arg(selected_row, on_cadastrar_cliente_action_triggered));
        if(!query.next()){
            QStringList lista;
            lista << selected_row << on_cadastrar_cliente_action_triggered;
            insert_permission(lista);
        }
}
    else{
        query.exec(QString("DELETE FROM Permissoes.Permissao where Usuario = '%1' AND PermissaoID = '%2'").arg(selected_row, on_cadastrar_cliente_action_triggered));
    }





    //se o checkbox estiver selecionado definir acesso total ao usuário
    if(ui->administrador_checkBox->isChecked()){
        QStringList lista;
        query.exec(QString("update Usuarios.Login set Acesso = '%1' where Usuario = '%2'").arg("total", selected_row));
        qDebug() << "agora atualizou o acesso total";
        atualizar_modelo();
    }
    else{
        query.exec(QString("update Usuarios.Login set Acesso = '%1' where Usuario = '%2'").arg("limitado", selected_row));
        QSqlQuery query;
        query.prepare("select * from login cat");
        query.exec();
        model.setQuery(query);
        qDebug() << "agora atualizou o acesso limitado";
    }

    if(ui->deletar_usuario_checkBox->isChecked()){
        QStringList lista;

        //mensagem após salvar os dados
        QMessageBox msgBox;
        msgBox.setWindowTitle("Deletar Usuário");
        msgBox.setText(QString("Tem certeza que deseja deletar o usuário %1?").arg(selected_row));
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes, tr("Sim"));
        msgBox.setButtonText(QMessageBox::No, tr("Não"));
        if(msgBox.exec() == QMessageBox::Yes){
          // do something
            query.exec(QString("DELETE FROM Usuario.Login where Usuario = '%1'").arg(selected_row));
            atualizar_modelo();
            return;
        }else {
          qDebug() << "Não Deletar";
          return;
        }
        query.exec(QString("DELETE FROM Usuarios.Login where Usuario = '%1'").arg(selected_row));
        QSqlQuery query;
        query.prepare("select * from login cat");
        query.exec();
        model.setQuery(query);
    }

    //mensagem após salvar os dados
    QMessageBox msgBox;
    msgBox.setWindowTitle("Edição do Usuário.");
    msgBox.setText("As alterações foram efetuadas com sucesso!");
    msgBox.exec();
    //
}
