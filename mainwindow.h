#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTimer>
#include <QCloseEvent>
#include "ui_viewproblem.h"
#include "configuration.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bReloadName_clicked();

    void on_bReloadProblem_clicked();

    void on_bResetName_clicked();

    void on_bPopName_clicked();

    void on_bPushName_clicked();

    void on_bResetProblem_clicked();

    void on_bPopProblem_clicked();

    void on_bPushProblem_clicked();

    void on_listNAsked_itemDoubleClicked(QListWidgetItem *item);

    void on_listAsked_itemDoubleClicked(QListWidgetItem *item);

    void on_horizSpeed_valueChanged(int value);

    void on_bRoll_clicked();

    void on_timerRoll_timeout();

    void on_bStop_clicked();

    void on_labelProblem_clicked();

    void on_spinTextSize_valueChanged(int value);

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_bTextColor_clicked();

    void on_bTextItalic_toggled(bool checked);

    void on_bTextBold_toggled(bool checked);

    void on_bTextUnderline_toggled(bool checked);

    void on_bTimerStart_clicked();

    void on_timerTimer_timeout();

    void on_timerStopWatch_timeout();

    void on_bTimerStop_clicked();

    void on_bWatchStart_clicked();

    void on_bWatchStop_clicked();

private:
    const QString sessionFileName = "RollingLydiaSession.txt";

    Configuration config;
    Ui::MainWindow *ui;
    Ui::DialogProblem *dialogProblem_ui;
    QDialog *dialogProblem;
    QTimer *timerRoll;
    QTimer *timerTimer;
    QTimer *timerStopWatch;
    QTime timeTimer;
    QTime timeStopWatch;
    QListWidgetItem *currProblemItem = nullptr;
    QListWidgetItem *currNameItem = nullptr;
    int hz = 1;

private:
    void setupUi();
    void closeEvent(QCloseEvent *event) override;
    bool loadSession();
    void saveSession();
    void transferCurrItem(QListWidget *listSrc, QListWidget *listDst);
    void displayProblem(QListWidgetItem *item);
};


#endif // MAINWINDOW_H
