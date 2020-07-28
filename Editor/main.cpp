#include "Editor/EditorWindow.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EditorWindow w;
    w.show();
    return a.exec();
}
