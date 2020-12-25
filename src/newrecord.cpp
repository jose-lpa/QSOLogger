#include <QPushButton>

#include "databasehandler.h"
#include "newrecord.h"
#include "qsomodel.h"
#include "ui_record.h"


NewRecord::NewRecord(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->callSignEdit->setInputMethodHints(Qt::ImhUppercaseOnly);

    setValidators();
}

NewRecord::~NewRecord()
{
    delete ui;
}

void NewRecord::setValidators() {
    QRegExp regEx("^[A-Za-z0-9]{3,7}$");
    QRegExpValidator *validator = new QRegExpValidator(regEx);
    ui->callSignEdit->setValidator(validator);
}

void NewRecord::on_callSignEdit_textChanged()
{
    QString callSignEditValue = ui->callSignEdit->text();

    // Always turn letters into uppercase.
    ui->callSignEdit->setText(callSignEditValue.toUpper());

    // Form can only be submitted if the call sign seems to be a valid one.
    if (!callSignEditValue.isEmpty() && callSignEditValue.length() > 2) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void NewRecord::on_buttonBox_accepted()
{
    QSOModel *model = new QSOModel();
    bool created = model->addQSO(ui->dateTimeEdit->dateTime(),
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

    if (created)
        emit qsoCreated();
}
