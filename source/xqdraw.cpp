#include "xqdraw.h"

void xDrawPixtoGView(QPixmap pmSource, QGraphicsView *target, DrawImgMethod method)
{
    //QMessageBox::information(this,tr("111"),tr("222"));
    QGraphicsScene *gsTarget=new QGraphicsScene;

    QSize szSource=pmSource.size();
    QSize szTarget=target->size();

    szTarget.setHeight(szTarget.height()-10);
    szTarget.setWidth(szTarget.width()-10);

    double dWidTimes=1.0*szTarget.width()/szSource.width();
    double dHeiTimes=1.0*szTarget.height()/szSource.height();
    switch(method)
    {
    case xORIGINAL:
        szTarget.setHeight(szSource.height());
        szTarget.setWidth(szSource.width());
        break;
    case xFULLFILL:
        break;
    case xPERSPECTIVE:
        if(dWidTimes>dHeiTimes)
        {
            szTarget.setWidth((int)(dHeiTimes*szSource.width()));
        }
        else
        {
            szTarget.setHeight((int)(dWidTimes*szSource.height()));
        }
        break;
    default:
        break;
    }

    QPixmap pmTarget=pmSource.scaled(szTarget);
    gsTarget->addPixmap(pmTarget);
    target->setScene(gsTarget);
    target->show();
}
