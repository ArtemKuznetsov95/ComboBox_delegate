#include "DelegateComboBox.h"
#include <QApplication>
#include <iostream>
#include <QDebug>

DelegateComboBox::DelegateComboBox(QStandardItemModel *model, QObject *parent) :
    QStyledItemDelegate(parent), m_model{model}
{
}

void DelegateComboBox::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    bool value = index.model()->data(index, Qt::CheckStateRole).toBool();
    auto text  = index.model()->data(index, Qt::DisplayRole).toString();

    QFont nameFont(option.font);
    const QFontMetrics nameFM(nameFont);

    //-----------------Рисование текста c checkbox-----------------
    {
    QStringList words = text.split(' ');
    QString str;
    QString textStr;

    for(auto word : words) {

        int nameWidth = nameFM.horizontalAdvance(str + " " + word);
        if(nameWidth < (option.rect.width() * 0.6)) {
            str += " " + word;
            textStr += " " + word;
        }
        else {
            str = word;
            textStr += "\n" + word;
        }
    }

    const QStyle *style = QApplication::style();
    QStyleOptionButton opt;
    opt.state |= value ? QStyle::State_On : QStyle::State_Off;
    opt.state |= QStyle::State_Enabled;
    opt.text = textStr;
    opt.rect = option.rect;

    style->drawControl(QStyle::CE_CheckBox, &opt, painter);
    }

    //-----------------Рисование шкалы цвета слоя-----------------
    qreal x1 = option.rect.width() * 2/3;
    qreal y1 = option.rect.y() + option.rect.height()/2;
    qreal width1 = option.rect.width() - 20;
    qreal height1 = 12;
    qreal corner_radius = 7.0;

    QLinearGradient lineGragient;
    lineGragient.setColorAt(0.0, Qt::green);
    lineGragient.setColorAt(1.0, Qt::red);
    lineGragient.setStart(x1, y1);
    lineGragient.setFinalStop(option.rect.width(), y1 + height1);

    QPainterPath pathRect;
    pathRect.moveTo(x1, y1);
    pathRect.arcTo(x1, y1 + (height1  - 2 * corner_radius), 2 * corner_radius, 2 * corner_radius, 180.0, 90.0);
    pathRect.lineTo((width1 - 2 * corner_radius), y1 + (height1));
    pathRect.arcTo((width1 - 2 * corner_radius), y1 + (height1  - 2 * corner_radius), 2 * corner_radius, 2 * corner_radius, 270.0, 90.0);
    pathRect.arcTo(width1 - 2 * corner_radius, y1 - (height1 / 2 )  , 2 * corner_radius, 2 * corner_radius, 360.0, 90.0);
    pathRect.lineTo(x1 + corner_radius, y1 - (height1/2));
    pathRect.arcTo(x1, y1 - (height1/2), 2 * corner_radius, 2 * corner_radius, 90.0, 90.0);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setBrush(lineGragient);
    painter->drawPath(pathRect);
    painter->restore();
}

QSize DelegateComboBox::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize mySize = QStyledItemDelegate::sizeHint(option, index);

    QFont nameFont(option.font);
    nameFont.setWeight(QFont::Bold);
    const QFontMetrics nameFM(nameFont);
    int nameHeight = nameFM.height();

    auto text  = index.model()->data(index, Qt::DisplayRole).toString();
    QStringList words = text.split(' ');
    QString str;
    for(auto word : words) {
        int nameWidth = nameFM.horizontalAdvance(str + " " + word);
        if(nameWidth < (option.rect.width() * 0.6)) {
            str += " " + word;
        }
        else {
            str = word;
            mySize.setHeight(mySize.height() + nameHeight);
        }
    }

    return mySize;
}

