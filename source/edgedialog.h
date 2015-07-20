#ifndef EDGEDIALOG_H
#define EDGEDIALOG_H

#include <QDialog>

namespace Ui {
class edgeDialog;
}

class edgeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit edgeDialog(QWidget *parent = 0);
    ~edgeDialog();

public slots:
    void edgeTry(int para);

signals:
    void edgetry(int);
    void edgeapply();
    void edgecancel();

private slots:
    void on_isbEdge_valueChanged(int arg1);

    void on_hsEdge_sliderMoved(int position);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_hsEdge_valueChanged(int value);

private:
    Ui::edgeDialog *ui;
};

#endif // EDGEDIALOG_H
