#include "page1_dialog.h"
#include "ui_page1_dialog.h"
#include "mainwindow.h"
#include "page1_dialog.h"
#include "register_dialog.h"
#include "dbmanager.h"
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtSql/QSqlRecord>
#include <string.h>
#include <list>
#include <QPixmap>
//#include<dbmanager.h>
#include <QMainWindow>
#include<QtSql/QtSql>
#include<QtDebug>
#include<QFileInfo>



static const QString path = "TTD1.db";


int i=0;

#include <QDebug>
#include <QMessageBox>

page1_dialog::page1_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::page1_dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Login Page");

}

page1_dialog::~page1_dialog()
{
    delete ui;
}


void page1_dialog::on_Login_clicked()
{

    //this->setWindowTitle("New Title");
    //QString push_login =   ui->Login->text();
    QString usernam   =   ui->user_name->text();
    QString passwor   =   ui->Password->text();


    if(ui->user_name->text().isEmpty())
    {
         QMessageBox::information(this,"Login_Username","Username is empty");
         ui->user_name->setFocus();
     }
    if(ui->Password->text().isEmpty())
    {
         QMessageBox::information(this,"Login_Password","Enter Password is empty");
         ui->Password->setFocus();
     }
    DbManager db(path);

    if(!(db.isOpen())){
        qDebug()<<"Failed to open the database";
        return;
    }
    db.isOpen();
    QSqlQuery qry;
    qry.prepare("select * from people where username='"+usernam+"'and password='"+passwor+"'");

    if(qry.exec())
    {
        int count=0;
        while (qry.next()) {

            count++;
        }
        if(count==1)
        {
            //QMessageBox::information(this,"Login","Username and Password is Correct");
            db.isClose();

            hide();
            MainWindow *ptr1 = new MainWindow();
            ptr1->show();
            ptr1->parent();
            return;



        }
        else if(count>1){
            QMessageBox::warning(this,"Login","Duplicate Username and Password ");
        }
        else if(count<1){
            QMessageBox::warning(this,"Login","Username and Password is not Correct");
        }
    }

 }


void page1_dialog::on_pushButton_clicked()
{

    register_dialog ptr2;
    ptr2.show();
    ptr2.exec();
}
