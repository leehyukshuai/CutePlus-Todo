#ifndef TASKDETAILWIDGET_H
#define TASKDETAILWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "taskitem.h"

class TaskDetailWidget : public QWidget
{
    Q_OBJECT

private:
    TaskItem *taskItem;
    QLineEdit *nameInput;
    QLineEdit *detailInput;

public:
    explicit TaskDetailWidget(QWidget *parent = nullptr);
    void setTaskItemSource(TaskItem *item);

signals:
    void setTaskItemSignal(TaskItem *item, QString name, QString detail);
    void callWarningTip(QString);
    void finish();

public slots:
    void onYesBtnClicked();
    void onCancelBtnClicked();

};

#endif // TASKDETAILWIDGET_H
