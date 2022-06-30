#ifndef LISTITEM_H
#define LISTITEM_H

#include <QListWidgetItem>
#include <QDataStream>
#include "taskitem.h"

class ListItem : public QObject, public QListWidgetItem
{
public:
    ListItem();
    ~ListItem();
    QColor Color();
    void setColor(QColor c);
    friend QDataStream &operator<<(QDataStream &stream, const ListItem &listItem);
    friend QDataStream &operator>>(QDataStream &stream, ListItem &listItem);

public:
    QList<TaskItem *> tasks;

private:
    QColor color;
};

#endif // LISTITEM_H
