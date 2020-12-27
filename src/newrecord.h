#ifndef NEWRECORD_H
#define NEWRECORD_H

#include <QDialog>

#include "databasehandler.h"


namespace Ui {
    class Dialog;
}

struct Frequency {
    double lowest;
    double highest;
};

class NewRecord : public QDialog
{
    Q_OBJECT

public:
    explicit NewRecord(QWidget *parent = nullptr);
    virtual ~NewRecord();

signals:
    void qsoCreated();

private slots:
    void on_buttonBox_accepted();
    void on_callSignEdit_textChanged();
    void on_bandEdit_currentTextChanged(const QString &text);

private:
    Ui::Dialog *ui;
    DatabaseHandler *database;

    const QMap<QString, Frequency> bandFrequency {
        {QString("160m"), Frequency{1.810, 2.000}},
        {QString("80m"), Frequency{3.500, 3.800}},
        {QString("60m"), Frequency{5.000, 5.000}},
        {QString("40m"), Frequency{7.000, 7.200}},
        {QString("30m"), Frequency{10.100, 10.150}},
        {QString("20m"), Frequency{14.000, 14.350}},
        {QString("17m"), Frequency{18.068, 18.168}},
        {QString("15m"), Frequency{21.000, 21.450}},
        {QString("12m"), Frequency{24.890, 24.990}},
        {QString("10m"), Frequency{28.000, 29.700}},
        {QString("6m"), Frequency{50.000, 52.000}},
        {QString("4m"), Frequency{70.000, 70.500}},
        {QString("2m"), Frequency{144.000, 146.000}},
        {QString("70cm"), Frequency{430.000, 440.000}},
    };

    void setValidators();
};

#endif // NEWRECORD_H
