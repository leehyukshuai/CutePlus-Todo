#include "taskitemwidget.h"

TaskItemWidget::TaskItemWidget(TaskItem *item)
    : taskItem(item)
{
    checkBox = new QCheckBox;
    checkBox->setChecked(item->State());
    nameLabel = new QLabel();
    nameLabel->setText(item->Name());
    nameLabel->setStyleSheet("QLabel{background: transparent; color: black; font-family: \"Microsoft YaHei\";font-size: 9pt; border:2px transparent;}");
    timeLabel = new QLabel();
    timeLabel->setStyleSheet("QLabel{background: transparent; color: #29626f; font-family: \"Microsoft YaHei\";font-size: 8pt; }");
    timeLabel->setText(item->Time().toString(tr("M月d日 ddd hh:mm:ss")));
    layout = new QHBoxLayout(this);
    layout->addWidget(checkBox);
    layout->addWidget(nameLabel);
    layout->addWidget(timeLabel);

    connect(checkBox, SIGNAL(clicked(bool)), this, SLOT(emitFlipSignal()));
}

TaskItemWidget::~TaskItemWidget()
{
    delete checkBox;
    delete nameLabel;
    delete timeLabel;
    delete layout;
}

void TaskItemWidget::emitFlipSignal()
{
    emit flipSignal(taskItem);
}
