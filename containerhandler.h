#ifndef CONTAINERHANDLER_H
#define CONTAINERHANDLER_H

#include <QWidget>
#include <QLabel>
#include <QListView>
#include <QJsonDocument>
#include <QPushButton>

class ContainerHandler : public QWidget
{
    Q_OBJECT
private:
    QListView* containerview;
    QLabel *desc,*head,*properties,*price;
    QPushButton *elimina,*modifica;

    void updateRightColumn(const QVariant&);
public:
    ContainerHandler(QWidget *parent = nullptr);
    QByteArray getJsonParsed()const;
    void loadInModel(const QJsonDocument&);
signals:

public slots:
    void changeInfos(const QModelIndex &,const QModelIndex &);
    void save();
    void load();
    void eraseCurrent();
    void modify();
    void insert();
};

#endif // CONTAINERHANDLER_H
