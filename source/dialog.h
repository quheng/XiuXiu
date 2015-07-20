#ifndef DIALOG_H
#define DIALOG_H

#include <QMainWindow>
#include <QDialog>
#include <QPixmap>
#include <QWidget>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent, QPixmap _pmOrigin, QPixmap _pmPresent);
    ~Dialog();
    void resizeEvent(QResizeEvent *);
    void UpdateDiaUI();

private:
    Ui::Dialog *ui;
    QPixmap pmOrigin;
    QPixmap pmPresent;
};

#endif // DIALOG_H
