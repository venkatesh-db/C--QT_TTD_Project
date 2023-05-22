#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QtSql/QSqlTableModel>
#include <QTableView>
#include "page1_dialog.h"
#include <QDate>
#include <QDateEdit>
#include <QDateTime>
#include <QPrinter>
#include <QPrintDialog>
#include <QMessageBox>
#include <QIntValidator>
#include <QTableWidget>
#include <QGlobal.h>
#include <QTime>

static const QString path = "TTD1.db";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_item_returnPressed()
{
    int randomValue = randInt(1,20000);
    QString aString = QString::number(randomValue);
    ui->lineEdit->setText(aString);
}

int MainWindow::randInt(int low, int high)
{
    // Random number between low and high
    return (qrand() % ((high + 1) - low) + low);
}

void MainWindow::on_Submit_clicked()
{

    date = QDate::currentDate();//
    time = QTime::currentTime();
    name=ui->Name->text();
    Aadhar=ui->Aadhaar->text();
    // Get random value between 0-10000


if(Validate_Data()!=-1)
{
    int a;//, i=50000;
   // while(i)
    {
 a=Add_Data();//i--;
 }
  if(a)
  {

    Print();

    }
}
}


int MainWindow::Print()
{
    printcount=0;
    DbManager db(path);
  if(db.isOpen())
        {
      qDebug()<<"first1";
  //          db.isOpen();
           QSqlQuery* qry=new QSqlQuery();
           qry->prepare("select * from peopledata WHERE name='"+name+"' and aadharno='"+Aadhar+"'");
           qry->exec();

           if(qry->exec())
          {
               //qDebug()<<qry->next();

           while(qry->next())
           {
             qDebug()<<"first12";
             printcount++;
    if(printcount==1)
{
             ui->textEdit->append("                                          WELLCOME TO TTD \n"
                                 "                                            \n "
                                 "                                            \n");
             ui->textEdit->append("                                          "+qry->value(7).toString()+"  " +qry->value(8).toString() +"\n "
                                              "                                            \n "
                                              "                                            \n"
                                              "                                            \n");


             ui->stackedWidget->setCurrentIndex(1);
 qDebug()<<"it coming";
             ui->textEdit->append(" name:                   "+qry->value(1).toString()+" ");
             ui->textEdit->append(" Mobileno:              "+qry->value(2).toString()+" ");
             ui->textEdit->append(" State:                    "+qry->value(3).toString()+" ");
             ui->textEdit->append(" Aadharno:             "+qry->value(4).toString()+" ");
             ui->textEdit->append(" Numberofitems:     "+qry->value(5).toString()+" ");
             ui->textEdit->append(" Tocken No:                 "+qry->value(6).toString()+" ");

           }
       }

}
    }

    db.isClose();
}

bool MainWindow::Add_Data()
{
    DbManager db(path);
    if(db.isOpen())
    {
        qDebug()<<"first";


        db.createdataTable();

       if(db.adddataPerson(ui->Name->text(),ui->Mobile->text(),ui->state->currentText(),ui->Aadhaar->text(),ui->item->text(),ui->lineEdit->text(),date,time))
       {
            db.isClose();

           return true;
       }
       else
       {
           db.isClose();
           return false;
       }

       db.isClose();

}
}


int MainWindow::Validate_Data()
{

    if(ui->Name->text().isEmpty())
    {
        QMessageBox::information(this,"Error","Pls Enter Name..");
        ui->Name->setFocus();
        return -1;
    }

    if(!ui->Mobile->text().isEmpty())
    {
        if((ui->Mobile->text().count())!=10)
        {
                QMessageBox::information(this,"Error","Pls Enter 10 Digites..");
                ui->Mobile->setFocus();
                ui->Mobile->clear();
                return -1;
        }
    }
    else
    {
            QMessageBox::information(this,"Error","Pls Enter Mobile..");
            ui->Mobile->setFocus();
            return -1;
    }


    if(ui->state->currentText().isEmpty())
    {
        QMessageBox::information(this,"Error","Pls Enter state..");
        ui->state->setFocus();
        return -1;
    }
    if(!(ui->Aadhaar->text().isEmpty()))
    {
        if((ui->Aadhaar->text().count())!=16)
        {
                QMessageBox::information(this,"Error","Pls Enter 16 Digites..");
                ui->Aadhaar->setFocus();
                ui->Aadhaar->clear();
                return -1;
        }
    }
    else
    {
        QMessageBox::information(this,"Error","Pls Enter Aadhaar..");
        ui->Aadhaar->setFocus();
        return -1;
    }

    if(ui->item->text().isEmpty())
    {
        QMessageBox::information(this,"Error Item","Pls Enter item..");
        ui->item->setFocus();
        return -1;
    }
    /*   else if(!(ui->item->text().data()->isNonCharacter()))
    {
            QMessageBox::information(this,"Error","Pls Enter Digites..");
            ui->item->setFocus();
            ui->item->clear();
            return -1;

    }*/

    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"Error Item_no ","Pls Enter item..");
        ui->lineEdit->setFocus();
        return -1;
    }
}


