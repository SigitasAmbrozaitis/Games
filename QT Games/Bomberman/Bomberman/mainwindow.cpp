#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ContinueButton_clicked()
{
    //TODO implement last session game loading
    //last game session stored in file
    //game->start()
}

void MainWindow::on_NewGameButton_clicked()
{
    //TODO implement start of new game
    //after every cleared level save to file current level
    //game->start()
}


void MainWindow::on_ExitButton_clicked()
{
    close();
}
