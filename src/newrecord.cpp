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

void NewRecord::setValidators()
{
    // Validate call sign input.
    QRegExp callSignRegEx("^[A-Za-z0-9]{3,7}$");
    QRegExpValidator *callSignValidator = new QRegExpValidator(callSignRegEx);
    ui->callSignEdit->setValidator(callSignValidator);

    // Validate grid locators input.
    QRegExp gridRegEx("^[A-R]{2}[0-9]{2}[a-x]{2}[0-9]{2}$");
    QRegExpValidator *gridTxValidator = new QRegExpValidator(gridRegEx);
    ui->gridTxEdit->setValidator(gridTxValidator);
    ui->gridRxEdit->setValidator(gridTxValidator);
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

void NewRecord::on_bandEdit_currentTextChanged(const QString &text)
{
    // Obtain the minimum and maximum frequency values for the given band.
    Frequency frequency = bandFrequency.value(text);

    // Modify the `frequencyEdit` widget to accommodate boundaries and default
    // value to currently selected band.
    ui->frequencyEdit->setMinimum(frequency.lowest);
    ui->frequencyEdit->setMaximum(frequency.highest);
    ui->frequencyEdit->setValue(frequency.lowest);
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
