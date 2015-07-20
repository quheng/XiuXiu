#include "dialog.h"
#include "ui_dialog.h"
#include "xqdraw.h"

Dialog::Dialog(QWidget *parent, QPixmap _pmOrigin, QPixmap _pmPresent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    pmOrigin=_pmOrigin;
    pmPresent=_pmPresent;
    UpdateDiaUI();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::UpdateDiaUI()
{
    xDrawPixtoGView(pmOrigin, ui->gvOrigin,xPERSPECTIVE);
    xDrawPixtoGView(pmPresent, ui->gvPresent,xPERSPECTIVE);
    ui->gvOrigin->setMinimumWidth(0);
    ui->gvOrigin->setMinimumHeight(0);
    ui->gvPresent->setMinimumWidth(0);
    ui->gvPresent->setMinimumHeight(0);
}

void Dialog::resizeEvent(QResizeEvent *)
{
    UpdateDiaUI();
}
