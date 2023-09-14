#include "MyComboBox.h"
#include <QDebug>
#include <QLineEdit>
#include <QKeyEvent>

MyComboBox::MyComboBox(QWidget *parent) : QComboBox(parent)
{
}

void MyComboBox::showPopup() {
    QComboBox::showPopup();
    if (m_model->columnCount() > 0 && m_model->rowCount() > 0) {
        auto index = m_model->index(0, 0);
        m_model->dataChanged(index, index);
    }

    QWidget *popup = this->findChild<QFrame*>();
    popup->move(popup->x(), popup->y()-this->height());
    QComboBox::showPopup();
}

void MyComboBox::setModel(QStandardItemModel *model) {
    m_model = model;
    QComboBox::setModel(model);
}
