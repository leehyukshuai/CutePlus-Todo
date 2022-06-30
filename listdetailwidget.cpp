#include "listdetailwidget.h"
#include <QDebug>

ListDetailWidget::ListDetailWidget(QWidget *parent) : QWidget(parent)
{
    QPushButton *yesBtn = new QPushButton(tr("Yes"));
    QPushButton *cancelBtn = new QPushButton(tr("Cancel"));
    connect(yesBtn, SIGNAL(clicked(bool)), this, SLOT(onYesBtnClicked()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(onCancelBtnClicked()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(yesBtn);
    buttonLayout->addWidget(cancelBtn);

    QLabel *nameLabel = new QLabel(tr("Name: "));
    nameInput = new QLineEdit;

    QLabel *colorLabel = new QLabel(tr("Color:"));
    colorPreview = new QLabel;
    colorPreview->setStyleSheet("min-width:40px;min-height:40px;max-width:40px;max-height:40px;border-radius:20px;border:1px solid white;");
//    redInput = new QSlider(Qt::Horizontal);
//    greenInput = new QSlider(Qt::Horizontal);
//    blueInput = new QSlider(Qt::Horizontal);
    redInput = new QSlider(Qt::Vertical);
    greenInput = new QSlider(Qt::Vertical);
    blueInput = new QSlider(Qt::Vertical);
    redInput->setRange(0, 255);
    greenInput->setRange(0, 255);
    blueInput->setRange(0, 255);
    connect(redInput, SIGNAL(valueChanged(int)), this, SLOT(update()));
    connect(greenInput, SIGNAL(valueChanged(int)), this, SLOT(update()));
    connect(blueInput, SIGNAL(valueChanged(int)), this, SLOT(update()));

    QLabel *iconLabel = new QLabel(tr("Icon: "));
    iconInput = new QComboBox;
    QList<QIcon> iconList;
    iconList << QIcon(":/icons/contact.svg")
             << QIcon(":/icons/important.svg")
             << QIcon(":/icons/life.svg")
             << QIcon(":/icons/normal.svg")
             << QIcon(":/icons/shopping.svg")
             << QIcon(":/icons/study.svg");
    foreach (QIcon icon, iconList) {
        iconInput->addItem(icon, "");
    }

    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameInput, 1);

    QHBoxLayout *colorLayout = new QHBoxLayout;
    colorLayout->addWidget(colorLabel);
    colorLayout->addWidget(colorPreview, 1);
    colorLayout->addStretch(1);
    colorLayout->addWidget(redInput, 1);
    colorLayout->addStretch(1);
    colorLayout->addWidget(greenInput, 1);
    colorLayout->addStretch(1);
    colorLayout->addWidget(blueInput, 1);
    colorLayout->addStretch(4);

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(iconLabel);
    iconLayout->addWidget(iconInput, 1);
    iconLayout->addStretch(5);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch(1);
    mainLayout->addLayout(nameLayout, 1);
    mainLayout->addStretch(1);
    mainLayout->addLayout(colorLayout, 1);
    mainLayout->addStretch(1);
    mainLayout->addLayout(iconLayout, 1);
    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout, 1);
    mainLayout->addStretch(1);

    this->setStyleSheet("QLabel{font: 35 12pt \"Microsoft YaHei\"; background-color: rgba(0, 0, 0, 0); border: none;}");

}

void ListDetailWidget::setListItem(ListItem *_listItem)
{
    listItem = _listItem;
    if (listItem) {
        nameInput->setText(listItem->text());
        redInput->setValue(listItem->Color().red());
        greenInput->setValue(listItem->Color().green());
        blueInput->setValue(listItem->Color().blue());
        iconInput->setCurrentIndex(0);
    } else {
        nameInput->setText("");
        redInput->setValue(128);
        greenInput->setValue(128);
        blueInput->setValue(128);
        iconInput->setCurrentIndex(0);
    }
}

void ListDetailWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QBrush brush(QColor(redInput->value(), greenInput->value(), blueInput->value()));
    painter.setBrush(brush);
    painter.setPen(QPen(Qt::white));
    QRect rect = colorPreview->rect();
    rect.moveTopLeft(colorPreview->pos());
    painter.drawEllipse(rect);
}

void ListDetailWidget::onYesBtnClicked()
{
    if (nameInput->text().isEmpty()) {
        emit callWarningTip(tr("Name is blank."));
        return;
    }
    QString name(nameInput->text());
    QColor color(redInput->value(), greenInput->value(), blueInput->value());
    QIcon icon = iconInput->itemIcon(iconInput->currentIndex());
    if (listItem == nullptr) {
        emit commitAdd(listItem, name, color, icon);
    } else {
        emit commitModify(listItem, name, color, icon);
    }
    emit finish();
}

void ListDetailWidget::onCancelBtnClicked()
{
    emit finish();
}
