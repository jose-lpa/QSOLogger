#include <QDateTime>
#include <QSqlError>
#include <QSqlQuery>

#include "databasehandler.h"


DatabaseHandler::DatabaseHandler(const QString &dbname, QObject *parent)
    : QObject { parent }
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    db.open();
}

void DatabaseHandler::setUpTables()
{
    QSqlQuery query;

    bool result = query.exec(
        "CREATE TABLE IF NOT EXISTS record ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "timestamp INTEGER NOT NULL,"
        "callsign TEXT NOT NULL,"
        "band TEXT NOT NULL,"
        "frequency REAL,"
        "mode TEXT,"
        "power REAL,"
        "signal_tx INTEGER,"
        "signal_rx INTEGER,"
        "grid_tx TEXT,"
        "grid_rx TEXT,"
        "name TEXT,"
        "notes TEXT)"
    );

    if (!result)
        qFatal("ERROR: Can't set up database. %s.",
               query.lastError().text().toStdString().c_str());
}

DatabaseHandler::~DatabaseHandler()
{
    db.close();
}
