#include "taskpart.h"
#include <QDebug>

TaskPart::TaskPart(QWidget *parent) : QWidget(parent)
{
    treeWidget = new TreeWidget;
    connect(treeWidget, SIGNAL(callTaskItemDetailWidget(TaskItem*)), this, SLOT(onCallTaskItemDetailWidget(TaskItem*)));
    connect(treeWidget, SIGNAL(deleteTaskItem(TaskItem*)), this, SLOT(deleteTaskItem(TaskItem*)));
    connect(treeWidget, SIGNAL(forwardTaskItem(TaskItem*)), this, SLOT(forwardTaskItem(TaskItem*)));
    connect(treeWidget, SIGNAL(backwardTaskItem(TaskItem*)), this, SLOT(backwardTaskItem(TaskItem*)));
    connect(treeWidget, SIGNAL(toTopTaskItem(TaskItem*)), this, SLOT(toTopTaskItem(TaskItem*)));
    connect(treeWidget, SIGNAL(toBottomTaskItem(TaskItem*)), this, SLOT(toBottomTaskItem(TaskItem*)));

    todo = new QTreeWidgetItem(treeWidget, QStringList() << tr("Todo"));
    done = new QTreeWidgetItem(treeWidget, QStringList() << tr("Done"));

    taskInput = new QLineEdit;
    connect(taskInput, SIGNAL(returnPressed()), SLOT(onAddTaskBtnClicked()));
    taskInput->setPlaceholderText(tr("Please enter task name there"));
    addTaskBtn = new QPushButton(tr("Add Task"));
    connect(addTaskBtn, SIGNAL(clicked(bool)), this, SLOT(onAddTaskBtnClicked()));

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addSpacing(30);
    bottomLayout->addWidget(taskInput);
    bottomLayout->addSpacing(30);
    bottomLayout->addWidget(addTaskBtn);
    bottomLayout->addSpacing(30);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(treeWidget);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(bottomLayout);
    mainLayout->addSpacing(20);
}

void TaskPart::pushFrontTaskItem(TaskItem *item)
{
    if (item->State() == false) {
        todo->insertChild(0, item);
    } else {
        done->insertChild(0, item);
    }
    setTaskItemWidget(item);
}

void TaskPart::pushBackTaskItem(TaskItem *item)
{
    if (item->State() == false) {
        todo->addChild(item);
    } else {
        done->addChild(item);
    }
    setTaskItemWidget(item);
}

void TaskPart::removeTaskItem(QTreeWidgetItem *item)
{
    delete static_cast<TaskItemWidget *>(treeWidget->itemWidget(item, 0));
    treeWidget->removeItemWidget(item, 0);
    if (static_cast<TaskItem *>(item)->State() == false) {
        todo->removeChild(item);
    } else {
        done->removeChild(item);
    }
}

void TaskPart::deleteTaskItem(TaskItem *item)
{
    removeTaskItem(item);
    delete item;
}

void TaskPart::flipTaskItem(TaskItem *item)
{
    TaskItem *copy = new TaskItem;
    copy->setName(item->Name());
    copy->setState(!item->State());
    copy->setDetail(item->Detail());
    copy->setTime(item->Time());
    pushFrontTaskItem(copy);
    deleteTaskItem(item);
}

void TaskPart::setTaskItemWidget(TaskItem *item)
{
    TaskItemWidget *itemWidget = new TaskItemWidget(item);
    treeWidget->setItemWidget(item, 0, itemWidget);
    connect(itemWidget, SIGNAL(flipSignal(TaskItem*)), this, SLOT(flipTaskItem(TaskItem*)));
}

void TaskPart::setListItem(ListItem *_listItem)
{
    commit();
    listItem = _listItem;
    updateTasks();
    setThemeColor();
    treeWidget->expandItem(todo);
    treeWidget->collapseItem(done);
}

