#include "mainwindow.h"
#include "containerhandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ContainerHandler* core=new ContainerHandler(this);
    setCentralWidget(core);
}

MainWindow::~MainWindow()
{

}
