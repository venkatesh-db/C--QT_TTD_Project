#include "print_page.h"
#include "ui_print_page.h"
#include <QDate>
#include <QDateEdit>
#include <QDateTime>
#include <QPrinter>
#include <QPrintDialog>
#include  "dbmanager.h"
#include <QSqlQuery>
#include  <QDebug>
#include  "mainwindow.h"
#include <QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include<QSqlQueryModel>

static const QString path = "TTD12.db";

print_page::print_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::print_page)
{
    ui->setupUi(this);
    DbManager db(path);
    if(db.isOpen())
    {
       // QSqlQuery  qry;
        //ui->TableView->show(); // to show the tables

        QSqlQueryModel *modal1 =new QSqlQueryModel();

        QSqlQuery* qry=new QSqlQuery();
        //qry->prepare("select * from peopledata ");
        //qry->exec();

        modal1->setQuery(*qry);

        //ui->TableView->setModel(modal1);
       qry->prepare("select * from peopledata ");//WHERE name='"+name+"' ");
        qDebug()<<qry->exec();

        if(qry->exec())
       {
            qDebug()<<qry->next();

        while(qry->next())
        {
          qDebug()<<"fi";
      /*    ui->textEdit->copy();
          ui->textEdit->append(qry->value(1).toString());
          ui->textEdit->append(qry->value(2).toString());
          //ui->textEdit->setReadOnly(qry.value(2).toString());
/* ui->textEdit->append(qry.value(3).toString());
  ui->textEdit->append(qry.value(4).toString());
   ui->textEdit->append(qry.value(5).toString());
    ui->textEdit->append(qry.value(6).toString());
     ui->textEdit->append(qry.value(7).toString());

        /*  ui->lineEdit_10->setText(qry.value(1).toString());
          ui->lineEdit_7->setText(qry.value(2).toString());
          ui->lineEdit_8->setText(qry.value(3).toString());
          ui->lineEdit_9->setText(qry.value(4).toString());
          ui->lineEdit_2->setText(qry.value(5).toString());
          ui->label_11->setText(qry.value(6).toString());
          ui->label_12->setText(qry.value(7).toString());*/
        }
    }

}
}

print_page::~print_page()
{
    delete ui;
}

void print_page::on_pushButton_5_clicked()
{


    QPrinter printer;
    printer.setPrinterName("Printer");//  give any name
    QPrintDialog dialog(&printer,this);
    if(dialog.exec()==QDialog::Rejected) return ;
    ui->textEdit->print(&printer);
}

