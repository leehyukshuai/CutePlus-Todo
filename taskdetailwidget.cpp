#include "taskdetailwidget.h"

TaskDetailWidget::TaskDetailWidget(QWidget *parent) : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Name:"));
    QLabel *detailLabel = new QLabel(tr("Detail:"));
    nameInput = new QLineEdit;
    detailInput = new QLineEdit;

    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameInput);

    QHBoxLayout *detailLayout = new QHBoxLayout;
    detailLayout->addWidget(detailLabel);
    detailLayout->addWidget(detailInput);

    QPushButton *yesBtn = new QPushButton(tr("Yes"));
    QPushButton *cancelBtn = new QPushButton(tr("Cancel"));
    connect(yesBtn, SIGNAL(clicked(bool)), this, SLOT(onYesBtnClicked()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(onCancelBtnClicked()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(yesBtn);
    buttonLayout->addWidget(cancelBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addStretch(1);
    mainLayout->addLayout(nameLayout);
    mainLayout->addStretch(1);
    mainLayout->addLayout(detailLayout);
    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch(2);

    this->setLayout(mainLayout);

    this->setStyleSheet("QLabel{font: 35 12pt \"Microsoft YaHei\"; background-color: rgba(0, 0, 0, 0); border: none;}"
                        "QComboBox { border-width: 2px; border-radius: 8px; border-style: solid; border-top-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 #c1c9cf, stop:1 #d2d8dd); border-right-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #c1c9cf, stop:1 #d2d8dd); border-bottom-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 #c1c9cf, stop:1 #d2d8dd); border-left-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 #c1c9cf, stop:1 #d2d8dd); background-color: #f4f4f4; color: #272727; padding-left: 5px;}"
                        "QComboBox:editable, QComboBox:!editable, QComboBox::drop-down:editable, QComboBox:!editable:on, QComboBox::drop-down:editable:on { background: #ffffff;}"
                        "QComboBox::drop-down { subcontrol-origin: padding; subcontrol-position: top right; width: 15px; color: #272727; border-left-width: 1px; border-left-color: darkgray; border-left-style: solid; border-top-right-radius: 3px; border-bottom-right-radius: 3px;}"
                        "QComboBox::down-arrow { image: url(/usr/share/icons/Adwaita/16x16/actions/go-down-symbolic.symbolic.png); /*Adawaita icon thene*/}QComboBox::down-arrow:on { top: 1px; left: 1px;}"
                        "QComboBox QAbstractItemView { border: 1px solid darkgray; border-radius: 8px; selection-background-color: #dadada; selection-color: #272727; color: #272727; background: white;}");
}

void TaskDetailWidget::setTaskItemSource(TaskItem *item)
{
    taskItem = item;
    if (taskItem == nullptr) {
        nameInput->clear();
        detailInput->clear();
    } else {
        nameInput->setText(item->Name());
        detailInput->setText(item->Detail());
    }
}

void TaskDetailWidget::onYesBtnClicked()
{
    if (nameInput->text().isEmpty()) {
        emit callWarningTip("Task name is blank.");
        return;
    }
    emit setTaskItemSignal(taskItem, nameInput->text(), detailInput->text());
    emit finish();
}

void TaskDetailWidget::onCancelBtnClicked()
{
    emit finish();
}
