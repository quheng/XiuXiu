#include "whitendialog.h"
#include "ui_whitendialog.h"

whitenDialog::whitenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::whitenDialog)
{
    ui->setupUi(this);
}

whitenDialog::~whitenDialog()
{
    delete ui;
}

void whitenDialog::on_hsWhiten_sliderMoved(int position)
{
    ui->isbWhite->setValue(position);
    sendWhiten(position);
}

void whitenDialog::on_hsWhiten_valueChanged(int value)
{
    on_hsWhiten_sliderMoved(value);
}

void whitenDialog::on_isbWhite_valueChanged(int arg1)
{
    ui->hsWhiten->setValue(arg1);
    sendWhiten(arg1);
}

void whitenDialog::sendWhiten(int para)
{
    emit whitenpara(para);
}

void whitenDialog::on_buttonBox_accepted()
{
    emit whitenapply();
}

void whitenDialog::on_buttonBox_rejected()
{
    emit whitencancel();
}
