#include "edgedialog.h"
#include "ui_edgedialog.h"

edgeDialog::edgeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edgeDialog)
{
    ui->setupUi(this);
}

edgeDialog::~edgeDialog()
{
    delete ui;
}

void edgeDialog::on_isbEdge_valueChanged(int arg1)
{
    ui->hsEdge->setValue(arg1);
    edgeTry(arg1);
}

void edgeDialog::on_hsEdge_sliderMoved(int position)
{
    ui->isbEdge->setValue(position);
    edgeTry(position);
}

void edgeDialog::on_buttonBox_accepted()
{
    emit edgeapply();
}

void edgeDialog::edgeTry(int para)
{
    emit edgetry(para);
}

void edgeDialog::on_buttonBox_rejected()
{
    emit edgecancel();
}

void edgeDialog::on_hsEdge_valueChanged(int value)
{
    on_hsEdge_sliderMoved(value);
}
