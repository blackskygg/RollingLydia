#include "configuration.h"
#include "ui_viewproblem.h"
#include <QTextBrowser>
#include <QFile>
#include <QTime>
#include <QTimeEdit>
#include <QFontComboBox>
#include <QPalette>

Configuration::Configuration() :
    rollingSpeed(1),
    mode(0),
    isValid_(false)
{
}

Configuration::Configuration(QString &filename) : isValid_(false)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) return;

    //QJsonDocument jsonDoc = QJsonDocument::fromJson();

    isValid_ = true;
}

void WidgetItemObject::fromJson(QJsonObject &obj)
{
    text = obj["text"].toString();
    data = obj["data"].toString();
}

void WidgetItemObject::fromQListWidgetItem(QListWidgetItem &item)
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

ProblemViewerObject::ProblemViewerObject():
    size(17),
    isItalic(false),
    isBold(false),
    isUnderlined(false)
{
}

void ProblemViewerObject::fromJson(QJsonObject &obj)
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

void ProblemViewerObject::fromDialogProblemUi(Ui::DialogProblem &ui)
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
        ui.fontComboBox->setFont(comboFont);
    }
    if (0 != size) {
        font.setPixelSize(size);
        ui.spinTextSize->setValue(size);
    }
    font.setItalic(isItalic);
    if (isItalic) ui.bTextItalic->setChecked(true);
    font.setBold(isBold);
    if (isItalic) ui.bTextBold->setChecked(true);
    font.setUnderline(isUnderlined);
    if (isItalic) ui.bTextUnderline->setChecked(true);
    browser->setFont(font);

    if (!color.isEmpty()) pal.setColor(QPalette::Text, QColor(color));
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
