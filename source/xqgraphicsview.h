#ifndef XQGRAPHICSVIEW
#define XQGRAPHICSVIEW

#include <QGraphicsView>
#include <QPoint>
#include <QMouseEvent>
#include <QDialog>
#include <QLabel>
#include <QAction>

class xQGraphicsView : public QGraphicsView
{
    Q_OBJECT
private:
    QPoint qpMouse,qpNewMouse;
    bool bLeftdown;
    QWidget *parent;

public slots:
    void sendpos(int x, int y);

signals:
    void mousemove(int x,int y);

public:
    xQGraphicsView(QWidget *parent);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // XQGRAPHICSVIEW

