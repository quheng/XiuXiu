#ifndef WHITENDIALOG_H
#define WHITENDIALOG_H

#include <QDialog>

namespace Ui {
class whitenDialog;
}

class whitenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit whitenDialog(QWidget *parent = 0);
    ~whitenDialog();

private slots:

    void on_hsWhiten_sliderMoved(int position);

    void on_hsWhiten_valueChanged(int value);

    void on_isbWhite_valueChanged(int arg1);

signals:
    void whitenpara(int para);
    void whitenapply();
    void whitencancel();

private:
    Ui::whitenDialog *ui;

private slots:
    void sendWhiten(int para);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // WHITENDIALOG_H