void MainWindow::on_pushButton_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
  fillTables();
}


void MainWindow::on_pushButton_2_clicked()
{
 ui->tableWidget->hideColumn(0);
 ui->stackedWidget->setCurrentIndex(2);
fillTables();
 //ui->TableView->show(); // to show the tables


/*
  qDebug()<<"first1";



qDebug()<<name;

  DbManager db(path);
 if(db.isOpen())
 {

     ui->TableView->show(); // to show the tables
     ui->TableView->resizeColumnsToContents();
     ui->TableView->resizeRowsToContents();
     QSqlQueryModel *modal1 =new QSqlQueryModel();

     QSqlQuery* qry=new QSqlQuery();
     qry->prepare("select * from peopledata ");
     qry->exec();

     modal1->setQuery(*qry);
     list->setModel(modal1);

     //ui->TableView->setModel(modal1);
     ui->tableWidget->setModel(list);

}*/
}

void MainWindow::on_pushButton_3_clicked()
{
    /* for printer settings */

    QPrinter printer;
    printer.setPrinterName("Printer");//  give any name
    QPrintDialog dialog(&printer,this);
    if(dialog.exec()==QDialog::Rejected) return ;
    ui->textEdit->print(&printer);
    ui->textEdit->clear();
    ui->stackedWidget->setCurrentIndex(0);

         ui->Name->clear();
         ui->Mobile->clear();
         ui->Aadhaar->clear();
         ui->item->clear();
         ui->lineEdit->clear();

}



void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    DbManager db(path); // for editing data its delect old data in database
    if(db.isOpen())
    {
        db.removePerson(name,Aadhar);
    }
 ui->textEdit->clear();
}

void MainWindow::fillTables()
{
    DbManager db(path);
    int num_row,r,c;
    QSqlQuery q;
    if(!q.exec("select count(id) as num_row from peopledata")) qDebug()<<"first"+q.lastError().text();
    q.first();
    num_row=q.value(0).toInt();
    ui->tableWidget->setRowCount(num_row);

     if(!q.exec("select * from peopledata ORDER BY id DESC")) qDebug()<<"secound"+q.lastError().text();
    for(r=0,q.first();q.isValid();q.next(),r++)
    {
        for(c=0;c<9;c++){
            ui->tableWidget->setItem(r,c,new QTableWidgetItem(q.value(c).toString()));
        }
    }
}

void MainWindow::on_pushButton_5_clicked()
{
 ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_6_clicked()
{
    search1=ui->search_line->text();

    if(ui->search_line->text()!=NULL)
    {
       DbManager db(path);
       if(db.isOpen())
       {
           /* for searching in tableview
            *
             ui->TableView->show(); // to show the tables

             modal2 =new QSqlQueryModel();

            QSqlQuery* qry=new QSqlQuery();

            qry->prepare("select * from peopledata WHERE name='"+search1+"' or aadharno='"+search1+"' or itemid='"+search1+"' or moblieno='"+search1+"' ");
            qry->exec();

            qDebug()<<qry->exec();


           modal2->setQuery(*qry);*/


           int num_row,r,c;
           QSqlQuery q;


           if(!q.exec("select * from peopledata WHERE name='"+search1+"' or aadharno='"+search1+"' or itemid='"+search1+"' or moblieno='"+search1+"'")) qDebug()<<"secound"+q.lastError().text();
            q.first();
            num_row=q.value(0).toInt();
             ui->tableWidget->setRowCount(num_row);
           for(r=0,q.first();q.isValid();q.next(),r++)
          {
              for(c=0;c<9;c++){
                  ui->tableWidget->setItem(r,c,new QTableWidgetItem(q.value(c).toString()));
              }

      }
    }
   }
    else
    {
        QMessageBox::information(this,"Error Item_no ","Field must be non-emptly");
    }

    if(ui->tableWidget->rowCount()==NULL)
    {
        qDebug()<<"empty records";
        QMessageBox::information(this,"Error Item_no ","record is not valid");

        on_pushButton_2_clicked();

    }
    ui->search_line->clear();
}




void MainWindow::on_signout_clicked()
{
    hide();
    page1_dialog w;
   w.show();
    close();
    w.exec();
}

void MainWindow::on_item_editingFinished()
{
    int randomValue = randInt(1,20000);
    QString aString = QString::number(randomValue);
    ui->lineEdit->setText(aString);
}
