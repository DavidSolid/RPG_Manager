#include "containerhandler.h"
#include "containermodel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDataWidgetMapper>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>

#include <QMessageBox>//debug

ContainerHandler::ContainerHandler(QWidget *parent) : QWidget(parent),containerview(new QListView(this)),desc(new QLabel(this)),head(new QLabel(this)),properties(new QLabel(this)),price(new QLabel(this))
{
    //setup desc
    desc->setText("Nessun Oggetto Selezionato");
    QLabel* deschead=new QLabel(this);
    deschead->setText("Descrizione");
    deschead->setStyleSheet("font-weight: bold;");
    //setup head
    head->setText("Nessuna Informazione Disponibile");
    head->setStyleSheet("font-weight: bold;");
    head->setAlignment(Qt::AlignCenter);
    head->setWordWrap(true);
    head->setMargin(25);
    //setup properties
    properties->setAlignment(Qt::AlignCenter);
    //setup price
    price->setAlignment(Qt::AlignCenter);
    //layout
    QVBoxLayout* column1=new QVBoxLayout;
    QVBoxLayout* column2=new QVBoxLayout;
    QHBoxLayout* layout=new QHBoxLayout;
    //view e modello
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

void ContainerHandler::save(){
    QMessageBox result;
    QString filename=QFileDialog::getSaveFileName(this,"Scegli file su cui salvare","","Json file (*.json)");
    if(filename.isEmpty() || filename.isNull()){
        result.setText("Impossibile salvare. Nessun File selezionato");
    }
    else{
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly)){
            result.setText("Impossibile aprire il file selezionato");
        }
        else{
            if(file.write(getJsonParsed())!=-1){
                result.setText("Salvataggio avvenuto con successo in "+filename);
            }
            else result.setText("Si è verificato un errore durante il salvataggio");
        }
    }
    result.exec();
}

void ContainerHandler::load(){
    QMessageBox result;
    QString filename=QFileDialog::getOpenFileName(this,"Scegli file da cui caricare","","Json file (*.json)");
    if(filename.isEmpty() || filename.isNull()){
        result.setText("Impossibile salvare. Nessun File selezionato");
    }
    else{
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly)){
            result.setText("Impossibile aprire il file selezionato");
        }
        else{
            QByteArray rawdata=file.readAll();
            if(rawdata.isEmpty()){
                result.setText("File Vuoto");
            }
            else{
                QJsonDocument doc=QJsonDocument::fromJson(rawdata);
                if(doc.isNull()){
                    result.setText("Errore di deserializzazione. File JSON non valido");
                }
                else {
                    loadInModel(doc);
                    result.setText("File caricato correttamente");
                }
            }
        }
    }
    result.exec();
}

QByteArray ContainerHandler::getJsonParsed()const{
    int nentry=containerview->model()->rowCount();
    QJsonArray array;
    for(int i=0;i<nentry;i++){
        array.append(QJsonObject::fromVariantMap(containerview->model()->index(i,0).data(ContainerModel::JsonRole).toMap()));
    }
    return QJsonDocument(array).toJson();
}

void ContainerHandler::loadInModel(const QJsonDocument& doc){
    QJsonArray array=doc.array();
    QAbstractItemModel* model=containerview->model();
    //model->removeRows(0,model->rowCount()); //qui è il problema
    model->insertRows(0,array.size());
    for(int i=0;i<array.size();i++){
        model->setData(model->index(i,0),array[i].toVariant());
    }
}
