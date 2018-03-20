#include <connect_database.h>
#include <QSqlDatabase>
#include <QtSql>
#include <login.h>
#include <iostream>
#include <fstream>
#include <algorithm>

//pg_hba.conf settings should look like for silgle ip address
//hostssl  all             all             192.168.0.102/32        trust

//or to allow all the whitin 192.168.0.* network
//hostssl  all             all             192.168.0.1/24        trust

//for password requiriment
//hostssl  all             all             192.168.0.1/24        md5


//------------------------------------------------------------------------------
//first usage on linux
//su - postgres -c "initdb --locale en_US.UTF-8 -D '/var/lib/postgres/data'"
//sudo systemctl start postgresql
//sudo systemctl enable postgresql
//su - postgres -c "createdb erp"



QSqlDatabase connect_db()
{
    static QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("erp");
    db.setUserName("postgres");

    QString cfg = QCoreApplication::applicationDirPath() + QString("/settings.ini");
    QFile inputFile(cfg);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
           QString line = in.readLine();
           QStringList list = line.split("=");

           if(list.startsWith("sslmode") && list.endsWith("verify-full"))
           {
               //requires root.crt
               db.setConnectOptions("sslmode=verify-full");
           }
           if(list.startsWith("sslmode") && list.endsWith("required"))
           {
               //does not force ssl
               db.setConnectOptions("sslmode=require");
           }
           if(list.startsWith("password"))
           {
               QString password = list.value(2);
               db.setPassword(password);
               qDebug() << "ssl disabled";
           }

       }
       inputFile.close();
    }

    db.setPort(5432);
    return db;
}
