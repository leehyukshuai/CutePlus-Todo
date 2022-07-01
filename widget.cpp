#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    listPart = new ListPart;

    taskPart = new TaskPart;
    listDetailWidget = new ListDetailWidget;
    connect(listDetailWidget, SIGNAL(callWarningTip(QString)), this, SLOT(callWarningTip(QString)));
    taskDetailWidget = new TaskDetailWidget;

    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(taskPart);
    stackedWidget->addWidget(listDetailWidget);
    stackedWidget->addWidget(taskDetailWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(listPart, 1);
    mainLayout->addWidget(stackedWidget, 3);

    connect(taskPart, SIGNAL(callTaskItemDetailWidget(TaskItem*)), this, SLOT(switchToTaskItemDetailWidget(TaskItem*)));
    connect(taskPart, SIGNAL(callWarningTip(QString)), this, SLOT(callWarningTip(QString)));
    connect(listPart, SIGNAL(currentListItemChanged(ListItem*)), taskPart, SLOT(setListItem(ListItem*)));
    connect(listPart, SIGNAL(callWarningTip(QString)), this, SLOT(callWarningTip(QString)));
    connect(listPart, SIGNAL(callListDetailWidget(ListItem*)), this, SLOT(switchToListDetailWidget(ListItem *)));
    connect(listDetailWidget, SIGNAL(finish()), this, SLOT(switchToTaskPart()));
    connect(listDetailWidget, SIGNAL(callWarningTip(QString)), this, SLOT(callWarningTip(QString)));
    connect(listDetailWidget, SIGNAL(commitAdd(ListItem*,QString,QColor,QIcon)), listPart, SLOT(addListItem(ListItem*,QString,QColor,QIcon)));
    connect(listDetailWidget, SIGNAL(commitModify(ListItem*,QString,QColor,QIcon)), listPart, SLOT(modifyListItem(ListItem*,QString,QColor,QIcon)));
    connect(taskDetailWidget, SIGNAL(finish()), this, SLOT(switchToTaskPart()));
    connect(taskDetailWidget, SIGNAL(callWarningTip(QString)), this, SLOT(callWarningTip(QString)));
    connect(taskDetailWidget, SIGNAL(setTaskItemSignal(TaskItem*,QString,QString)), taskPart, SLOT(setTaskItem(TaskItem*,QString,QString)));

    this->setStyleSheet("QListWidget::item {height: 90px;}QListView {font: 25 11pt \"Microsoft YaHei\";border: 15px solid white;border-radius: 10px;}"
                            "QListView::item:hover {background-color: transparent;padding: 10px;border-left: 3px solid rgb(210, 210, 210);}"
                            "QListView::item:selected {background-color: transparent;color: black;padding: 10px;border-left: 3px solid rgb(140, 140, 140);}"
                            "QTreeWidget {font: 25 9pt \"Microsoft YaHei\";border: 15px solid white;border-radius: 10px;}"
                            "QTreeWidget::item {height: 80px;} "
                            "QTreeWidget::item:hover {background-color: transparent;padding: 10px;border-bottom: 3px solid rgb(130, 130, 130);}"
                            "QTreeWidget::item:selected {background-color: transparent;color: black;padding: 10px;}"
                            "QLineEdit {font: 35 12pt \"Microsoft YaHei\"; background:transparent; border: 3px solid white; border-bottom:3px solid rgb(229, 229, 229);}"
                            "QLineEdit:hover{border-bottom:3px solid rgb(193,193, 193);}QLineEdit:focus{border-bottom:3px solid rgb(157, 193, 231);}"
                            "QPushButton {font: 35 12pt \"Microsoft YaHei\"; background-color: rgba(0, 0, 0, 0); border: none;}"
                            "QPushButton:hover{border-bottom:3px solid rgb(84, 192, 151);}QPushButton:focus{border-bottom:2px solid rgb(84, 147, 140);}"
                            );
    this->setWindowTitle("CutePlus Todo");
    this->setWindowIcon(QIcon(":/icon/icon/icon.png"));
    this->setLayout(mainLayout);
    this->resize(1500, 1000);
    this->read();

    notice = new QNotify(this);
    notice->notify(tr("welcome!"), QNotify::SUCCESS);
}

Widget::~Widget()
{
}

void Widget::closeEvent(QCloseEvent *)
{
    save();
}

void Widget::save()
{
    taskPart->commit();
    listPart->save();
}

void Widget::read()
{
    listPart->read();
    listPart->setIndex(0);
}

void Widget::switchToListDetailWidget(ListItem *item)
{
    stackedWidget->setCurrentWidget(listDetailWidget);
    listDetailWidget->setListItem(item);
}

void Widget::switchToTaskPart()
{
    stackedWidget->setCurrentWidget(taskPart);
}

void Widget::switchToTaskItemDetailWidget(TaskItem *item)
{
    stackedWidget->setCurrentWidget(taskDetailWidget);
    taskDetailWidget->setTaskItemSource(item);
}

void Widget::callWarningTip(QString string)
{
    notice->notify(string, QNotify::WARNING);
}
