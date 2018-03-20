#ifndef NEW_JOB_TITLE_H
#define NEW_JOB_TITLE_H
#include <QTableWidget>

#include <QMainWindow>

namespace Ui {
class new_job_title;
}

class new_job_title : public QMainWindow
{
    Q_OBJECT

public:
    explicit new_job_title(QWidget *parent = 0);
    ~new_job_title();

private slots:


    void on_addTitle_pushButton_clicked();

    void on_jobTitle_tableWidget_clicked(const QModelIndex &index);

private:
    Ui::new_job_title *ui;
    QTableWidget* jobTitle_table;
    enum Column
    {
        name, description
    };
};

#endif // NEW_JOB_TITLE_H
