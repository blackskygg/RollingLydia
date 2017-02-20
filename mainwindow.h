#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTimer>
#include <QCloseEvent>
#include "ui_viewproblem.h"

namespace Ui {
class MainWindow;
}

class ProblemListItem : public QListWidgetItem
{
public:
    ProblemListItem(const QString &text, QListWidget *view, const QString &content) :
        QListWidgetItem(text, view)
    {
        content_ = content;
    }

    QString &content() {return content_;}
private:
    QString content_;


};

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

    void on_timeout();

    void on_bStop_clicked();

    void on_labelProblem_clicked();

    void on_spinTextSize_valueChanged(int value);

    void on_fontComboBox_currentFontChanged(const QFont &f);

private:
    const QString sessionFileName = "RollingLydiaSession.txt";

    Ui::MainWindow *ui;
    Ui::DialogProblem *dialogProblem_ui;
    QDialog *dialogProblem;
    QTimer *timer;
    ProblemListItem *currProblemItem = nullptr;
    QListWidgetItem *currNameItem = nullptr;
    int hz = 1;

private:
    void setupUi();
    void closeEvent(QCloseEvent *event) override;
    bool loadSession();
    void saveSession();
    void transferCurrItem(QListWidget *listSrc, QListWidget *listDst);
    void displayProblem(ProblemListItem *item);
};


#endif // MAINWINDOW_H
