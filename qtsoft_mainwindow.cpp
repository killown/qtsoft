#include "qtsoft_mainwindow.h"
#include "ui_qtsoft_mainwindow.h"
#include <new_customer.h>
#include <QDesktopWidget>
#include <QStyle>
#include <localizar_cliente.h>
#include <sistema_de_login.h>
#include <change_customer.h>
#include <new_employee.h>
#include <QSqlDatabase>
#include <QtSql>
#include <QTimer>
#include <QMessageBox>
#include <global.h>
#include <editar_usuario.h>
#include <allow_or_not.h>
#include <new_supplier.h>
#include <new_product.h>
#include <sell.h>

/*
 * system deps
 * qt5-multimedia for camera.



/*
Procedimento pra adicionar nova permissão no código:

copiar o nome da função, exemplo: void QTSOFT_MainWindow::on_cadastrar_cliente_action_triggered() essa função é referente as ações do menu

adicionar novo checkbox, em sistema_de_login.ui e mudar o nome do objeto, exemplo: cadastrar_cliente_checkBox

adicionar nova condição em sistema_de_login.cpp na função _pushButton_clicked():
        if(ui->cadastrar_cliente_checkBox->isChecked()){
            QStringList lista;
            lista << ui->usuario_lineEdit->text() << "void QTSOFT_MainWindow::on_cadastrar_cliente_action_triggered() ";
            inserir_dados(lista);
            }
*/


void QTSOFT_MainWindow::createStatusBar()
{
    static QSqlDatabase db = QSqlDatabase::database();
    bool ok = db.isOpen();
    if(ok != true)
    {
    ui->statusBar->showMessage(tr("Banco de Dados Desconectado....."));
    }
    else
    {
    ui->statusBar->showMessage(tr("Banco de Dados Conectado....."));
    }


}


QTSOFT_MainWindow::QTSOFT_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QTSOFT_MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        ));


    static QSqlDatabase db = QSqlDatabase::database();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(createStatusBar()));
    timer->start(5000);

    bool ok = db.open();
    if(ok != true)
    {
    ui->statusBar->showMessage(tr("Banco de Dados Desconectado....."));
    }
    else
    {
    ui->statusBar->showMessage(tr("Banco de Dados Conectado....."));
    }

}

QTSOFT_MainWindow::~QTSOFT_MainWindow()
{
    delete ui;
}


void QTSOFT_MainWindow::on_cadastrar_cliente_action_triggered()
{
    //sistema de permissão
    QStringList lista;
    // allow_or_not espera uma lista com o nome da função no index 0 e a ação da mensagem no index 1
    lista << Q_FUNC_INFO << "Cadastrar Cliente";
    // a função retorna true para liberado e falso para acesso negado.
    if (!allow_or_not(lista)){return;}
    // final do sistema de permissão

    static new_customer w;
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


void QTSOFT_MainWindow::on_cadastrar_usuario_action_triggered()
{
    /*

    //sistema de permissão
    QMessageBox msgBox;


    QSqlQuery query(QString("select * from Permissoes.Permissao where PermissaoID similar to '%(%1)%' AND Usuario = '%2'").arg(Q_FUNC_INFO, username_loggedin));
    if (query.next()){

    }
    else{
        msgBox.setText("Você não tem autorização para usar esse recurso.");
        msgBox.setWindowTitle("Acesso Negado.");
        msgBox.exec();
        return;
    }
    //

    */

    //sistema de permissão
    QStringList lista;
    // allow_or_not espera uma lista com o nome da função no index 0 e a ação da mensagem no index 1
    lista << Q_FUNC_INFO << "Cadastrar Usuário";
    // a função retorna true para liberado e falso para acesso negado.
    if (!allow_or_not(lista)){return;}
    // final do sistema de permissão

    //abre a janela depois de verificada a permissão
    sistema_de_login Janela_Cadastrar_Usuario;
    Janela_Cadastrar_Usuario.setModal(true);
    Janela_Cadastrar_Usuario.exec();
}

void QTSOFT_MainWindow::on_localizar_cliente_action_triggered()
{
    //sistema de permissão
    QStringList lista;
    // allow_or_not espera uma lista com o nome da função no index 0 e a ação da mensagem no index 1
    lista << Q_FUNC_INFO << "Localizar Cliente";
    // a função retorna true para liberado e falso para acesso negado.
    if (!allow_or_not(lista)){return;}
    // final do sistema de permissão

    //abre a janela depois de verificada a permissão
    localizar_cliente Janela_Localizar_Cliente;
    Janela_Localizar_Cliente.setModal(true);
    Janela_Localizar_Cliente.exec();
}

void QTSOFT_MainWindow::on_editar_cliente_action_triggered()
{

    //sistema de permissão
    QStringList lista;
    // allow_or_not espera uma lista com o nome da função no index 0 e a ação da mensagem no index 1
    lista << Q_FUNC_INFO << "Editar Cliente";
    // a função retorna true para liberado e falso para acesso negado.
    if (!allow_or_not(lista)){return;}
    // final do sistema de permissão

    //abre a janela depois de verificada a permissão
    change_customer change_customer_window;
    change_customer_window.setModal(true);
    change_customer_window.exec();
}

void QTSOFT_MainWindow::on_editar_usuario_action_triggered()
{
    //sistema de permissão
    QStringList lista;
    // allow_or_not espera uma lista com o nome da função no index 0 e a ação da mensagem no index 1
    lista << Q_FUNC_INFO << "Editar Usuário";
    // a função retorna true para liberado e falso para acesso negado.
    if (!allow_or_not(lista)){return;}
    // final do sistema de permissão

    //abre a janela depois de verificada a permissão
    editar_usuario Janela_Editar_Usuario;
    Janela_Editar_Usuario.setModal(true);
    Janela_Editar_Usuario.exec();
}

void QTSOFT_MainWindow::on_actionFuncionario_triggered()
{
    //sistema de permissão
    QStringList lista;
    // allow_or_not espera uma lista com o nome da função no index 0 e a ação da mensagem no index 1
    lista << Q_FUNC_INFO << "Cadastrar Cliente";
    // a função retorna true para liberado e falso para acesso negado.
    if (!allow_or_not(lista)){return;}
    // final do sistema de permissão


    static new_employee w;
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



void QTSOFT_MainWindow::on_action_new_supplier_triggered()
{
    //permission system
    QStringList list;
    // allow_or_not expect a list with a name of the funtion in the index 0 and the action message in the index 1
    list << Q_FUNC_INFO << "new supplier";
    // return true for allowed and false for denied.
    if (!allow_or_not(list)){return;}
    // system permission ends here.



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

void QTSOFT_MainWindow::on_action_new_product_triggered()
{
    //permission system
    QStringList list;
    // allow_or_not expect a list with a name of the funtion in the index 0 and the action message in the index 1
    list << Q_FUNC_INFO << "new product";
    // return true for allowed and false for denied.
    if (!allow_or_not(list)){return;}
    // system permission ends here.


    static new_product w;

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

void QTSOFT_MainWindow::on_actionSell_triggered()
{
    //permission system
    QStringList list;
    // allow_or_not expect a list with a name of the funtion in the index 0 and the action message in the index 1
    list << Q_FUNC_INFO << "new product";
    // return true for allowed and false for denied.
    if (!allow_or_not(list)){return;}
    // system permission ends here.


    static sell w;

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
