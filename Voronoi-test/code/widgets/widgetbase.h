#ifndef WIDGETFOUNTAIN_H
#define WIDGETFOUNTAIN_H

#include <QWidget>

namespace Ui {
class WidgetBase;
}

class WidgetBase : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetBase(QWidget *parent = nullptr);
    ~WidgetBase();


signals:

private:
    Ui::WidgetBase *ui;
};

#endif // WIDGETFOUNTAIN_H
