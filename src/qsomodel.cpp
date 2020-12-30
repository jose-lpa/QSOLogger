#include <QMessageBox>
#include <QSqlError>
#include <QSqlField>

#include "qsomodel.h"


QSOModel::QSOModel(QObject *parent) : QSqlTableModel { parent }
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
    dateTimeField.setValue(dateTime.currentSecsSinceEpoch());
    callSignField.setValue(callSign);
    nameField.setValue(name);
    bandField.setValue(band);
    modeField.setValue(mode);
    frequencyField.setValue(frequency);
    powerField.setValue(power);
    signalTxField.setValue(signalTx);
    signalRxField.setValue(signalRx);
    gridTxField.setValue(gridTx);
    gridRxField.setValue(gridRx);
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

    if (!insertRecord(-1, record))
    {
        emit qsoCreated();
    }
    else
    {
        emit qsoCreationFailed();

        if (lastError().isValid()) {
            qCritical("Database error: %s",
                      qUtf8Printable(lastError().databaseText().toUtf8()));
        }
    }
}
