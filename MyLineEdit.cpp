#include "MyLineEdit.h"

MyLineEdit::MyLineEdit(QComboBox *combo) :
    QLineEdit(nullptr),
    m_lineEdit(combo->lineEdit()),
    m_combo(combo)
{

}
bool MyLineEdit::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_lineEdit) {
        if(event->type() == QEvent::MouseButtonPress) {
            m_combo->showPopup();
        }
    }
    return QLineEdit::eventFilter(watched, event);
}

void MyLineEdit::mousePressEvent(QMouseEvent *event){
    (void)event;
}

void MyLineEdit::mouseReleaseEvent(QMouseEvent *event)
{
    (void)event;
    m_combo->showPopup();
}

void MyLineEdit::mouseMoveEvent(QMouseEvent *event){
    (void)event;
}

void MyLineEdit::mouseDoubleClickEvent(QMouseEvent *event){
    (void)event;
}
