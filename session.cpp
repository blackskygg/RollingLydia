#include "session.h"
#include "ui_viewproblem.h"
#include "ui_mainwindow.h"
#include <QTextBrowser>
#include <QJsonDocument>
#include <QFont>
#include <QVariant>
#include <QFile>
#include <QTime>
#include <QTimeEdit>
#include <QFontComboBox>
#include <QPalette>
#include <QListWidgetItem>

int Session::load(QFile &file)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject jsonObj = jsonDoc.object();
    fromJson(jsonObj);

    return 0;
}

int Session::save(QFile &file)
{
    QJsonDocument jsonDoc;
    jsonDoc.setObject(toJson());
    file.write(jsonDoc.toJson());

    return 0;
}

void Session::fromJson(const QJsonObject &obj)
{
    mainObj.fromJson(obj["mainwindow"].toObject());
    viewerObj.fromJson(obj["problemviewer"].toObject());
}

QJsonObject Session::toJson()
{
    QJsonObject obj;
    obj["mainwindow"] = mainObj.toJson();
    obj["problemviewer"] = viewerObj.toJson();
    return obj;
}

void Session::fromUi(const Ui::MainWindow &mainUi, const Ui::DialogProblem &dialogUi)
{
    mainObj.fromMainWindowUi(mainUi);
    viewerObj.fromDialogProblemUi(dialogUi);
}

void Session::applyToUi(Ui::MainWindow &mainUi, Ui::DialogProblem &dialogUi)
{
    mainObj.applyToMainWindowUi(mainUi);
    viewerObj.applyToDialogProblemUi(dialogUi);
}

void WidgetItemObject::fromJson(const QJsonObject &obj)
{
    text = obj["text"].toString();
    data = obj["data"].toString();
}

void WidgetItemObject::fromQListWidgetItem(const QListWidgetItem &item)
{
    text = item.text();
    data = item.data(Qt::UserRole).toString();
}

void WidgetItemObject::applyToQListWidgetItem(QListWidgetItem &item)
{
    item.setText(text);
    item.setData(Qt::UserRole, QVariant(data));
}

QJsonObject WidgetItemObject::toJson()
{
    QJsonObject obj;
    obj["text"] = text;
    obj["data"] = data;
    return obj;
}

void WidgetItemListObject::fromJson(const QJsonArray &arr)
{
    for (const QJsonValue &val : arr) {
        WidgetItemObject obj;
        obj.fromJson(val.toObject());
        list.append(obj);
    }
}

QJsonArray WidgetItemListObject::toJson()
{
    QJsonArray arr;

    for (WidgetItemObject &obj : list) {
        arr.append(QJsonValue(obj.toJson()));
    }

    return arr;
}

void WidgetItemListObject::fromQListWidget(const QListWidget &lw)
{
    int cnt = lw.count();
    for (int i = 0; i < cnt; ++i) {
        WidgetItemObject obj;
        obj.fromQListWidgetItem(*lw.item(i));
        list.append(obj);
    }
}

void WidgetItemListObject::applyToQListWidget(QListWidget &lw)
{
    for (WidgetItemObject &obj: list) {
        QListWidgetItem *item = new QListWidgetItem(&lw);
        obj.applyToQListWidgetItem(*item);
        item->setSizeHint(QSize(item->sizeHint().width(), 20));
    }
}

void MainWindowObject::fromJson(const QJsonObject &obj)
{
    askedList.fromJson(obj["askedList"].toArray());
    notAskedList.fromJson(obj["notAskedList"].toArray());
    rolledList.fromJson(obj["rolledList"].toArray());
    notRolledList.fromJson(obj["notRolledList"].toArray());

    rollingSpeed = obj["rollingSpeed"].toInt();
    rollingMode = obj["rollingMode"].toInt();
}

QJsonObject MainWindowObject::toJson()
{
    QJsonObject obj;

    obj["askedList"] = askedList.toJson();
    obj["notAskedList"] = notAskedList.toJson();
    obj["rolledList"] = rolledList.toJson();
    obj["notRolledList"] = notRolledList.toJson();

    obj["rollingSpeed"] = rollingSpeed;
    obj["rollingMode"] = rollingMode;

    return obj;
}

void MainWindowObject::fromMainWindowUi(const Ui::MainWindow &ui)
{
    askedList.fromQListWidget(*ui.listAsked);
    notAskedList.fromQListWidget(*ui.listNAsked);
    rolledList.fromQListWidget(*ui.listRolled);
    notRolledList.fromQListWidget(*ui.listNRolled);

    rollingSpeed = ui.horizSpeed->value();
    rollingMode = ui.comboMode->currentIndex();
}

void MainWindowObject::applyToMainWindowUi(Ui::MainWindow &ui)
{
    askedList.applyToQListWidget(*ui.listAsked);
    notAskedList.applyToQListWidget(*ui.listNAsked);
    rolledList.applyToQListWidget(*ui.listRolled);
    notRolledList.applyToQListWidget(*ui.listNRolled);

    ui.horizSpeed->setValue(rollingSpeed);
    ui.comboMode->setCurrentIndex(rollingMode);
}

void ProblemViewerObject::fromJson(const QJsonObject &obj)
{
    family = obj["family"].toString();
    size = obj["size"].toInt();
    isItalic = obj["isItalic"].toBool();
    isBold = obj["isBold"].toBool();
    isUnderlined = obj["isUnderlined"].toBool();
    color = obj["color"].toString();
    minute = obj["minute"].toInt();
    second = obj["second"].toInt();
}

void ProblemViewerObject::fromDialogProblemUi(const Ui::DialogProblem &ui)
{
    QTextBrowser *browser = ui.textBrowser;
    QFont font = browser->font();
    QColor pal_color = browser->palette().color(QPalette::Text);
    QTime time = ui.timeEditLimit->time();

    family = font.family();
    size = font.pixelSize();
    isItalic = font.italic();
    isBold = font.bold();
    isUnderlined = font.underline();
    color = pal_color.name();
    minute = time.minute();
    second = time.second();
}

void ProblemViewerObject::applyToDialogProblemUi(Ui::DialogProblem &ui)
{
    QTextBrowser *browser = ui.textBrowser;
    QFont font = browser->font();
    QPalette pal = browser->palette();
    QTime time(0, minute, second);

    if (!family.isEmpty()) {
        font.setFamily(family);
        QFont comboFont = ui.fontComboBox->font();
        comboFont.setFamily(family);
        ui.fontComboBox->setCurrentFont(comboFont);
    }
    if (size > 0) {
        font.setPixelSize(size);
        ui.spinTextSize->setValue(size);
    }
    font.setItalic(isItalic);
    if (isItalic) ui.bTextItalic->setChecked(true);
    font.setBold(isBold);
    if (isBold) ui.bTextBold->setChecked(true);
    font.setUnderline(isUnderlined);
    if (isUnderlined) ui.bTextUnderline->setChecked(true);
    browser->setFont(font);

    if (!color.isEmpty()) pal.setColor(QPalette::Text, QColor(color));
    browser->setPalette(pal);
    if (QTime(0, 0, 0) != time) ui.timeEditLimit->setTime(time);
}

QJsonObject ProblemViewerObject::toJson()
{
    QJsonObject obj;
    obj["family"] = family;
    obj["size"] = size;
    obj["isItalic"] = isItalic;
    obj["isBold"] = isBold;
    obj["isUnderlined"] = isUnderlined;
    obj["color"] = color;
    obj["minute"] = minute;
    obj["second"] = second;
    return obj;
}
