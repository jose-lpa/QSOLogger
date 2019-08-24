#include <QDateTime>
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
    model->setHeaderData(1, Qt::Horizontal, tr("Time"));
    model->setHeaderData(2, Qt::Horizontal, tr("Call sign"));
    model->setHeaderData(3, Qt::Horizontal, tr("Band"));
    model->setHeaderData(4, Qt::Horizontal, tr("Frequency"));
    model->setHeaderData(5, Qt::Horizontal, tr("Mode"));
    model->setHeaderData(6, Qt::Horizontal, tr("Power"));
    model->setHeaderData(7, Qt::Horizontal, tr("Signal TX"));
    model->setHeaderData(8, Qt::Horizontal, tr("Signal RX"));
    model->setHeaderData(9, Qt::Horizontal, tr("Grid TX"));
    model->setHeaderData(10, Qt::Horizontal, tr("Grid RX"));
    model->setHeaderData(11, Qt::Horizontal, tr("Name"));
    model->setHeaderData(12, Qt::Horizontal, tr("Notes"));

    QSqlQuery query;

    qint64 timestamp = QDateTime::currentSecsSinceEpoch();

    query.prepare(
        "INSERT INTO record ("
        "timestamp, callsign, band, frequency, mode, power, signal_tx,"
        "signal_rx, grid_tx, grid_rx, name, notes) "
        "VALUES ("
        ":timestamp, :callsign, :band, :frequency, :mode, :power, :signal_tx,"
        ":signal_rx, :grid_tx, :grid_rx, :name, :notes)"
    );
    query.bindValue(":timestamp", timestamp);
    query.bindValue(":callsign", "2E0IST");
    query.bindValue(":band", "20m");
    query.bindValue(":frequency", 14.234);
    query.bindValue(":mode", "SSB");
    query.bindValue(":power", 50);
    query.bindValue(":signal_tx", 59);
    query.bindValue(":signal_rx", 57);
    query.bindValue(":grid_tx", "IO91jo");
    query.bindValue(":grid_rx", "EL34is");
    query.bindValue(":name", "Jerry");
    query.bindValue(":notes", "Something curious about the contact.");

    if (!query.exec())
        qFatal("ERROR: Database query error. %s.",
               query.lastError().text().toStdString().c_str());
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
