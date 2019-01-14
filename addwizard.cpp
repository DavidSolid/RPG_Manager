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

AddWizard::AddWizard(QWidget* parent):QWizard(parent)
{
    setWindowTitle("RPGItem Manager");
    setDefaultProperty("QTextEdit","plainText",SIGNAL(textChanged()));
    setDefaultProperty("QDoubleSpinBox","value",SIGNAL(valueChanged(double)));
    setPage(initialpage,new InitialPage(this));
    setPage(armorpage,new ArmorPage(this));
    setPage(weaponpage,new WeaponPage(this));
    setPage(consumablepage,new ConsumablePage(this));
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

InitialPage::InitialPage(QWidget *parent):QWizardPage(parent){
    QVBoxLayout* layout=new QVBoxLayout;
    setTitle("Creazione oggetto");
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

ArmorPage::ArmorPage(QWidget *parent):QWizardPage(parent){
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
}

WeaponPage::WeaponPage(QWidget *parent):QWizardPage(parent){
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

ConsumablePage::ConsumablePage(QWidget *parent):QWizardPage(parent){
    QVBoxLayout* layout=new QVBoxLayout;
    setTitle("Consumabile");
    setSubTitle("Scegli costo di base e se l'effetto è benefico o malevolo");
    QLabel* lcosto=new QLabel("Costo Base");
    QSpinBox* cost=new QSpinBox;
    lcosto->setBuddy(cost);
    cost->setRange(0,10000);
    QCheckBox* positive=new QCheckBox("Effetto Positivo");
    positive->setLayoutDirection(Qt::RightToLeft);
    layout->addWidget(lcosto);
    layout->addWidget(cost);
    layout->addWidget(positive);
    setLayout(layout);
    registerField("cost",cost);
    registerField("positive",positive);

}
