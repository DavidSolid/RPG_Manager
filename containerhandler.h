#ifndef CONTAINERHANDLER_H
#define CONTAINERHANDLER_H

#include <QWidget>
#include <QLabel>
#include <QListView>

class ContainerHandler : public QWidget
{
    Q_OBJECT
private:
    QListView* containerview;
    QLabel *desc,*head,*properties,*price;

    void updateRightColumn(const QVariant&);
public:
    ContainerHandler(QWidget *parent = nullptr);
    QByteArray getJsonParsed()const;
signals:

public slots:
    void changeInfos(const QModelIndex &,const QModelIndex &);
    void save();
};

#endif // CONTAINERHANDLER_H
