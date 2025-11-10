#include "widgetbase.h"
#include "ui_widgetbase.h"

WidgetBase::WidgetBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetBase)
{
    ui->setupUi(this);

}

WidgetBase::~WidgetBase()
{
    delete ui;
}

