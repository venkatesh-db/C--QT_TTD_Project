#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QDate>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString name;
    QString Aadhar;
    QDate date ;
    QTime time ;
    QString DateString ;
    QString TimeString ;
    int printcount;
    int low,high;
    QString search1;
    QSqlQueryModel *modal2;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_Submit_clicked();

    void on_pushButton_clicked();

 //   void on_tableView_doubleClicked(const QModelIndex &index);


    int Validate_Data();
    bool Add_Data();
    int Print();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void fillTables();

    void on_pushButton_5_clicked();

    int randInt(int low, int high);

    void on_pushButton_6_clicked();

    void on_item_returnPressed();

    void on_signout_clicked();

    void on_item_editingFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
