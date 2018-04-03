#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ContinueButton_clicked();

    void on_NewGameButton_clicked();

    void on_ExitButton_clicked();

private:
    Ui::MainWindow *ui;

    //Game * game
    //inherit qgraphics view
    //is a window same size as mainwindow
    //handles all game logic
};

#endif // MAINWINDOW_H
