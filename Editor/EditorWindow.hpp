#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EditorWindow.h"

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditorWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::EditorWindowClass ui;
};
