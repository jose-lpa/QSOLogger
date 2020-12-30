#include <QMessageBox>
#include <QPushButton>

#include "databasehandler.h"
#include "newrecord.h"
#include "ui_record.h"


NewRecord::NewRecord(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->callSignEdit->setInputMethodHints(Qt::ImhUppercaseOnly);

    setValidators();

    model = new QSOModel();

    connect(model, &QSOModel::qsoCreated, this, &NewRecord::on_qsoCreated);
    connect(model, &QSOModel::qsoCreationFailed, this, &NewRecord::on_qsoCreated);
}

NewRecord::~NewRecord()
{
    delete ui;
    delete model;
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

void NewRecord::on_qsoCreated()
{
    QMessageBox successMessage;
    successMessage.setWindowTitle(tr("QSO Added"));
    successMessage.setText(tr("New QSO successfully created."));
    successMessage.setIcon(QMessageBox::Information);
    successMessage.exec();

    emit qsoCreatedSuccess();
}

void NewRecord::on_qsoCreationFailed()
{
    QMessageBox errorMessage;
    errorMessage.setWindowTitle(tr("QSO Logger error"));
    errorMessage.setText(tr("Database error: unable to store QSO."));
    errorMessage.setIcon(QMessageBox::Critical);
    errorMessage.exec();
}
