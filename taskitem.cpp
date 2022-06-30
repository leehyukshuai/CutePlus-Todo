#include "taskitem.h"

TaskItem::TaskItem()
{
}

TaskItem::~TaskItem()
{
}

void TaskItem::flipState()
{
    state = !state;
}

bool TaskItem::State() const
{
    return state;
}

QString TaskItem::Name() const
{
    return name;
}

QString TaskItem::Detail() const
{
    return detail;
}

QDateTime TaskItem::Time() const
{
    return time;
}

void TaskItem::setState(bool s)
{
    state = s;
}

void TaskItem::setName(QString n)
{
    name = n;
}

void TaskItem::setDetail(QString d)
{
    detail = d;
}

void TaskItem::setTime(QDateTime t)
{
    time = t;
}

QDataStream &operator>>(QDataStream &stream, TaskItem &taskItem)
{
    stream >> taskItem.state >> taskItem.name >> taskItem.detail >> taskItem.time;
    return stream;
}

QDataStream &operator<<(QDataStream &stream, const TaskItem &taskItem)
{
    stream << taskItem.state << taskItem.name << taskItem.detail << taskItem.time;
    return stream;
}