void TaskPart::setThemeColor()
{
    if (listItem != nullptr) {
        QString str = QString().sprintf("%2d, %2d, %2d", listItem->Color().red(), listItem->Color().green(), listItem->Color().blue());
        setStyleSheet(QString("QTreeWidget::item:hover {background-color:rgba(%1, 10) ;padding: 10px;border-bottom: 3px solid rgb(%2);}").arg(str).arg(str) +
                      QString("QTreeWidget{font: 25 9pt \"Microsoft YaHei\";border: 15px solid rgba(%1, 20);border-radius: 10px;}").arg(str));
    }
}

void TaskPart::updateTasks()
{
    if (listItem != nullptr) {
        clearItems();
        foreach (TaskItem *item, listItem->tasks) {
            pushBackTaskItem(item);
        }
    }
}

void TaskPart::forwardTaskItem(TaskItem *item)
{
    int index;
    if (item->State() == false) {
        index = todo->indexOfChild(item);
        if (index > 0) --index;
    } else {
        index = done->indexOfChild(item);
        if (index > 0) --index;
    }
    removeTaskItem(item);
    insertTaskItem(index, item);
}

void TaskPart::backwardTaskItem(TaskItem *item)
{
    int index;
    if (item->State() == false) {
        index = todo->indexOfChild(item);
        if (index < todo->childCount() - 1) ++index;
    } else {
        index = done->indexOfChild(item);
        if (index < done->childCount() - 1) ++index;
    }
    removeTaskItem(item);
    insertTaskItem(index, item);
}

void TaskPart::toTopTaskItem(TaskItem *item)
{
    removeTaskItem(item);
    insertTaskItem(0, item);
}

void TaskPart::toBottomTaskItem(TaskItem *item)
{
    int index;
    if (item->State() == false) {
        index = todo->childCount() - 1;
    } else {
        index = done->childCount() - 1;
    }
    removeTaskItem(item);
    insertTaskItem(index, item);
}

void TaskPart::insertTaskItem(int index, TaskItem *item)
{
    if (item->State() == false) {
        todo->insertChild(index, item);
    } else {
        done->insertChild(index, item);
    }
    setTaskItemWidget(item);
}

void TaskPart::setTaskItem(TaskItem *item, QString name, QString detail)
{
    TaskItemWidget *itemWidget = static_cast<TaskItemWidget *>(treeWidget->itemWidget(item, 0));
    treeWidget->removeItemWidget(item, 0);
    delete itemWidget;
    item->setName(name);
    item->setDetail(detail);
    setTaskItemWidget(item);
}

void TaskPart::clearItems()
{
    while (todo->childCount() > 0) {
        removeTaskItem(todo->child(0));
    }
    while (done->childCount() > 0) {
        removeTaskItem(done->child(0));
    }
}

void TaskPart::commit()
{
    treeWidget->reset();
    if (listItem != nullptr) {
        listItem->tasks.clear();
        for (int i = 0; i < todo->childCount(); ++i) {
            listItem->tasks.append(static_cast<TaskItem *>(todo->child(i)));
        }
        for (int i = 0; i < done->childCount(); ++i) {
            listItem->tasks.append(static_cast<TaskItem *>(done->child(i)));
        }
    }
}

void TaskPart::onAddTaskBtnClicked()
{
    if (taskInput->text().isEmpty()) {
        emit callWarningTip(tr("Task name is blank."));
        return;
    }
    TaskItem *item = new TaskItem;
    item->setName(taskInput->text());
    item->setState(false);
    item->setTime(QDateTime::currentDateTime());
    pushFrontTaskItem(item);
    if (todo->isExpanded() == false) {
        todo->setExpanded(true);
    }
    taskInput->clear();
}

void TaskPart::onDelTaskActionTriggered()
{
    deleteTaskItem(static_cast<TaskItem *>(treeWidget->itemAt(menuPosition)));
}

void TaskPart::onCallTaskItemDetailWidget(TaskItem *item)
{
    emit callTaskItemDetailWidget(item);
}
