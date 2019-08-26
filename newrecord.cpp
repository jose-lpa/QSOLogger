#include "newrecord.h"
#include "ui_record.h"


NewRecord::NewRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

NewRecord::~NewRecord()
{
    delete ui;
}
