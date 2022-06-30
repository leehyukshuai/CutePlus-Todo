#ifndef TASKPART_H
#define TASKPART_H

#include <QWidget>
#include <QTreeWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QMenu>
#include "taskitemwidget.h"
#include "treewidget.h"
#include "listitem.h"

class TaskPart : public QWidget
{
    Q_OBJECT

private:
    ListItem *listItem;
    TreeWidget *treeWidget;
    QLineEdit *taskInput;
    QPushButton *addTaskBtn;
    QTreeWidgetItem *todo;
    QTreeWidgetItem *done;
    QPoint menuPosition;

signals:
    void callWarningTip(QString);
    void callTaskItemDetailWidget(TaskItem *item);

public:
    explicit TaskPart(QWidget *parent = nullptr);

private:
    void pushFrontTaskItem(TaskItem *item);
    void pushBackTaskItem(TaskItem *item);
    void removeTaskItem(QTreeWidgetItem *item);
    void setTaskItemWidget(TaskItem *item);

public slots:
    void flipTaskItem(TaskItem *item);
    void setListItem(ListItem *_listItem);
    void setThemeColor();
    void updateTasks();
    void insertTaskItem(int index, TaskItem *item);
    void setTaskItem(TaskItem *item, QString name, QString detail);
    void deleteTaskItem(TaskItem *item);
    void forwardTaskItem(TaskItem *item);
    void backwardTaskItem(TaskItem *item);
    void toTopTaskItem(TaskItem *item);
    void toBottomTaskItem(TaskItem *item);
    void clearItems();
    void commit();


private slots:
    void onAddTaskBtnClicked();
    void onDelTaskActionTriggered();
    void onCallTaskItemDetailWidget(TaskItem *item);
};

#endif // TASKPART_H
