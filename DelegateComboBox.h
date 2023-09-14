#ifndef DELEGATECOMBOBOX_H
#define DELEGATECOMBOBOX_H

#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <QPainter>
#include <QComboBox>
#include <QPainterPath>

class DelegateComboBox : public QStyledItemDelegate
{
    Q_OBJECT
public:
    DelegateComboBox(QStandardItemModel *model, QObject *parent = 0);

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    // QAbstractItemDelegate interface
public:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QStandardItemModel *m_model;
};

#endif // DELEGATECOMBOBOX_H
