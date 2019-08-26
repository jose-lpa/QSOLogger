#ifndef NEWRECORD_H
#define NEWRECORD_H

#include <QDialog>


namespace Ui {
    class Dialog;
}

class NewRecord : public QDialog
{
    Q_OBJECT

public:
    explicit NewRecord(QWidget *parent = nullptr);
    virtual ~NewRecord();

private:
    Ui::Dialog *ui;
};

#endif // NEWRECORD_H
