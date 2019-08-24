#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlTableModel>
//#include <QSqlRecord>


class DatabaseHandler : public QObject
{
    Q_OBJECT

public:
    DatabaseHandler(const QString &databaseName, QObject *parent = nullptr);
    ~DatabaseHandler();

    bool setUpTables(QString *error);
    QSqlTableModel *getModel();
    //void insertRow(const QString &table, const QSqlRecord &record);

private:
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // DATABASEHANDLER_H
