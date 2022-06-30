#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>
#include <QMouseEvent>
#include <QMenu>
#include <QMimeData>
#include <QDataStream>
#include <QByteArray>
#include "taskitem.h"


class TreeWidget : public QTreeWidget
{
    Q_OBJECT

private:
    QMenu *menu;
    QPoint doubleClickPosition;
    QPoint menuPosition;

public:
    explicit TreeWidget(QWidget *parent = nullptr);

signals:
    void callTaskItemDetailWidget(TaskItem *);
    void deleteTaskItem(TaskItem *);
    void forwardTaskItem(TaskItem *);
    void backwardTaskItem(TaskItem *);
    void toTopTaskItem(TaskItem *);
    void toBottomTaskItem(TaskItem *);

protected:
    void mouseDoubleClickEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    // drag and drop (deprecated)
//    Qt::DropActions supportedDropActions() const;
//    QStringList mimeTypes() const;
//    QMimeData *mimeData(const QList<QTreeWidgetItem *> items) const;
//    void dropEvent(QDropEvent *e);

private slots:
    void onDeleteActionTriggered();
    void onForwardActionTriggerrd();
    void onBackwardActionTriggerrd();
    void onToTopActionTriggerrd();
    void onToBottomActionTriggerrd();


};

#endif // TREEWIDGET_H
