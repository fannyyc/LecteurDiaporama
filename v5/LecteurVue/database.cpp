#include "database.h"

Database::Database()
{

}

bool Database::openDataBase()
{
    _mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    _mydb.setDatabaseName(DATABASE_NAME);
    return _mydb.open();
}

void Database::closeDataBase()
{
    _mydb.close();
}
