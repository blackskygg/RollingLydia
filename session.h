#ifndef SESSION_H
#define SESSION_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include <QListWidgetItem>
#include <QFont>
#include <QFile>

namespace  Ui {
    class DialogProblem;
    class MainWindow;
}

class WidgetItemObject {
public:
    WidgetItemObject() = default;

    void fromJson(const QJsonObject &obj);
    void fromQListWidgetItem(const QListWidgetItem &item);
    void applyToQListWidgetItem(QListWidgetItem &item);
    QJsonObject toJson();

private:
    QString text;
    QString data;
};

class WidgetItemListObject
{
public:
    WidgetItemListObject() = default;

    void fromQListWidget(const QListWidget &lw);
    void applyToQListWidget(QListWidget &lw);
    void fromJson(const QJsonArray &arr);
    QJsonArray toJson();

private:
    QList<WidgetItemObject> list;
};

class MainWindowObject
{
public:
    MainWindowObject() = default;

    void fromJson(const QJsonObject &obj);
    void fromMainWindowUi(const Ui::MainWindow &ui);
    void applyToMainWindowUi(Ui::MainWindow &ui);
    QJsonObject toJson();

private:
    WidgetItemListObject askedList;
    WidgetItemListObject  notAskedList;
    WidgetItemListObject  rolledList;
    WidgetItemListObject  notRolledList;

    int rollingSpeed = 0;
    int rollingMode = 0;
};

class ProblemViewerObject
{
public:
    ProblemViewerObject() = default;

    void fromJson(const QJsonObject &obj);
    void fromDialogProblemUi(const Ui::DialogProblem &ui);
    void applyToDialogProblemUi(Ui::DialogProblem &ui);
    QJsonObject toJson();

private:
    // Font settings
    QString family;
    int size = 17;
    bool isItalic = false;
    bool isBold = false;
    bool isUnderlined = false;

    // Color settings
    QString color;

    // Time limit settings;
    int minute = 0;
    int second = 0;
};

class Session
{
public:
    Session() = default;

    void fromUi(const Ui::MainWindow &mainUi, const Ui::DialogProblem &dialogUi);
    void applyToUi(Ui::MainWindow &mainUi, Ui::DialogProblem &dialogUi);
    QJsonObject toJson();
    void fromJson(const QJsonObject &obj);
    int save(QFile &file);
    int load(QFile &file);

public:
    // Mainwindow status;
    MainWindowObject mainObj;

    // Problem dialog status;
    ProblemViewerObject viewerObj;
};

#endif // SESSION_H
