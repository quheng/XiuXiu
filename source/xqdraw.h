#ifndef XQDRAW
#define XQDRAW

#include <QPixmap>
#include <QGraphicsView>

enum DrawImgMethod
{
    xORIGINAL,
    xFULLFILL,
    xPERSPECTIVE
};

void xDrawPixtoGView(QPixmap pmSource, QGraphicsView *target, DrawImgMethod method);

#endif // XQDRAW

