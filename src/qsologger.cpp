#include "newrecord.h"
#include "qsologger.h"
#include "qsomodel.h"
#include "ui_qsologger.h"


QSOLogger::QSOLogger(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QSOLogger)
{
    ui->setupUi(this);

    // Draw the UI.
    createActions();

    // Initialize the database.
    DatabaseHandler *database = new DatabaseHandler(QString("qso_logger"), this);
    database->setUpTables();

    // Render the QSOs table.
    showQSOTable();
}

QSOLogger::~QSOLogger()
{
    delete ui;
}

void QSOLogger::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.svg"));
    QAction *newAct = new QAction(newIcon, tr("&New QSO"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Add new QSO"));
    connect(newAct, &QAction::triggered, this, &QSOLogger::on_newQSO_clicked);
    fileMenu->addAction(newAct);

    const QIcon loadIcon = QIcon::fromTheme("document-open", QIcon(":/images/load_data.svg"));
    QAction *loadAct = new QAction(loadIcon, tr("&Load"), this);
    loadAct->setShortcuts(QKeySequence::Open);
    loadAct->setStatusTip(tr("Load existent QSO data"));
    fileMenu->addAction(loadAct);

    fileMenu->addSeparator();

    const QIcon closeIcon = QIcon::fromTheme("application-exit", QIcon(":/images/quit.svg"));
    QAction *quitAct = new QAction(closeIcon, tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit QSO Logger"));
    connect(quitAct, &QAction::triggered, this, &QSOLogger::close);
    fileMenu->addAction(quitAct);
}

void QSOLogger::showQSOTable()
{
    QSOModel *model = new QSOModel();
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->show();
}

void QSOLogger::on_newQSO_clicked()
{
    newRecord = new NewRecord();
    newRecord->show();

    connect(newRecord, &NewRecord::qsoCreated, this, &QSOLogger::on_qsoCreated);
}

void QSOLogger::on_qsoCreated()
{
    showQSOTable();
}
