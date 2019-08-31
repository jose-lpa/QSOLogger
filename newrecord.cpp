#include "databasehandler.h"
#include "newrecord.h"
#include "qsomodel.h"
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

void NewRecord::on_buttonBox_accepted()
{
    QSOModel *model = new QSOModel();
    model->addQSO(ui->dateTimeEdit->dateTime(),
                  ui->callSignEdit->text(),
                  ui->nameEdit->text(),
                  ui->bandEdit->currentText(),
                  ui->modeEdit->currentText(),
                  ui->frequencyEdit->value(),
                  ui->powerTxEdit->value(),
                  ui->signalTxEdit->text(),
                  ui->signalRxEdit->text(),
                  ui->gridTxEdit->text(),
                  ui->gridRxEdit->text(),
                  ui->notesEdit->toPlainText());
}
