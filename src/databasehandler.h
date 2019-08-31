#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QDateTime>
#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlTableModel>


class DatabaseHandler : public QObject
{
    Q_OBJECT

public:
    DatabaseHandler(const QString &databaseName, QObject *parent = nullptr);
    ~DatabaseHandler();

    void setUpTables();

private:
    QSqlDatabase db;
};

#endif // DATABASEHANDLER_H
