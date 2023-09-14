#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QComboBox>
#include <QStandardItemModel>

class MyComboBox : public QComboBox
{
public:
    MyComboBox(QWidget *parent = nullptr);

    void showPopup() override;

    void setModel(QStandardItemModel *model);

    QStandardItemModel *m_model;

};

#endif // MYCOMBOBOX_H
