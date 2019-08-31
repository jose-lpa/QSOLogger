#ifndef QSOMODEL_H
#define QSOMODEL_H

#include <QDateTime>
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
};

#endif // QSOMODEL_H
