#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

#define DATABASE_NAME "sae201_diaporama"
    // le nom du DSN permettant d'accéder à la BDD
#define CONNECT_TYPE "QODBC"
    // permet d'indiquer que l'on veut utiliser le driver ODBC

class Database
{
public:
    Database();
    bool openDataBase();
    void closeDataBase();

private:
    QSqlDatabase _mydb;
};

#endif // DATABASE_H
