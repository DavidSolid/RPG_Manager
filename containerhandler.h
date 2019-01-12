#ifndef CONTAINERHANDLER_H
#define CONTAINERHANDLER_H

#include <QWidget>
#include <QLabel>

class ContainerHandler : public QWidget
{
    Q_OBJECT
private:
    QLabel *desc,*head,*properties,*price;

    void updateRightColumn(const QVariant&);
public:
    ContainerHandler(QWidget *parent = nullptr);

signals:

public slots:
    void changeInfos(const QModelIndex &,const QModelIndex &);
};

#endif // CONTAINERHANDLER_H
