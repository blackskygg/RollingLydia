#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QJsonObject>
#include <QVariant>
#include <QListWidgetItem>
#include <QFont>

namespace  Ui {
    class DialogProblem;
}

class WidgetItemObject
{
public:
    WidgetItemObject() = default;

    void fromJson(QJsonObject &obj);
    void fromQListWidgetItem(QListWidgetItem &item);
    void applyToQListWidgetItem(QListWidgetItem &item);
    QJsonObject toJson();

private:
    QString text;
    QString data;
};

class ProblemViewerObject {
public:
    ProblemViewerObject();

    void fromJson(QJsonObject &obj);
    void fromDialogProblemUi(Ui::DialogProblem &ui);
    void applyToDialogProblemUi(Ui::DialogProblem &ui);
    QJsonObject toJson();

private:
    // Font settings
    QString family;
    int size;
    bool isItalic;
    bool isBold;
    bool isUnderlined;

    // Color settings
    QString color;

    // Time limit settings;
    int minute;
    int second;
};

class Configuration
{
public:
    Configuration();
    Configuration(QString &filename);

    bool isValid() {return isValid_;}

public:
    // Mainwindow status;
    QList<WidgetItemObject> askedList;
    QList<WidgetItemObject> notAskedList;
    QList<WidgetItemObject> rolledList;
    QList<WidgetItemObject> notRolledList;

    int rollingSpeed;
    int mode;

    // Problem dialog status;
    ProblemViewerObject viewer;

private:
    bool isValid_;

};

#endif // CONFIGURATION_H
