#ifndef LISTPART_H
#define LISTPART_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QMenu>
#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QMouseEvent>
#include "listwidget.h"
#include "listitem.h"

class ListPart : public QWidget
{
    Q_OBJECT

private:
    ListWidget *listWidget;
    QPushButton *addListBtn;

signals:
    void currentListItemChanged(ListItem *listItem);
    void callWarningTip(QString);
    void callListDetailWidget(ListItem *listItem);

public:
    ListPart(QWidget *parent = nullptr);
    void setIndex(int index);

public slots:
    void save();
    void read();
    void addListItem(ListItem *item);
    void addListItem(ListItem *item, QString name, QColor color, QIcon icon);
    void modifyListItem(ListItem *item, QString name, QColor color, QIcon icon);

private slots:
    void onAddListBtnClicked();
    void onDeleleActionTriggered(ListItem* listItem);
    void onModifyActionTriggered(ListItem* listItem);
    void emitCurrentListItemChanged(QListWidgetItem *listItem);


};

#endif // LISTPART_H
