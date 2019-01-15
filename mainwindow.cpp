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
    QMenu* submenu2=menu->addMenu("Modifica");
    //QAction* modifica=submenu2->addAction("Modifica Oggetto...");
    QAction* aggiungi=submenu2->addAction("Aggiungi Oggetto...");
    setMenuBar(menu);
    //handler
    ContainerHandler* core=new ContainerHandler(this);
    setCentralWidget(core);
    //connections
    connect(save,SIGNAL(triggered()),core,SLOT(save()));
    connect(carica,SIGNAL(triggered()),core,SLOT(load()));
    connect(aggiungi,SIGNAL(triggered()),core,SLOT(insert()));
    //aspetto
    setWindowTitle("RPG Item Manager (a.k.a. Qontainer)");
    //setWindowIcon(QIcon(""));
}

MainWindow::~MainWindow()
{

}
