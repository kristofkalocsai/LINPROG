#include "pppwidget.h"
#include "qpainter.h"

pppWidget::pppWidget(QWidget *parent) : QWidget(parent)
{

}

pppWidget::~pppWidget()
{

}

void pppWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter p(this);

    QRect rect = geometry();
    int w = rect.width();
    int h = rect.height();
    int bw = w/3;
    int bh = h/3;

    QPen linepen(Qt::black, 1);
    p.setPen(linepen);

    p.drawRect(0,0,w,h);

    for(int i = 1;i<3; i++){
        p.drawLine(i*bw, 0, i*bw, h);
        p.drawLine(0, i*bh, w, i*bh);
    }

}

