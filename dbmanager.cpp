
#include "dbmanager.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>

static const QString path = "TTD1.db";

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

void DbManager::isClose()
{
    return m_db.close();
}

bool DbManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE people(id INTEGER PRIMARY KEY, name TEXT, username TEXT, password TEXT, Emailid TEXT, mobileno TEXT);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'people': one might already exist.";
        success = false;
    }

    return success;
}

bool DbManager::createdataTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE peopledata(id INTEGER PRIMARY KEY, name TEXT, moblieno TEXT, state TEXT, aadharno TEXT, itemno TEXT, itemid TEXT ,date DATE,time TIME);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'peopledata': one might already exist.";
        success = false;
    }

    return success;
}

bool DbManager::addPerson(const QString& name, const QString& username, const QString& password, const QString &Emailid, const QString &mobileno)
{
    bool success = false;

    if(!name.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO people (name, username, password, Emailid, mobileno) VALUES (:name, :username, :password, :Emailid, :mobileno)");
        queryAdd.bindValue(":name", name);
        queryAdd.bindValue(":username", username);
        queryAdd.bindValue(":password", password);
        queryAdd.bindValue(":Emailid", Emailid);
        queryAdd.bindValue(":mobileno", mobileno);

        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add person failed: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add person failed: name cannot be empty";
    }

    return success;
}

bool DbManager::adddataPerson(const QString& name, const QString& moblieno, const QString& state, const QString& aadharno, const QString& itemno,const QString& itemid, const QDate &date, const QTime &time)
{
    bool success = false;

    if(!name.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO peopledata (name, moblieno, state, aadharno, itemno,itemid, date, time) VALUES (:name, :moblieno, :state, :aadharno, :itemno, :itemid, :date, :time)");
        queryAdd.bindValue(":name", name);
        queryAdd.bindValue(":moblieno", moblieno);
        queryAdd.bindValue(":state", state);
        queryAdd.bindValue(":aadharno", aadharno);
        queryAdd.bindValue(":itemno", itemno);
        queryAdd.bindValue(":itemid", itemid);
        queryAdd.bindValue(":date", date);
        queryAdd.bindValue(":time", time);

        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add person failed: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add person failed: name cannot be empty";
    }

    return success;
}


bool DbManager::removePerson(const QString& name,const QString& aadharno)
{
    bool success = false;

    if (personExists(name,aadharno))
    {
        QSqlQuery queryD;
        queryD.prepare("DELETE  FROM peopledata WHERE name = (:name) and aadharno =(:aadharno)");
        queryD.bindValue(":name", name);
        queryD.bindValue(":aadharno", aadharno);
        success = queryD.exec();

        if(!success)
        {
            qDebug() << "remove person faileds: " << queryD.lastError();
        }
    }
    else
    {
        qDebug() << "remove person failed: person doesnt exist";
    }

    return success;
}

void DbManager::printAllPersons() const
{
    qDebug() << "Persons in db:";
  //  QSqlQueryModel * modal=new QSqlQueryModel();
    QSqlQuery query("SELECT * FROM peopledata");
   int idName = query.record().indexOf("name");
    while (query.next())
    {
        QString name = query.value(idName).toString();
        qDebug() << idName << "===" << name;
    }


    query.exec();

}

bool DbManager::personExists(const QString& name,const QString& aadharno) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name,aadharno FROM peopledata WHERE  name=(:name) and aadharno =(:aadharno) ");
    checkQuery.bindValue(":name", name);
    checkQuery.bindValue(":aadharno", aadharno);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "person exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::personExists1(const QString& name1) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name FROM people WHERE name1=(:password)");
    //checkQuery.bindValue(":username", name);
    checkQuery.bindValue(":password", name1);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "person exists1 failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::removeAllPersons()
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM people");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all persons failed: " << removeQuery.lastError();
    }

    return success;
}
