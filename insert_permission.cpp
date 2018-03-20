#include "ui_sistema_de_login.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>


void insert_permission(const QStringList list) {

    QSqlDatabase::database();
    QSqlQuery query;

    query.exec("CREATE EXTENSION citext;");
    query.exec("CREATE SCHEMA Permissions;");
    query.exec("create table Permission"
              "(colname SERIAL primary key, "
              "username  CITEXT, "
              "permission varchar(100))");

    query.prepare("INSERT INTO Permissions.Permission (username, permissionID) "
                  "VALUES (:username, :permissionID)");
    query.bindValue(":username", list[0]);
    query.bindValue(":permissionID", list[1]);
    query.exec();
}

