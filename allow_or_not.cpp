#include <QSqlDatabase>
#include <QtSql>
#include <QMessageBox>
#include <global.h>

#include <allow_or_not.h>


bool allow_or_not(const QStringList lista) {
    //sistema de permissão, a função espera Q_FUNC_INFO como primeira item da lista e a ação, exemplo "Você não tem autorização para %1"
    QSqlDatabase::database();
    QSqlQuery query;
    QMessageBox msgBox;

    //libera acesso para administradores
    query.exec(QString("select * from Usuarios.Login where Acesso = 'total' AND Usuario = '%1'").arg(username_loggedin));
    if (query.next()){
        return true;

    }
    query.clear();
    //


    //verifica a permissão para usuários com acesso limitado
    query.exec(QString("select * from Permissoes.Permissao where PermissaoID similar to '%(%1)%' AND Usuario = '%2'").arg(lista[0], username_loggedin));

    if (query.next()){
        return true;

    }
    else{
        msgBox.setText(QString("Você não tem autorização para %1").arg(lista[1]));
        msgBox.setWindowTitle("Acesso Negado.");
        msgBox.exec();
        return false;
     }
    //
}
