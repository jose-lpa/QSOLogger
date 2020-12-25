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

signals:
    void qsoCreated();

private slots:
    void on_buttonBox_accepted();
    void on_callSignEdit_textChanged();

private:
    Ui::Dialog *ui;

    DatabaseHandler *database;

    void setValidators();
};

#endif // NEWRECORD_H
