#include "containerhandler.h"
#include <QListView>
#include "containermodel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDataWidgetMapper>

ContainerHandler::ContainerHandler(QWidget *parent) : QWidget(parent),desc(new QLabel(this)),head(new QLabel(this)),properties(new QLabel(this)),price(new QLabel(this))
{
    //setup desc
    desc->setText("Nessun Oggetto Selezionato");
    QLabel* deschead=new QLabel(this);
    deschead->setText("Descrizione");
    deschead->setStyleSheet("font-weight: bold;");
    //setup head
    head->setText("Nessuna Informazione Disponibile");
    head->setStyleSheet("font-weight: bold;");
    head->setMargin(5);
    //setup properties
    properties->setAlignment(Qt::AlignCenter);
    //setup price
    price->setAlignment(Qt::AlignCenter);
    //layout
    QVBoxLayout* column1=new QVBoxLayout;
    QVBoxLayout* column2=new QVBoxLayout;
    QHBoxLayout* layout=new QHBoxLayout;
    //view e modello
    QListView* containerview = new QListView(this);
    ContainerModel* model=new ContainerModel(this);
    containerview->setModel(model);
    connect(containerview->selectionModel(),&QItemSelectionModel::currentChanged,
            this,&ContainerHandler::changeInfos);
    //containerview->selectionModel()->setCurrentIndex(model->index(0), QItemSelectionModel::SelectCurrent);
    //setup layout
    column1->addWidget(containerview);
    column1->addWidget(deschead);
    column1->addWidget(desc);
    column2->addWidget(head);
    column2->addWidget(properties);
    column2->addWidget(price);
    layout->addLayout(column1);
    layout->addLayout(column2);
    setLayout(layout);
}

void ContainerHandler::changeInfos(const QModelIndex & n,const QModelIndex &){
    if(n.isValid()){
        desc->setText(n.data(ContainerModel::DescriptionRole).toString());
        updateRightColumn(n.data(ContainerModel::CompleteInfoRole));
    }
    else{
        desc->setText("Nessun Oggetto Selezionato");
        head->setText("Nessuna Informazione Disponibile");
        properties->clear();
        price->clear();
    }
}

void ContainerHandler::updateRightColumn(const QVariant& info){
    const QVariantMap map=info.toMap();
    QString strhead=map["category"].toString();
    if(map["type"].isValid()){
        strhead+=" di "+map["type"].toString();
    }
    if(map["legendary"].isValid()){
        strhead+=" ";
        strhead+=map["legendary"].toBool()?"leggendaria":"comune";
    }
    if(map["onehanded"].isValid()){
        strhead+=" ";
        strhead+=map["onehanded"].toBool()?"a una mano":"a due mani";
    }
    if(map["positive"].isValid()){
        strhead+=" con effetto ";
        strhead+=map["positive"].toBool()?"positivo":"negativo";
    }
    head->setText(strhead);
    QString strpro;
    if(map["damage"].isValid()){
        strpro+="Danno: "+map["damage"].toString()+"\n";
    }
    if(map["defence"].isValid()){
        strpro+="Difesa: "+map["defence"].toString()+"\n";
    }
    if(map["level"].isValid()){
        strpro+="Livello: "+map["level"].toString()+"\n";
    }
    properties->setText(strpro);
    price->setText("Prezzo: "+map["price"].toString());
}
