#include "mainwindow.h"
#include "containerhandler.h"
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createMenu();
    ContainerHandler* core=new ContainerHandler(this);
    setCentralWidget(core);
}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenu(){
    QMenuBar* menu=new QMenuBar;
    QMenu* submenu=menu->addMenu("File");
    QAction* carica=submenu->addAction("Carica...");
    QAction* save=submenu->addAction("Salva...");
    setMenuBar(menu);
}
