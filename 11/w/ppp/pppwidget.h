#ifndef PPPWIDGET_H
#define PPPWIDGET_H

#include <QWidget>

class pppWidget : public QWidget
{
    Q_OBJECT
public:
    explicit pppWidget(QWidget *parent = 0);
    ~pppWidget();

signals:

public slots:

protected:
    virtual void paintEvent(QPaintEvent * event);
};

#endif // PPPWIDGET_H
