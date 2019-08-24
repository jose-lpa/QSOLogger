#ifndef QSOLOGGER_H
#define QSOLOGGER_H

#include <QMainWindow>

#include "databasehandler.h"


namespace Ui {
    class QSOLogger;
}

class QSOLogger : public QMainWindow
{
    Q_OBJECT

public:
    explicit QSOLogger(QWidget *parent = nullptr);
    ~QSOLogger();

private:
    Ui::QSOLogger *ui;

    DatabaseHandler *database;
    void createActions();
    void showQSOTable();
};

#endif // QSOLOGGER_H
