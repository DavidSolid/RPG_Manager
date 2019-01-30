#include "containerhandler.h"
#include "containermodel.h"
#include "searchproxy.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDataWidgetMapper>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include "addwizard.h"

#include <QLineEdit>
#include <QCheckBox>

#include <QMessageBox>//debug

ContainerHandler::ContainerHandler(QWidget *parent) : QWidget(parent),containerview(new QListView(this)),desc(new QLabel(this)),head(new QLabel(this)),properties(new QLabel(this)),price(new QLabel(this)),elimina(new QPushButton("Elimina",this)),modifica(new QPushButton("Modifica",this))
{
    //setup search
    QLineEdit* bar=new QLineEdit;
    QCheckBox* armi=new QCheckBox("Armi");
    QCheckBox* armor=new QCheckBox("Armature");
    QCheckBox* cons=new QCheckBox("Consumabili");
    armi->setChecked(true);
    armor->setChecked(true);
    cons->setChecked(true);
    armi->setLayoutDirection(Qt::RightToLeft);
    armor->setLayoutDirection(Qt::RightToLeft);
    cons->setLayoutDirection(Qt::RightToLeft);
    //setup desc
    desc->setText("Nessun Oggetto Selezionato");
    desc->setWordWrap(true);
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
    //buttons
    connect(elimina,&QPushButton::clicked,this,&ContainerHandler::eraseCurrent);
    elimina->setHidden(true);
    connect(modifica,&QPushButton::clicked,this,&ContainerHandler::modify);
    modifica->setHidden(true);
    //layout
    QHBoxLayout* search=new QHBoxLayout;
    QVBoxLayout* column1=new QVBoxLayout;
    QVBoxLayout* column2=new QVBoxLayout;
    QHBoxLayout* buttons=new QHBoxLayout;
    QHBoxLayout* hlayout=new QHBoxLayout;
    QVBoxLayout* layout=new QVBoxLayout;
    //view e modello
    ContainerModel* model=new ContainerModel(this);
    SearchProxy* proxy=new SearchProxy(bar,armi,armor,cons,this);
    proxy->setSourceModel(model);
    containerview->setModel(proxy);
    connect(containerview->selectionModel(),&QItemSelectionModel::currentChanged,
            this,&ContainerHandler::changeInfos);
    connect(proxy,&QAbstractItemModel::dataChanged,
            this,&ContainerHandler::changeInfos);

    connect(bar,&QLineEdit::textChanged,proxy,&QSortFilterProxyModel::invalidate);
    connect(bar,&QLineEdit::textChanged,this,&ContainerHandler::afterFilterInfo);
    connect(armi,&QCheckBox::toggled,proxy,&QSortFilterProxyModel::invalidate);
    connect(armi,&QCheckBox::toggled,this,&ContainerHandler::afterFilterInfo);
    connect(armor,&QCheckBox::toggled,proxy,&QSortFilterProxyModel::invalidate);
    connect(armor,&QCheckBox::toggled,this,&ContainerHandler::afterFilterInfo);
    connect(cons,&QCheckBox::toggled,proxy,&QSortFilterProxyModel::invalidate);
    connect(cons,&QCheckBox::toggled,this,&ContainerHandler::afterFilterInfo);
    //containerview->selectionModel()->setCurrentIndex(model->index(0), QItemSelectionModel::SelectCurrent);
    //setup layout
    search->addWidget(bar);
    search->addWidget(armi);
    search->addWidget(armor);
    search->addWidget(cons);
    column1->addWidget(containerview);
    column1->addWidget(deschead);
    column1->addWidget(desc);
    column2->addWidget(head);
    column2->addWidget(properties);
    column2->addWidget(price);
    buttons->addWidget(elimina);
    buttons->addWidget(modifica);
    column2->addLayout(buttons);
    hlayout->addLayout(column1);
    hlayout->addLayout(column2);
    layout->addLayout(search);
    layout->addLayout(hlayout);
    setLayout(layout);
}

void ContainerHandler::afterFilterInfo(){
    changeInfos(containerview->selectionModel()->currentIndex());
}

void ContainerHandler::changeInfos(const QModelIndex & n,const QModelIndex &){
    if(n.isValid()){
        desc->setText(n.data(ContainerModel::CompleteInfoRole).toMap()["description"].toString());
        updateRightColumn(n.data(ContainerModel::CompleteInfoRole));
    }
    else{
        desc->setText("Nessun Oggetto Selezionato");
        head->setText("Nessuna Informazione Disponibile");
        properties->clear();
        price->clear();
        elimina->setHidden(true);
        modifica->setHidden(true);
    }
}

QString ContainerHandler::translate(const QString & a){
    if(a=="wood"){
        return "legno";
    }
    if(a=="bronze"){
        return "bronzo";
    }
    if(a=="iron"){
        return "ferro";
    }
    if(a=="steel"){
        return "acciaio";
    }
    if(a=="mithril"){
        return a;
    }
    else return "materiale sconosciuto";
}

void ContainerHandler::updateRightColumn(const QVariant& info){
    const QVariantMap map=info.toMap();
    QString strhead=map["category"].toString();
    if(map["type"].isValid()){
        strhead+=" di "+translate(map["type"].toString());
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
    elimina->setHidden(false);
    modifica->setHidden(false);
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
                if(doc.isNull() || doc.isEmpty() || !doc.array().size()){
                    result.setText("Errore di deserializzazione. File JSON non valido o vuoto");
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

void ContainerHandler::eraseCurrent(){
    containerview->model()->removeRows(containerview->selectionModel()->currentIndex().row(),1);
    //if(!containerview->selectionModel()->currentIndex().isValid()){
        changeInfos(containerview->selectionModel()->currentIndex(),QModelIndex());
    //}
}

void ContainerHandler::modify(){
    QModelIndex current=containerview->selectionModel()->currentIndex();
    //creating map with all values
    AddWizard wizard(this,current.data(ContainerModel::CompleteInfoRole));
    int ret=wizard.exec();
    QMessageBox* mess=new QMessageBox(this);
    if(ret){
        containerview->model()->setData(current,wizard.getItemMap(),ContainerModel::SetRole);
        mess->setText("Operazione eseguita con successo");
    }
    else{
        mess->setText("Operazione annullata");
    }
    mess->exec();
}

void ContainerHandler::insert(){
    AddWizard wizard(this);
    int ret=wizard.exec();
    QMessageBox* mess=new QMessageBox(this);
    if(ret){
        QAbstractItemModel* model=dynamic_cast<QSortFilterProxyModel*>(containerview->model())->sourceModel();
        QModelIndex currentitem = containerview->selectionModel()->currentIndex();//map
        if(currentitem.isValid()){
            model->insertRows(currentitem.row(),1);
        }
        else{
            model->insertRows(model->rowCount(),1);
            currentitem=model->index(model->rowCount()-1,0);//map
        }
        model->setData(currentitem,wizard.getItemMap());
        //containerview->selectionModel()->setCurrentIndex(currentitem,QItemSelectionModel::ClearAndSelect/*Current*/);
        mess->setText("Operazione eseguita con successo");
    }
    else{
        mess->setText("Operazione annullata");
    }
    mess->exec();
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
    QAbstractItemModel* model=dynamic_cast<QSortFilterProxyModel*>(containerview->model())->sourceModel();
    model->removeRows(0,model->rowCount());
    model->insertRows(0,array.size());
    for(int i=0;i<array.size();i++){
        //implementare un controllo
        model->setData(model->index(i,0),array[i].toVariant());//map
    }
}
