#ifndef DBMANAGER_H
#define DBMANAGER_H

//#include <QSqlDatabase>
#include<QtSql/QSqlDatabase>
#include<QDate>
#include<QTime>

/**
 * \class DbManager
 *
 * \brief SQL Database Manager class
 *
 * DbManager sets up the connection with SQL database
 * and performs some basics queries. The class requires
 * existing SQL database. You can create it with sqlite:
 * 1. $ sqlite3 people.db
 * 2. sqilte> CREATE TABLE people(ids integer primary key, name text);
 * 3. sqlite> .quit
 */
class DbManager
{
public:
    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    DbManager(const QString& path);

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbManager();

    bool isOpen() const;
     void isClose() ;

    /**
     * @brief Creates a new 'people' table if it doesn't already exist
     * @return true - 'people' table created successfully, false - table not created
     */
    bool createTable();
    bool createdataTable();

    /**
     * @brief Add person data to db
     * @param name - name of person to add
     * @return true - person added successfully, false - person not added
     */
    bool addPerson(const QString& name, const QString &username, const QString &password, const QString &Emailid, const QString &mobileno);
    bool adddataPerson(const QString& name, const QString& moblieno, const QString& state, const QString& aadharno, const QString& itemno, const QString &itemid, const QDate& date, const QTime& time);
    /**
     * @brief Remove person data from db
     * @param name - name of person to remove.
     * @return true - person removed successfully, false - person not removed
     */
    bool removePerson(const QString& name,const QString& aadharno);

    /**
     * @brief Check if person of name "name" exists in db
     * @param name - name of person to check.
     * @return true - person exists, false - person does not exist
     */
    bool personExists(const QString& name, const QString &aadharno) const;

    bool personExists1(const QString& name1) const;
    /**
     * @brief Print names of all persons in db
     */
    void printAllPersons() const;

    /**
     * @brief Remove all persons from db
     * @return true - all persons removed successfully, false - not removed
     */
    bool removeAllPersons();


    QSqlDatabase m_db;


private:

};

#endif // DBMANAGER_H
