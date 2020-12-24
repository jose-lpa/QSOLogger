#ifndef QSOLOGGER_H
#define QSOLOGGER_H

#include <QMainWindow>

#include "databasehandler.h"
#include "newrecord.h"


namespace Ui {
    class QSOLogger;
}

class QSOLogger : public QMainWindow
{
    Q_OBJECT

public:
    explicit QSOLogger(QWidget *parent = nullptr);
    ~QSOLogger();

public slots:
    void on_newActTriggered();
    void on_qsoCreated();
    void about();

private:
    Ui::QSOLogger *ui;

    DatabaseHandler *database;
    NewRecord *newRecord;
    void createActions();
    void showQSOTable();
};

#endif // QSOLOGGER_H
