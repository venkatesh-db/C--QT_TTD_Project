#include "register_dialog.h"
#include "ui_register_dialog.h"
#include "dbmanager.h"
//#include "dialog.h"
#include "page1_dialog.h"
#include <QMessageBox>

static const QString path = "TTD1.db";


register_dialog::register_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_dialog)
{
    ui->setupUi(this);


}

register_dialog::~register_dialog()
{
    delete ui;
}

void register_dialog::on_pushButton_clicked()
{
 if(Validate_Data()!=-1)
{
    DbManager db(path);
    if(db.isOpen())
    {

       db.createTable();

       db.addPerson(ui->NAME->text(),ui->USERNAME->text(),ui->PASSWORD->text(),ui->EMAIL->text(),ui->MOBILENUMBER->text());

    }
    db.isClose();
    hide();
    page1_dialog w;
    w.show();
 }
}
int register_dialog::Validate_Data()
{

    if(ui->NAME->text().isEmpty())
    {
        QMessageBox::information(this,"Error","Pls Enter NAME..");
        ui->NAME->setFocus();
        return -1;
    }
    if(ui->USERNAME->text().isEmpty())
    {
        QMessageBox::information(this,"Error","Pls Enter USERNAME..");
        ui->USERNAME->setFocus();
        return -1;
    }
    if(ui->PASSWORD->text().isEmpty())
    {
        QMessageBox::information(this,"Error","Pls Enter PASSWORDE..");
        ui->PASSWORD->setFocus();
        return -1;
    }
    if(ui->EMAIL->text().isEmpty())
    {
        QMessageBox::information(this,"Error","Pls Enter EMAIL..");
        ui->EMAIL->setFocus();
        return -1;
    }

    if(!ui->MOBILENUMBER->text().isEmpty())
    {
        if((ui->MOBILENUMBER->text().count())!=10)
        {
                QMessageBox::information(this,"ErrorMOBILENUMBER","Pls Enter 10 Digites..");
                ui->MOBILENUMBER->setFocus();
                ui->MOBILENUMBER->clear();
                return -1;
        }
    }
    else
    {
            QMessageBox::information(this,"ErrorMOBILENUMBER","Pls Enter Mobile..");
            ui->MOBILENUMBER->setFocus();
            return -1;
    }
}

void register_dialog::on_REG_SUBMIT_clicked()
{
    hide();
    page1_dialog w;
    w.show();
}

void register_dialog::on_MOBILENUMBER_editingFinished()
{
    ui->MOBILENUMBER->setValidator(new QIntValidator(7000000000, 9999999999, this) );
}

