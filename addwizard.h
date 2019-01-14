#ifndef ADDWIZARD_H
#define ADDWIZARD_H

#include <QWizard>

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
    AddWizard(QWidget* parent=nullptr);
    int nextId() const override;
};

class InitialPage: public QWizardPage{
public:
    InitialPage(QWidget* =nullptr);
};

class ArmorPage: public QWizardPage{
public:
    ArmorPage(QWidget* =nullptr);
};

class WeaponPage: public QWizardPage{
public:
    WeaponPage(QWidget* =nullptr);
};

class ConsumablePage: public QWizardPage{
public:
    ConsumablePage(QWidget* =nullptr);
};
#endif // ADDWIZARD_H
