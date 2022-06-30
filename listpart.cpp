#include "listpart.h"
#include <QDebug>

ListPart::ListPart(QWidget *parent)
    : QWidget(parent)
{
    listWidget = new ListWidget;
    connect(listWidget, SIGNAL(deleteListItem(ListItem*)), this, SLOT(onDeleleActionTriggered(ListItem*)));
    connect(listWidget, SIGNAL(modifyListItem(ListItem*)), this, SLOT(onModifyActionTriggered(ListItem*)));
    connect(listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(emitCurrentListItemChanged(QListWidgetItem*)));

    addListBtn = new QPushButton(tr("Add List"));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(listWidget);
    layout->addSpacing(30);
    layout->addWidget(addListBtn);
    layout->addSpacing(20);

    connect(addListBtn, SIGNAL(clicked(bool)), this, SLOT(onAddListBtnClicked()));

    this->setLayout(layout);
}

void ListPart::setIndex(int index)
{
    emitCurrentListItemChanged(listWidget->item(index));
}

void ListPart::save()
{
    QFile file("data.bin");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream stream(&file);
        for (int i = 0; i < listWidget->count(); ++i) {
            ListItem *listItem = static_cast<ListItem *>(listWidget->item(i));
            stream << *listItem;
        }
        file.close();
    }
}

void ListPart::read()
{
    QFile file("data.bin");
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    while (!stream.atEnd()) {
        ListItem *listItem = new ListItem;
        stream >> *listItem;
        addListItem(listItem);
    }
}

void ListPart::addListItem(ListItem *item)
{
    listWidget->addItem(item);
}

void ListPart::addListItem(ListItem *item, QString name, QColor color, QIcon icon)
{
    item = new ListItem;
    item->setText(name);
    item->setColor(color);
    item->setIcon(icon);
    listWidget->addItem(item);
}

void ListPart::modifyListItem(ListItem *item, QString name, QColor color, QIcon icon)
{
    item->setText(name);
    item->setColor(color);
    item->setIcon(icon);
    emitCurrentListItemChanged(item);
}

void ListPart::onAddListBtnClicked()
{
    emit callListDetailWidget(nullptr);
}

void ListPart::onDeleleActionTriggered(ListItem *listItem)
{
    emit callWarningTip(tr("This operation is irreversible."));
    listWidget->takeItem(listWidget->row(listItem));
    delete listItem;
}

void ListPart::onModifyActionTriggered(ListItem *listItem)
{
    emit callListDetailWidget(listItem);
}

void ListPart::emitCurrentListItemChanged(QListWidgetItem *listItem)
{
    emit currentListItemChanged(static_cast<ListItem *>(listItem));
}
