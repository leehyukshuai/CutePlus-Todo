#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include "qnotify.h"
#include "listpart.h"
#include "taskpart.h"
#include "listdetailwidget.h"
#include "taskdetailwidget.h"

class Widget : public QWidget
{
    Q_OBJECT

private:
    ListPart *listPart;
    TaskPart *taskPart;
    ListDetailWidget *listDetailWidget;
    TaskDetailWidget *taskDetailWidget;
    QStackedWidget *stackedWidget;

    QNotify *notice;

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void closeEvent(QCloseEvent *);

private:
    void save();
    void read();

public slots:
    void switchToListDetailWidget(ListItem *);
    void switchToTaskPart();
    void switchToTaskItemDetailWidget(TaskItem *);
    void callWarningTip(QString string);


};

#endif // WIDGET_H
