#include <QMessageBox>
#include <QSqlError>
#include <QSqlField>

#include "qsomodel.h"


QSOModel::QSOModel(QObject *parent)
    : QSqlTableModel { parent }
{
    setTable("record");
    select();
    setHeaderData(0, Qt::Horizontal, tr("ID"));
    setHeaderData(1, Qt::Horizontal, tr("Time"));
    setHeaderData(2, Qt::Horizontal, tr("Call sign"));
    setHeaderData(3, Qt::Horizontal, tr("Band"));
    setHeaderData(4, Qt::Horizontal, tr("Frequency"));
    setHeaderData(5, Qt::Horizontal, tr("Mode"));
    setHeaderData(6, Qt::Horizontal, tr("Power"));
    setHeaderData(7, Qt::Horizontal, tr("Signal TX"));
    setHeaderData(8, Qt::Horizontal, tr("Signal RX"));
    setHeaderData(9, Qt::Horizontal, tr("Grid TX"));
    setHeaderData(10, Qt::Horizontal, tr("Grid RX"));
    setHeaderData(11, Qt::Horizontal, tr("Name"));
    setHeaderData(12, Qt::Horizontal, tr("Notes"));
}

void QSOModel::addQSO(const QDateTime &dateTime, const QString &callSign,
            const QString &name, const QString &band, const QString &mode,
            const double &frequency, const double &power,
            const QString &signalTx, const QString &signalRx,
            const QString &gridTx, const QString &gridRx,
            const QString &notes)
{
    // TODO: Move the `QSqlField` instantiations to constructor ^^^
    QSqlField dateTimeField("timestamp", QVariant::Int);
    dateTimeField.setValue(dateTime.currentSecsSinceEpoch());

    QSqlField callSignField("callsign", QVariant::String);
    callSignField.setValue(callSign);

    QSqlField nameField("name", QVariant::String);
    nameField.setValue(name);

    QSqlField bandField("band", QVariant::String);
    bandField.setValue(band);

    QSqlField modeField("mode", QVariant::String);
    modeField.setValue(mode);

    QSqlField frequencyField("frequency", QVariant::Double);
    frequencyField.setValue(frequency);

    QSqlField powerField("power", QVariant::Double);
    powerField.setValue(power);

    QSqlField signalTxField("signal_tx", QVariant::Int);
    signalTxField.setValue(signalTx);

    QSqlField signalRxField("signal_rx", QVariant::Int);
    signalRxField.setValue(signalRx);

    QSqlField gridTxField("grid_tx", QVariant::String);
    gridTxField.setValue(gridTx);

    QSqlField gridRxField("grid_rx", QVariant::String);
    gridRxField.setValue(gridRx);

    QSqlField notesField("notes", QVariant::String);
    notesField.setValue(notes);

    QSqlRecord record;

    record.append(dateTimeField);
    record.append(callSignField);
    record.append(nameField);
    record.append(bandField);
    record.append(modeField);
    record.append(frequencyField);
    record.append(powerField);
    record.append(signalTxField);
    record.append(signalRxField);
    record.append(gridTxField);
    record.append(gridRxField);
    record.append(notesField);

    // TODO: `emit` signal to update the table with new data after successful creation
    if (!insertRecord(-1, record))
    {
        QMessageBox errorMessage;
        errorMessage.setWindowTitle(tr("QSO Logger error"));
        errorMessage.setText(lastError().text());  // FIXME: no `lastError` here.
        errorMessage.setIcon(QMessageBox::Critical);
        errorMessage.exec();
    }
    else
    {
        QMessageBox successMessage;
        successMessage.setWindowTitle(tr("QSO Added"));
        successMessage.setText(tr("New QSO successfully created."));
        successMessage.setIcon(QMessageBox::Information);
        successMessage.exec();
    }
}
