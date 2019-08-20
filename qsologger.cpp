#include "qsologger.h"
#include "ui_qsologger.h"

QSOLogger::QSOLogger(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QSOLogger)
{
    ui->setupUi(this);

    createActions();

    // Create new model.
    model = new QStandardItemModel(4, 2, this);

    // Attach the model to the view.
    ui->tableView->setModel(model);

    // Add (dummy) data to the table;
    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 2; column++)
        {
            QModelIndex index = model->index(row, column, QModelIndex());
            model->setData(index, "Testing");
        }
    }
}

QSOLogger::~QSOLogger()
{
    delete ui;
}

void QSOLogger::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    const QIcon loadIcon = QIcon::fromTheme("document-open", QIcon(":/images/load_data.svg"));
    QAction *loadAct = new QAction(loadIcon, tr("&Load"), this);
    loadAct->setShortcuts(QKeySequence::New);
    loadAct->setStatusTip(tr("Load existent QSO data"));
    fileMenu->addAction(loadAct);

    fileMenu->addSeparator();

    const QIcon closeIcon = QIcon::fromTheme("application-exit", QIcon(":/images/quit.svg"));
    QAction *quitAct = new QAction(closeIcon, tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit QSO Logger"));
    fileMenu->addAction(quitAct);
}
