#ifndef QSOMODEL_H
#define QSOMODEL_H

#include <QDateTime>
#include <QSqlField>
#include <QSqlTableModel>
#include <QSqlRecord>


class QSOModel : public QSqlTableModel
{
    Q_OBJECT

public:
    QSOModel(QObject *parent = nullptr);
    bool addQSO(const QDateTime &dateTime, const QString &callSign,
                const QString &name, const QString &band, const QString &mode,
                const double &frequency, const double &power,
                const QString &signalTx, const QString &signalRx,
                const QString &gridTx, const QString &gridRx,
                const QString &notes);

private:
    QSqlField dateTimeField = QSqlField("timestamp", QVariant::DateTime);
    QSqlField callSignField = QSqlField("callsign", QVariant::String);
    QSqlField nameField = QSqlField("name", QVariant::String);
    QSqlField bandField = QSqlField("band", QVariant::String);
    QSqlField modeField = QSqlField("mode", QVariant::String);
    QSqlField frequencyField = QSqlField("frequency", QVariant::Double);
    QSqlField powerField = QSqlField("power", QVariant::Double);
    QSqlField signalTxField = QSqlField("signal_tx", QVariant::Int);
    QSqlField signalRxField = QSqlField("signal_rx", QVariant::Int);
    QSqlField gridTxField = QSqlField("grid_tx", QVariant::String);
    QSqlField gridRxField = QSqlField("grid_rx", QVariant::String);
    QSqlField notesField = QSqlField("notes", QVariant::String);
};

#endif // QSOMODEL_H
