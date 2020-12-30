#include <QMessageBox>

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
    // 'File' menu.
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    const QIcon newIcon = QIcon::fromTheme("document-new",
                                           QIcon(":/images/new.svg"));
    QAction *newAct = new QAction(newIcon, tr("&New QSO"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Add new QSO"));
    connect(newAct, &QAction::triggered, this, &QSOLogger::on_newActTriggered);
    fileMenu->addAction(newAct);

    const QIcon loadIcon = QIcon::fromTheme("document-open",
                                            QIcon(":/images/load_data.svg"));
    QAction *loadAct = new QAction(loadIcon, tr("&Load"), this);
    loadAct->setShortcuts(QKeySequence::Open);
    loadAct->setStatusTip(tr("Load existent QSO data"));
    fileMenu->addAction(loadAct);

    fileMenu->addSeparator();

    const QIcon closeIcon = QIcon::fromTheme("application-exit",
                                             QIcon(":/images/quit.svg"));
    QAction *quitAct = new QAction(closeIcon, tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit QSO Logger"));
    connect(quitAct, &QAction::triggered, this, &QSOLogger::close);
    fileMenu->addAction(quitAct);

    // 'Help' menu.
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    const QIcon aboutIcon = QIcon::fromTheme("help-about",
                                             QIcon(":/images/info.svg"));
    QAction *aboutAct = new QAction(aboutIcon, tr("&About"), this);
    aboutAct->setStatusTip((tr("About QSO Logger")));
    connect(aboutAct, &QAction::triggered, this, &QSOLogger::about);
    helpMenu->addAction(aboutAct);
}

void QSOLogger::showQSOTable()
{
    QSOModel *model = new QSOModel();
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->show();
}

void QSOLogger::on_newActTriggered()
{
    newRecord = new NewRecord();
    newRecord->show();

    connect(newRecord, &NewRecord::qsoCreatedSuccess, this, &QSOLogger::on_qsoCreated);
}

void QSOLogger::on_qsoCreated()
{
    showQSOTable();
}

void QSOLogger::about()
{
    QMessageBox::about(
        this, tr("About QSO Logger"),
        tr("<b>A simple application for radio amateurs to log QSO's</b>.<br>"
           "<br>Written using Qt5.<br>"
           "<br>This program is licensed under GPL version 3. You can read the"
           " license terms "
           "<a href=\"https://www.gnu.org/licenses/gpl-3.0.html\">here</a>.<br>"
           "<br>The source code is available in "
           "<a href=\"https://github.com/jose-lpa/QSOLogger\">GitHub</a>."));
}
