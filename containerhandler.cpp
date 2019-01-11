#include "containerhandler.h"
#include <QListView>
#include "containermodel.h"
#include <QVBoxLayout>
#include <QDataWidgetMapper>

ContainerHandler::ContainerHandler(QWidget *parent) : QWidget(parent),desc(new QLabel(this))
{
    //setup desc
    desc->setText("Nessun Oggetto Selezionato");
    QLabel* deschead=new QLabel(this);
    deschead->setText("Descrizione");
    deschead->setStyleSheet("font-weight: bold;");
    //layout
    QVBoxLayout* column=new QVBoxLayout;
    //view e modello
    QListView* containerview = new QListView(this);
    ContainerModel* model=new ContainerModel(this);
    containerview->setModel(model);
    connect(containerview->selectionModel(),&QItemSelectionModel::currentChanged,
            this,&ContainerHandler::changeInfos);
    //containerview->selectionModel()->setCurrentIndex(model->index(0), QItemSelectionModel::SelectCurrent);
    //setup layout
    column->addWidget(containerview);
    column->addWidget(deschead);
    column->addWidget(desc);
    setLayout(column);
}

void ContainerHandler::changeInfos(const QModelIndex & n,const QModelIndex &){
    desc->setText(n.data(ContainerModel::DescriptionRole).toString());
}
