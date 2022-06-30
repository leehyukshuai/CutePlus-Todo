#ifndef TASKITEMWIDGET_H
#define TASKITEMWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QHBoxLayout>
#include "taskitem.h"

class TaskItemWidget : public QWidget
{
    Q_OBJECT

private:
    TaskItem *taskItem;
    QCheckBox *checkBox;
    QLabel *nameLabel;
    QLabel *timeLabel;
    QHBoxLayout *layout;

signals:
    void flipSignal(TaskItem *);

public:
    TaskItemWidget(TaskItem *item);
    ~TaskItemWidget();

private slots:
    void emitFlipSignal();
};

#endif // TASKITEMWIDGET_H
