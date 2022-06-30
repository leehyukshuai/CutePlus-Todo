#ifndef LISTDETAILWIDGET_H
#define LISTDETAILWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPainter>
#include "listitem.h"

class ListDetailWidget : public QWidget
{
    Q_OBJECT

private:
    ListItem *listItem;
    QLineEdit *nameInput;
    QLabel *colorPreview;
    QSlider *redInput;
    QSlider *greenInput;
    QSlider *blueInput;
    QComboBox *iconInput;

public:
    explicit ListDetailWidget(QWidget *parent = nullptr);
    void setListItem(ListItem *_listItem);

protected:
    void paintEvent(QPaintEvent *);

signals:
    void finish();
    void callWarningTip(QString string);
    void commitModify(ListItem *, QString, QColor, QIcon);
    void commitAdd(ListItem *, QString, QColor, QIcon);

private slots:
    void onYesBtnClicked();
    void onCancelBtnClicked();
};

#endif // LISTDETAILWIDGET_H
