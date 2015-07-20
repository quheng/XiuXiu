#include "xqgraphicsview.h"
#include <QMessageBox>
#include <QStatusBar>


xQGraphicsView::xQGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
}

void xQGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    qpMouse = qpNewMouse;
    qpNewMouse = event->pos();
    sendpos(qpNewMouse.x(),qpNewMouse.y());
}

void xQGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        bLeftdown=true;
    }
}

void xQGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        bLeftdown=false;
    }
}

void xQGraphicsView::sendpos(int x, int y)
{
    emit mousemove(x,y);
}
