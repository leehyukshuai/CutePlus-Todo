#include "listitem.h"
#include <QDebug>

ListItem::ListItem()
{
}

ListItem::~ListItem()
{
    for (int i = 0; i < tasks.count(); ++i) {
        delete tasks.at(i);
    }
}

QColor ListItem::Color()
{
    return color;
}

void ListItem::setColor(QColor c)
{
    color = c;
}

QDataStream &operator<<(QDataStream &stream, const ListItem &listItem)
{
    stream << listItem.text() << listItem.color << listItem.icon() << listItem.tasks.count();
    for (int i = 0; i < listItem.tasks.count(); ++i) {
        stream << *listItem.tasks.at(i);
    }
    return stream;
}

QDataStream &operator>>(QDataStream &stream, ListItem &listItem)
{
    QString name;
    QIcon icon;
    int cnt;
    stream >> name >> listItem.color >> icon >> cnt;
    listItem.setText(name);
    listItem.setIcon(icon);
    for (int i = 0; i < cnt; ++i) {
        TaskItem *taskItem = new TaskItem;
        stream >> *taskItem;
        listItem.tasks.append(taskItem);
    }
    return stream;
}
