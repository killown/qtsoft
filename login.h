#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSqlDatabase>



namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    QSqlQuery createDatabase();

private slots:

    void on_entrar_pushButton_clicked();

private:
    Ui::login *ui;
    QSqlDatabase database;

};

#endif // LOGIN_H
