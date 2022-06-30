#ifndef TASKITEM_H
#define TASKITEM_H

#include <QTreeWidgetItem>
#include <QDateTime>
#include <QDataStream>

class TaskItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT

public:
    TaskItem();
    ~TaskItem();
    void flipState();
    bool State() const;
    QString Name() const;
    QString Detail() const;
    QDateTime Time() const;
    void setState(bool s);
    void setName(QString n);
    void setDetail(QString d);
    void setTime(QDateTime t);
    friend QDataStream &operator<<(QDataStream &stream, const TaskItem &taskItem);
    friend QDataStream &operator>>(QDataStream &stream, TaskItem &taskItem);

private:
    bool state;
    QString name;
    QString detail;
    QDateTime time;
};

#endif // TASKITEM_H
