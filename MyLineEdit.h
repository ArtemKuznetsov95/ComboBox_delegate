#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QObject>
#include <QObject>
#include <QLineEdit>
#include <QComboBox>
#include <QEvent>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QComboBox *combo);

    bool eventFilter(QObject *watched, QEvent *event);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    QLineEdit* m_lineEdit;
    QComboBox* m_combo;
};

#endif // MYLINEEDIT_H
