#ifndef PAGE1_DIALOG_H
#define PAGE1_DIALOG_H

#include <QDialog>
//#include<dbmanager.h>
#include"dbmanager.h"
#include "mainwindow.h"
//#include <QMainWindow>
#include<QtSql/QSql>
#include<QtDebug>
#include<QFileInfo>


namespace Ui {
class page1_dialog;
}

class page1_dialog : public QDialog
{
    Q_OBJECT
    QString const push_login ;

QString loginname;

public:
    explicit page1_dialog(QWidget *parent = 0);
    ~page1_dialog();
QString passwor;
QString  usernam;
 QString   username ;
  QString   Vr[];
  QString   password;
  bool b;

  //void isClose() ;
 // bool isOpen() const;
  QSqlDatabase m_db;

  void isClose()
  {
       m_db.close();
  }

  bool isOpen() const
  {
      return m_db.isOpen();
  }

    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    page1_dialog(const QString& path);

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
   // ~page1_dialog();

   // void isClose() ;
   // bool isOpen() const;
    /**
     * @brief Creates a new 'people' table if it doesn't already exist
     * @return true - 'people' table created successfully, false - table not created
     */
    bool createTable();

    bool createTable1();

    bool add1Person(const QString& name );

    /**
     * @brief Add person data to db
     * @param name - name of person to add
     * @return true - person added successfully, false - person not added
     */
    bool addPerson(const QString& name, const QString &username, const QString &password, const QString &Emailid, const QString &mobileno);

    /**
     * @brief Remove person data from db
     * @param name - name of person to remove.
     * @return true - person removed successfully, false - person not removed
     */
    bool Checkinguser(const QString& name, const QString& password);

    /**
     * @brief Check if person of name "name" exists in db
     * @param name - name of person to check.
     * @return true - person exists, false - person does not exist
     */
    bool personExists(const QString& name) const;

    /**
     * @brief Print names of all persons in db
     */
    void printAllPersons1() const;

    /**
     * @brief Remove all persons from db
     * @return true - all persons removed successfully, false - not removed
     */
    bool removeAllPersons();


    friend class MainWindow;



private slots:



    void on_Login_clicked();



    void on_pushButton_clicked();

private:
    Ui::page1_dialog *ui;
};

#endif // PAGE1_DIALOG_H
