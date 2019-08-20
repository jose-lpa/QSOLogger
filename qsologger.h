#ifndef QSOLOGGER_H
#define QSOLOGGER_H

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
    class QSOLogger;
}

class QSOLogger : public QMainWindow
{
    Q_OBJECT

public:
    explicit QSOLogger(QWidget *parent = nullptr);
    ~QSOLogger();

    QStandardItemModel *model;

private:
    Ui::QSOLogger *ui;

    void createActions();
};

#endif // QSOLOGGER_H
