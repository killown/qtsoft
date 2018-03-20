#ifndef NEW_EMPLOYEE_H
#define NEW_EMPLOYEE_H

#include <QMainWindow>
#include <QTableWidget>

namespace Ui {
class new_employee;
}

class new_employee : public QMainWindow
{
    Q_OBJECT

public:
    explicit new_employee(QWidget *parent = 0);
    ~new_employee();

private slots:
    void on_gender_comboBox_mainData_currentTextChanged(const QString &arg1);

    void on_newDependent_pushButton_dependents_clicked();

    void on_dependent_detableWidget_dependents_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_cep_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::new_employee *ui;
    QTableWidget* m_pTableWidget;

    QStringList m_TableHeader;

    enum Column
    {
        Dependente, DataDeNascimento
    };
};

#endif // NEW_EMPLOYEE_H
