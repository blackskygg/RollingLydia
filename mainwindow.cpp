#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_viewproblem.h"
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QFontDialog>
#include <QDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Setup UI
    ui->setupUi(this);
    dialogProblem_ui = new Ui::DialogProblem;
    dialogProblem = new QDialog(this);
    dialogProblem_ui->setupUi(dialogProblem);

    // Setup Timer
    timer = new QTimer(this);
    timer->setInterval(1);
    timer->stop();

    // Connect Events
    connect(dialogProblem_ui->bFont, SIGNAL(clicked()),
            this, SLOT(on_problem_bFont_clicked()));
    connect(timer, SIGNAL(timeout()), SLOT(on_timeout()));
    connect(ui->labelProblem, SIGNAL(clicked(bool)), this, SLOT(on_labelProblem_doubleClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dialogProblem_ui;
}

void MainWindow::transferCurrItem(QListWidget *listSrc, QListWidget *listDst)
{
    int row = listSrc->currentRow();
    QListWidgetItem *item = listSrc->takeItem(row);
    listDst->addItem(item);
}

void MainWindow::displayProblem(ProblemListItem *item)
{
    if (nullptr == item) return;

    dialogProblem_ui->textBrowser->clear();
    dialogProblem_ui->textBrowser->append(item->text());
    dialogProblem_ui->textBrowser->append(item->content());
    dialogProblem->show();
}

void MainWindow::on_bReloadName_clicked()
{
    QString filename =
        QFileDialog::getOpenFileName(this, "Please choose the name list file.");
    if (filename.isEmpty()) return;

    QFile file(filename);
    if (!file.open(QFile::ReadOnly|QFile::Text)) {
        QMessageBox::warning(this, tr("RollingLydia"),
                             tr("Can't open file %1: %2.")
                                .arg(QDir::toNativeSeparators(filename), file.errorString()));
        return;
    }

    ui->listNRolled->clear();
    QListWidgetItem *item;
    while (!file.atEnd()) {
        item = new QListWidgetItem(file.readLine(), ui->listNRolled);
        item->setSizeHint(QSize(item->sizeHint().width(), 20));
    }

    file.close();
}

void MainWindow::on_bReloadProblem_clicked()
{
    QString filename =
        QFileDialog::getOpenFileName(this, "Please choose the problem list file.");
    if (filename.isEmpty()) return;

    QFile file(filename);
    if (!file.open(QFile::ReadOnly|QFile::Text)) {
        QMessageBox::warning(this, tr("RollingLydia"),
                             tr("Can't open file %1: %2.")
                                .arg(QDir::toNativeSeparators(filename), file.errorString()));
        return;
    }

    ui->listNAsked->clear();
    QListWidgetItem *item;
    QString text, line;
    QStringList content;
    while (!file.atEnd()) {
        if("BEGIN\n" != file.readLine())
            continue;
        text = file.readLine();
        text.chop(1); // discard trailling newline
        content.clear();
        while (!file.atEnd()) {
            line = file.readLine();
            if ("END\n" == line)
                break;
            else
                content.append(line);
        };

        item = new ProblemListItem(text, ui->listNAsked, content.join(""));
        item->setSizeHint(QSize(item->sizeHint().width(), 20));
    }

    file.close();
}

void MainWindow::on_bResetName_clicked()
{
    QListWidgetItem *item;
    while (0 != ui->listRolled->count()) {
        item = ui->listRolled->takeItem(0);
        ui->listNRolled->addItem(item);
    }

}

void MainWindow::on_bPopName_clicked()
{
    transferCurrItem(ui->listNRolled, ui->listRolled);
}

void MainWindow::on_bPushName_clicked()
{
    transferCurrItem(ui->listRolled, ui->listNRolled);
}

void MainWindow::on_bResetProblem_clicked()
{
    QListWidgetItem *item;
    while (0 != ui->listAsked->count()) {
        item = ui->listAsked->takeItem(0);
        ui->listNAsked->addItem(item);
    }
}

void MainWindow::on_bPopProblem_clicked()
{
    transferCurrItem(ui->listNAsked, ui->listAsked);
}

void MainWindow::on_bPushProblem_clicked()
{
    transferCurrItem(ui->listAsked, ui->listNAsked);
}

void MainWindow::on_listNAsked_itemDoubleClicked(QListWidgetItem *item)
{
    displayProblem((ProblemListItem *)item);
}

void MainWindow::on_listAsked_itemDoubleClicked(QListWidgetItem *item)
{
    displayProblem((ProblemListItem *)item);
}

void MainWindow::on_problem_bFont_clicked()
{
   bool ok;
   QFont font = QFontDialog::getFont(&ok, dialogProblem);
   if (ok)
        dialogProblem_ui->textBrowser->setFont(font);
}

void MainWindow::on_horizSpeed_valueChanged(int value)
{
    hz = 20*value/100+1; // From 1Hz to 20Hz
    ui->labelSpeed->setText(tr("%1Hz").arg(hz));
}

void MainWindow::on_bRoll_clicked()
{
    if (0 == ui->listNRolled->count()) {
        QMessageBox::warning(this, "RollingLydia", "Name list is empty!");
        return;
    }

    if (0 == ui->comboMode->currentIndex() && 0 == ui->listNAsked->count()) {
        QMessageBox::warning(this, "RollingLydia", "Problem list is empty!");
        return;
    }
    ui->bRoll->setEnabled(false);
    timer->start();
    ui->bStop->setEnabled(true);
}

void MainWindow::on_timeout()
{
    static int count = 0;
    int target_cnt = 1000 / hz;
    if (++count >= target_cnt) {
        count = 0;
        int index = qrand() % ui->listNRolled->count();
        ui->labelName->setText(ui->listNRolled->item(index)->text());
        currNameItem = ui->listNRolled->item(index);

        if (0 == ui->comboMode->currentIndex()) {
            int index = qrand() % ui->listNAsked->count();
            ui->labelProblem->setText(ui->listNAsked->item(index)->text());
            currProblemItem = (ProblemListItem *)ui->listNAsked->item(index);
        }
    }
}

void MainWindow::on_bStop_clicked()
{
    ui->bStop->setEnabled(false);
    timer->stop();
    ui->listNAsked->setCurrentItem(currProblemItem);
    ui->listNRolled->setCurrentItem(currNameItem);
    transferCurrItem(ui->listNAsked, ui->listAsked);
    transferCurrItem(ui->listNRolled, ui->listRolled);
    ui->bRoll->setEnabled(true);
}

void MainWindow::on_labelProblem_doubleClicked()
{
    if (ui->bStop->isEnabled()) return; // Can't clicked till set.
    displayProblem(currProblemItem);
}
