#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "framework/GlWindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public GlWindow
{
public:
    MainWindow();
    ~MainWindow();

    bool initializeObjects();
    void render();
    void keyPressEvent(QKeyEvent*);

private:
};

#endif // MAINWINDOW_H
