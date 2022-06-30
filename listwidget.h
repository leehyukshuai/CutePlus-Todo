#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>
#include <QMenu>
#include <QMouseEvent>
#include <QMimeData>
#include <QDataStream>
#include <QByteArray>
#include "listitem.h"

class ListWidget : public QListWidget
{
    Q_OBJECT

private:
    QMenu *menu;
    QPoint menuPosition;

signals:
    void deleteListItem(ListItem *listItem);
    void modifyListItem(ListItem *listItem);

public:
    ListWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *e);
    Qt::DropActions supportedDropActions() const;
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QList<QListWidgetItem *> items) const;

private slots:
    void onDeleteActionTriggered();
    void onModifyActionTriggered();

};

#endif // LISTWIDGET_H
