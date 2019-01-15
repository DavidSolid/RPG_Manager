#ifndef ADDWIZARD_H
#define ADDWIZARD_H

#include <QWizard>
#include <QVariant>

class AddWizard : public QWizard
{
    Q_OBJECT

public:
    enum{
        initialpage, //forse private
        armorpage,
        weaponpage,
        consumablepage
    };
    AddWizard(QWidget* parent=nullptr,const QVariant& =QVariant());
    int nextId() const override;
    QVariant getItemMap() const;
};

class InitialPage: public QWizardPage{
public:
    InitialPage(QWidget* =nullptr,const QVariant& =QVariant());
};

class ArmorPage: public QWizardPage{
public:
    ArmorPage(QWidget* =nullptr,const QVariant& =QVariant());
};

class WeaponPage: public QWizardPage{
public:
    WeaponPage(QWidget* =nullptr,const QVariant& =QVariant());
};

class ConsumablePage: public QWizardPage{
public:
    ConsumablePage(QWidget* =nullptr,const QVariant& =QVariant());
};
#endif // ADDWIZARD_H
