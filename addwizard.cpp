#include "addwizard.h"
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QButtonGroup>
#include <QTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QVBoxLayout>

AddWizard::AddWizard(QWidget* parent,const QVariant & old):QWizard(parent)
{
    setWindowTitle("RPGItem Manager");
    setDefaultProperty("QTextEdit","plainText",SIGNAL(textChanged()));
    setDefaultProperty("QDoubleSpinBox","value",SIGNAL(valueChanged(double)));
    setPage(initialpage,new InitialPage(this,old));
    setPage(armorpage,new ArmorPage(this,old));
    setPage(weaponpage,new WeaponPage(this,old));
    setPage(consumablepage,new ConsumablePage(this,old));
}

int AddWizard::nextId() const{
    switch(currentId()){
    case initialpage:
        if(field("weapon").toBool()){
            return weaponpage;
        }
        if(field("armor").toBool()){
            return armorpage;
        }
        return consumablepage;
    case armorpage:
    case weaponpage:
    case consumablepage:
    default:
        return -1;
    }
}

QVariant AddWizard::getItemMap() const{
    QVariantMap out;
    out.insert("name",field("name"));
    out.insert("description",field("description"));
    if(field("weapon").toBool()){
        out.insert("category","weapon");
        out.insert("level",field("wlevel"));
        out.insert("legendary",field("wlegendary"));
        out.insert("onehanded",field("onehanded"));
        out.insert("b_damage",field("damage"));
    }
    else if(field("armor").toBool()){
        out.insert("category","armor");
        out.insert("type",field("type"));
        out.insert("level",field("alevel"));
        out.insert("legendary",field("alegendary"));
    }
    else{
        out.insert("category","consumable");
        out.insert("b_cost",field("cost"));
        out.insert("positive",field("positive"));
    }
    return out;
}

InitialPage::InitialPage(QWidget *parent,const QVariant& def):QWizardPage(parent){
    QVBoxLayout* layout=new QVBoxLayout;
    setTitle("Creazione oggetto"); //cambiare in caso di def valido
    setSubTitle("Scegli nome, descrizione e tipo di oggetto");
    QLabel* lname=new QLabel("Nome");
    QLineEdit* name=new QLineEdit(this);
    lname->setBuddy(name);
    QLabel* ldesc=new QLabel("Descrizione");
    QTextEdit* desc=new QTextEdit(this);
    ldesc->setBuddy(desc);
    QLabel* ltype=new QLabel("Tipo");
    QRadioButton* weapon=new QRadioButton("Arma");
    QRadioButton* armor=new QRadioButton("Armatura");
    QRadioButton* consumable=new QRadioButton("Consumabile");
    ltype->setBuddy(weapon);
    QButtonGroup* group=new QButtonGroup(this);
    group->addButton(weapon);
    group->addButton(armor);
    group->addButton(consumable);
    group->setExclusive(true);
    weapon->setChecked(true);
    //if default value set
    if(def.isValid()){
        //setting default values
        //hiding type selection
        ltype->setVisible(false);
        weapon->setVisible(false);
        armor->setVisible(false);
        consumable->setVisible(false);
    }
    //layout set
    layout->addWidget(lname);
    layout->addWidget(name);
    layout->addWidget(ldesc);
    layout->addWidget(desc);
    layout->addWidget(ltype);
    layout->addWidget(weapon);
    layout->addWidget(armor);
    layout->addWidget(consumable);
    setLayout(layout);
    //registerfields
    registerField("name*",name);
    registerField("description*",desc);
    registerField("weapon",weapon);
    registerField("armor",armor);
    registerField("consumable",consumable);
}

ArmorPage::ArmorPage(QWidget *parent,const QVariant& old):QWizardPage(parent){
    QVBoxLayout* layout=new QVBoxLayout;
    setTitle("Armatura");
    setSubTitle("Scegli tipo, livello e rarità");
    QLabel* ltype=new QLabel("Tipo");
    QComboBox* type=new QComboBox;
    type->addItem("Legno");
    type->addItem("Bronzo");
    type->addItem("Ferro");
    type->addItem("Acciaio");
    type->addItem("Mithril");
    ltype->setBuddy(type);
    QLabel* llevel=new QLabel("Livello");
    QSpinBox* level=new QSpinBox;
    level->setRange(1,100);
    llevel->setBuddy(level);
    QCheckBox* legendary=new QCheckBox("Leggendario");
    legendary->setLayoutDirection(Qt::RightToLeft);
    layout->addWidget(ltype);
    layout->addWidget(type);
    layout->addWidget(llevel);
    layout->addWidget(level);
    layout->addWidget(legendary);
    setLayout(layout);
    registerField("type",type);
    registerField("alevel",level);
    registerField("alegendary",legendary);
}

WeaponPage::WeaponPage(QWidget *parent,const QVariant& old):QWizardPage(parent){
    QVBoxLayout* layout=new QVBoxLayout;
    QHBoxLayout* sublayout=new QHBoxLayout;
    setTitle("Arma");
    setSubTitle("Scegli danno di base, livello, rarità e se è ad una o due mani");
    QLabel* ldamage=new QLabel("Danno di base");
    QDoubleSpinBox* damage=new QDoubleSpinBox;
    ldamage->setBuddy(damage);
    damage->setRange(1,200);
    damage->setSingleStep(0.5);
    QLabel* llevel=new QLabel("Livello");
    QSpinBox* level=new QSpinBox;
    level->setRange(1,100);
    llevel->setBuddy(level);
    QCheckBox* legendary=new QCheckBox("Leggendario");
    legendary->setLayoutDirection(Qt::RightToLeft);
    QCheckBox* onehand=new QCheckBox("A due Mani");
    onehand->setLayoutDirection(Qt::RightToLeft);
    sublayout->addWidget(legendary);
    sublayout->addWidget(onehand);
    layout->addWidget(ldamage);
    layout->addWidget(damage);
    layout->addWidget(llevel);
    layout->addWidget(level);
    layout->addLayout(sublayout);
    setLayout(layout);
    registerField("damage",damage);
    registerField("wlevel",level);
    registerField("wlegendary",legendary);
    registerField("onehanded",onehand);
}

ConsumablePage::ConsumablePage(QWidget *parent,const QVariant& old):QWizardPage(parent){
    QVBoxLayout* layout=new QVBoxLayout;
    setTitle("Consumabile");
    setSubTitle("Scegli costo di base e se l'effetto è benefico o malevolo");
    QLabel* lcosto=new QLabel("Costo Base");
    QDoubleSpinBox* cost=new QDoubleSpinBox;
    lcosto->setBuddy(cost);
    cost->setRange(0,10000);
    cost->setSingleStep(0.5);
    QCheckBox* positive=new QCheckBox("Effetto Positivo");
    positive->setLayoutDirection(Qt::RightToLeft);
    layout->addWidget(lcosto);
    layout->addWidget(cost);
    layout->addWidget(positive);
    setLayout(layout);
    registerField("cost",cost);
    registerField("positive",positive);

}
