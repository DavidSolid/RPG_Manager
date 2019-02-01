#ifndef CONTAINERHANDLER_H
#define CONTAINERHANDLER_H

#include <QWidget>
#include <QLabel>
#include <QListView>
#include <QJsonDocument>
#include <QPushButton>
#include <QTextEdit>

class ContainerHandler : public QWidget
{
    Q_OBJECT
private:
    QListView* containerview;
    QTextEdit* desc;
    QLabel *head,*properties,*price;
    QPushButton *elimina,*modifica;

    void updateRightColumn(const QVariant&);
    static QString translate(const QString &);
    static bool validateInputArray(const QJsonArray &);
public:
    ContainerHandler(QWidget *parent = nullptr);
    QByteArray getJsonParsed()const;
    bool loadInModel(const QJsonDocument&);
signals:

public slots:
    void afterFilterInfo();
    void changeInfos(const QModelIndex &,const QModelIndex & =QModelIndex());
    void save();
    void load();
    void eraseCurrent();
    void modify();
    void insert();
};

#endif // CONTAINERHANDLER_H
