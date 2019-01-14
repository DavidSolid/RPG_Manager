#include "mainwindow.h"
#include "containerhandler.h"
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //menù
    QMenuBar* menu=new QMenuBar;
    QMenu* submenu=menu->addMenu("File");
    QAction* carica=submenu->addAction("Carica...");
    QAction* save=submenu->addAction("Salva...");
    setMenuBar(menu);
    //handler
    ContainerHandler* core=new ContainerHandler(this);
    setCentralWidget(core);
    //connections
    connect(save,SIGNAL(triggered()),core,SLOT(save()));
    connect(carica,SIGNAL(triggered()),core,SLOT(load()));
}

MainWindow::~MainWindow()
{

}
