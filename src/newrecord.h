#ifndef NEWRECORD_H
#define NEWRECORD_H

#include <QDialog>

#include "databasehandler.h"


namespace Ui {
    class Dialog;
}

class NewRecord : public QDialog
{
    Q_OBJECT

public:
    explicit NewRecord(QWidget *parent = nullptr);
    virtual ~NewRecord();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;

    DatabaseHandler *database;
};

#endif // NEWRECORD_H
