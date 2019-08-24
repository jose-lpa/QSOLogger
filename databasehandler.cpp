#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "databasehandler.h"


DatabaseHandler::DatabaseHandler(const QString &dbname, QObject *parent)
    : QObject { parent }
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    db.open();

    model = new QSqlTableModel(parent, db);

    model->setTable("record");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(0, Qt::Horizontal, tr("Time"));
    model->setHeaderData(0, Qt::Horizontal, tr("Call sign"));
    model->setHeaderData(0, Qt::Horizontal, tr("Band"));
    model->setHeaderData(0, Qt::Horizontal, tr("Frequency"));
    model->setHeaderData(0, Qt::Horizontal, tr("Mode"));
    model->setHeaderData(0, Qt::Horizontal, tr("Power"));
    model->setHeaderData(0, Qt::Horizontal, tr("Signal TX"));
    model->setHeaderData(0, Qt::Horizontal, tr("Signal RX"));
    model->setHeaderData(0, Qt::Horizontal, tr("Grid TX"));
    model->setHeaderData(0, Qt::Horizontal, tr("Grid RX"));
    model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    model->setHeaderData(0, Qt::Horizontal, tr("Notes"));
}

bool DatabaseHandler::setUpTables(QString *error)
{
    QSqlQuery query;

    bool result = query.exec(
        "CREATE TABLE IF NOT EXISTS record ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "timestamp INTEGER NOT NULL,"
        "callsign TEXT NOT NULL,"
        "band INTEGER NOT NULL,"
        "frequency REAL,"
        "mode TEXT,"
        "power INTEGER,"
        "signal_tx INTEGER,"
        "signal_rx INTEGER,"
        "grid_tx TEXT,"
        "grid_rx TEXT,"
        "name TEXT,"
        "notes TEXT)"
    );

    if (result)
        return true;
    else {
        if (error)
            *error = query.lastError().text();

        return false;
    }
}

DatabaseHandler::~DatabaseHandler()
{
    db.close();
}

QSqlTableModel *DatabaseHandler::getModel()
{
    return model;
}
