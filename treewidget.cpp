#include "treewidget.h"
#include <QDebug>

TreeWidget::TreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    menu = new QMenu(this);
    QAction *deleteAction = new QAction(tr("Delete"));
    QAction *forwardAction = new QAction(tr("Forward"));
    QAction *backwardAction = new QAction(tr("BackWard"));
    QAction *toTopAction = new QAction(tr("To top"));
    QAction *toBottomAction = new QAction(tr("To Bottom"));

    deleteAction->setIcon(QIcon(":/icons/delete_c.png"));
    forwardAction->setIcon(QIcon(":/icons/up.png"));
    backwardAction->setIcon(QIcon(":/icons/down.png"));
    toTopAction->setIcon(QIcon(":/icons/top.png"));
    toBottomAction->setIcon(QIcon(":/icons/bottom.png"));

    menu->addAction(deleteAction);
    menu->addAction(forwardAction);
    menu->addAction(toTopAction);
    menu->addAction(backwardAction);
    menu->addAction(toBottomAction);
    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(onDeleteActionTriggered()));
    connect(forwardAction, SIGNAL(triggered(bool)), this, SLOT(onForwardActionTriggerrd()));
    connect(backwardAction, SIGNAL(triggered(bool)), this, SLOT(onBackwardActionTriggerrd()));
    connect(toTopAction, SIGNAL(triggered(bool)), this, SLOT(onToTopActionTriggerrd()));
    connect(toBottomAction, SIGNAL(triggered(bool)), this, SLOT(onToBottomActionTriggerrd()));
    this->setHeaderHidden(true);
    this->setAnimated(true);
    this->setVerticalScrollMode(QTreeWidget::ScrollPerPixel);
    this->setAlternatingRowColors(true);

//    this->setDefaultDropAction(Qt::MoveAction);
//    this->setAcceptDrops(true);
//    this->setDragEnabled(true);
}

void TreeWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        QTreeWidgetItem *item = itemAt(e->pos());
        if (item != nullptr && item != topLevelItem(0) && item != topLevelItem(1)) {
            doubleClickPosition = e->pos();
            emit callTaskItemDetailWidget(static_cast<TaskItem *>(itemAt(e->pos())));
        }
    }
    QTreeWidget::mouseDoubleClickEvent(e);
}

void TreeWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton) {
        QTreeWidgetItem *item = itemAt(e->pos());
        if (item != nullptr && item != topLevelItem(0) && item != topLevelItem(1)) {
            menuPosition = e->pos();
            menu->exec(e->globalPos());
        }
    }
    QTreeWidget::mousePressEvent(e);
}


void TreeWidget::onDeleteActionTriggered()
{
    TaskItem *item = static_cast<TaskItem *>(itemAt(menuPosition));
    emit deleteTaskItem(item);
}

void TreeWidget::onForwardActionTriggerrd()
{
    TaskItem *item = static_cast<TaskItem *>(itemAt(menuPosition));
    emit forwardTaskItem(item);
}

void TreeWidget::onBackwardActionTriggerrd()
{
    TaskItem *item = static_cast<TaskItem *>(itemAt(menuPosition));
    emit backwardTaskItem(item);
}

void TreeWidget::onToTopActionTriggerrd()
{
    TaskItem *item = static_cast<TaskItem *>(itemAt(menuPosition));
    emit toTopTaskItem(item);
}

void TreeWidget::onToBottomActionTriggerrd()
{
    TaskItem *item = static_cast<TaskItem *>(itemAt(menuPosition));
    emit toBottomTaskItem(item);
}

//Qt::DropActions TreeWidget::supportedDropActions() const
//{
//    return Qt::MoveAction;
//}

//QStringList TreeWidget::mimeTypes() const
//{
//    return QStringList() << "application/task.item";
//}

//QMimeData *TreeWidget::mimeData(const QList<QTreeWidgetItem *> items) const
//{
//    QMimeData *mimeData = new QMimeData;
//    QByteArray encodedData;
//    QDataStream stream(&encodedData, QIODevice::WriteOnly);
//    TaskItem *item = static_cast<TaskItem *>(items[0]);
//    stream << *item;
//    mimeData->setData("application/task.item", encodedData);
//    return mimeData;
//}

//void TreeWidget::dropEvent(QDropEvent *e)
//{
//    if (e->mimeData()->hasFormat("application/task.item")) {
//        QByteArray encodedData = e->mimeData()->data("application/task.item");
//        QDataStream stream(&encodedData, QIODevice::ReadOnly);
//        TaskItem *item = new TaskItem;
//        stream >> *item;
//        QTreeWidgetItem *target = itemAt(e->pos());
//        if (target != nullptr) {
//            if (target == topLevelItem(0)) {
//                if (item->State() == false) {
//                    emit insertItem(0, item);
//                    e->acceptProposedAction();
//                }
//            } else if (target == topLevelItem(1)){
//                if (item->State() == true) {
//                    emit insertItem(0, item);
//                    e->acceptProposedAction();
//                }
//            } else {
//                TaskItem *pItem = static_cast<TaskItem *>(target);
//                if (item->State() == false) {
//                    if (pItem->State() == false) {
//                        emit insertItem(topLevelItem(0)->indexOfChild(pItem), item);
//                        e->accept();
//                        e->acceptProposedAction();
//                    }
//                } else {
//                    if (pItem->State() == true) {
//                        emit insertItem(topLevelItem(1)->indexOfChild(pItem), item);
//                        e->acceptProposedAction();
//                    }
//                }
//            }
//        }
//    }
//}
