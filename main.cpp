#include <../SelectionLayersMap.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SelectionLayersMap w;
    w.show();
    return a.exec();
}
