#include "listwidget.h"
#include <QDebug>

ListWidget::ListWidget(QWidget *parent) : QListWidget(parent)
{
    menu = new QMenu(this);
    QAction *modifyAction = new QAction(tr("Modify"));
    QAction *deleteAction = new QAction(tr("Delete"));
//    modifyAction->setIcon(QIcon(":/icon/icon/modify.png"));
//    deleteAction->setIcon(QIcon(":/icon/icon/delete.png"));
    menu->addAction(modifyAction);
    menu->addAction(deleteAction);
    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(onDeleteActionTriggered()));
    connect(modifyAction, SIGNAL(triggered(bool)), this, SLOT(onModifyActionTriggered()));
    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setDefaultDropAction(Qt::MoveAction);
}

QMimeData *ListWidget::mimeData(const QList<QListWidgetItem *> items) const
{
    QMimeData *mimeData = new QMimeData;
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    ListItem *item = static_cast<ListItem *>(items.at(0));
    stream << *item;
    mimeData->setData("application/list.item", encodedData);
    return mimeData;
}

void ListWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton) {
        if (itemAt(e->pos()) != nullptr) {
            menuPosition = e->pos();
            menu->exec(e->globalPos());
        }
    }
    QListWidget::mousePressEvent(e);
}

Qt::DropActions ListWidget::supportedDropActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}

QStringList ListWidget::mimeTypes() const
{
    return QStringList() << "application/list.item";
}

void ListWidget::onDeleteActionTriggered()
{
    ListItem *item = static_cast<ListItem *>(itemAt(menuPosition));
    emit deleteListItem(item);
}

void ListWidget::onModifyActionTriggered()
{
    ListItem *item = static_cast<ListItem *>(itemAt(menuPosition));
    emit modifyListItem(item);
}
