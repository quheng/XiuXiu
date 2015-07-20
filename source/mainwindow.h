/*
 * Add filters:
 * -
 *
 * Add functions:
 * -    comic setComicCommand
 * -    whiten new dialog
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QMessageBox>
#include <QGraphicsView>
#include <QMainWindow>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFileDialog>
#include <string>
#include <QMouseEvent>
#include "common/common.h"
#include "common/CommandParameter.h"
#include <stdio.h>
#include <QWidget>
#include "dialog.h"
#include "xqdraw.h"
#include "edgedialog.h"
#include "xqgraphicsview.h"
#include "whitendialog.h"

#define dtoint(x) ((int)((x+1.0)/2.0*100))
#define inttod(x) (2.0*x/100-1.0)
#define dtopara(x) ((x+1.0)/2.0)

enum xEditType
{
    xGAMMA,
    xBRICON,
    xHUESAT
};

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString qsStyleSheet;
    QApplication *qaApp;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //bingding command
    void setOpenCommand    (const RefPtr<ICommandEx>& cmd){openCommand = cmd;}
    void setFaceLiftCommand(const RefPtr<ICommandEx>& cmd){faceLiftCommand = cmd;}
    void setGrayCommand    (const RefPtr<ICommandEx>& cmd){grayCommand = cmd;}

    void setUndoCommand    (const RefPtr<ICommandEx>& cmd){undoCommand = cmd;}
    void setRedoCommand    (const RefPtr<ICommandEx>& cmd){redoCommand = cmd;}

    void setHistCommand    (const RefPtr<ICommandEx>& cmd){histCommand = cmd;}
    void setMeibaiCommand  (const RefPtr<ICommandEx>& cmd){meibaiCommand = cmd;}
    void setPencilCommand  (const RefPtr<ICommandEx>& cmd){pencilCommand = cmd;}
    void setCrystalCommand (const RefPtr<ICommandEx>& cmd){crystalCommand = cmd;}
    void setAncientCommand (const RefPtr<ICommandEx>& cmd){ancientCommand = cmd;}
    void setCloseCommand   (const RefPtr<ICommandEx>& cmd){closeCommand = cmd;}
    void setGaussCommand   (const RefPtr<ICommandEx>& cmd){gaussCommand = cmd;}
    void setComicCommand   (const RefPtr<ICommandEx>& cmd){comicCommand = cmd;}

    void setEdgeCommand   (const RefPtr<ICommandEx>& cmd){edgeApplyCommand = cmd;}
    void setVerticleFlipCommand   (const RefPtr<ICommandEx>& cmd){verticleflipCommand = cmd;}
    void setHorizontalFlipCommand   (const RefPtr<ICommandEx>& cmd){horizontalflipCommand = cmd;}
    void setClockwiseCommand   (const RefPtr<ICommandEx>& cmd){clockwiseCommand = cmd;}
    void setCounterclockwiseCommand   (const RefPtr<ICommandEx>& cmd){counterclockwiseCommand = cmd;}

    void setEditApplyCommand   (const RefPtr<ICommandEx>& cmd){editApplyCommand = cmd;}
    void setEditCancleCommand   (const RefPtr<ICommandEx>& cmd){editCancleCommand = cmd;}
    void setEditGammaCommand   (const RefPtr<ICommandEx>& cmd){editGammaCommand = cmd;}
    void setEditBriConCommand   (const RefPtr<ICommandEx>& cmd){editBriConCommand = cmd;}
    void setEditHueSatCommand   (const RefPtr<ICommandEx>& cmd){editHueSatCommand = cmd;}

    void setEdgeApplyCommand   (const RefPtr<ICommandEx>& cmd){edgeApplyCommand = cmd;}
    void setEdgeTryCommand   (const RefPtr<ICommandEx>& cmd){edgeTryCommand = cmd;}
    void setEdgeCancelCommand   (const RefPtr<ICommandEx>& cmd){edgeCancelCommand = cmd;}


    //bingding data
    void setImageRef(const RefPtr<QImage>& refImg){img = refImg;}
    void setHistRef(const RefPtr<CQHistogram>& refImg){hist = refImg;}
    void UpdateUI();
    void resizeEvent(QResizeEvent *);

public slots:
    void edgeApply();
    void edgeCancel();
    void edgeTry(int para);
    void showmessage(int x, int y);
    void whitenpara(int para);
    void whitenapply();
    void whitencancel();

private slots:
    void on_open_triggered();

    void on_save_triggered();

    void on_save_as_triggered();

    void on_close_triggered();

    void on_facelift_triggered();

    void on_whiten_triggered();

    void on_pencil_triggered();

    void on_crystal_triggered();

    void on_ancient_triggered();

    void on_gray_triggered();

    void on_undo_triggered();

    void on_gauss_triggered();

    void on_showred_clicked();

    void on_showgreen_clicked();

    void on_showblue_clicked();

    void on_fanzhuan_triggered();

    void on_xuanzhuan_triggered();

    void on_horizontalflip_triggered();

    void on_counterclockwise_triggered();

    void on_origin_triggered();

    void on_hsBright_sliderMoved(int position);

    void on_dsbBright_valueChanged(double arg1);

    void on_dsbContrast_valueChanged(double arg1);

    void on_dsbSat_valueChanged(double arg1);

    void on_dsbHue_valueChanged(double arg1);

    void on_dsbGamma_valueChanged(double arg1);

    void on_hsContrast_sliderMoved(int position);

    void on_hsSat_sliderMoved(int position);

    void on_hsHue_sliderMoved(int position);

    void on_hsGamma_sliderMoved(int position);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_redo_triggered();

    void on_edge_triggered();

    void on_ll_triggered();

    void on_hsBright_valueChanged(int value);

    void on_hsContrast_valueChanged(int value);

    void on_hsSat_valueChanged(int value);

    void on_hsHue_valueChanged(int value);

    void on_hsGamma_valueChanged(int value);

    void on_actionComics_triggered();

private:
    QPoint qpLastPos;
    xQGraphicsView *xqgv;
    QStatusBar *sbStatusBar;
    QLabel qlStatus;
    Dialog *diaContrast;
    edgeDialog *edgedia;
    whitenDialog *whitendia;
    uint histstatus=0; //0 = red, 1=green, 2=blue
    QString presentfile="";
    bool filearu=false;
    bool showoriginal=false;
    void UpdateHist();
    void showExif();
    void editimage(xEditType edittype);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    Ui::MainWindow *ui;
    RefPtr<QImage> img;
    QPixmap pmOrigin;
    QPixmap pmPresent;
    RefPtr<CQHistogram> hist;
    QImage originimg;
    //command
    //open
    RefPtr<ICommandEx> openCommand;
    RefPtr<OneParameter<QString> > openPara;

    //facelift
    RefPtr<ICommandEx> faceLiftCommand;
    RefPtr<OneParameter<int> > faceLiftPara;

    //whiten
    RefPtr<ICommandEx> meibaiCommand;
    RefPtr<OneParameter<int> > meibaiPara;

    //pencil
    RefPtr<ICommandEx> pencilCommand;
    RefPtr<OneParameter<int> > pencilPara;

    //crystal
    RefPtr<ICommandEx> crystalCommand;

    //acient
    RefPtr<ICommandEx> ancientCommand;

    //gray
    RefPtr<ICommandEx> grayCommand;

    //undo
    RefPtr<ICommandEx> undoCommand;
    //redo
    RefPtr<ICommandEx> redoCommand;

    //hist
    RefPtr<ICommandEx> histCommand;

    //close
    RefPtr<ICommandEx> closeCommand;

    //edge
    RefPtr<ICommandEx> edgeApplyCommand;

    //edgecancel
    RefPtr<ICommandEx> edgeCancelCommand;

    //gause
    RefPtr<ICommandEx> gaussCommand;
    RefPtr<OneParameter<int> > gaussPara;

    //verticleflip
    RefPtr<ICommandEx> verticleflipCommand;

    //horizontalflip
    RefPtr<ICommandEx> horizontalflipCommand;

    //clockwise turn
    RefPtr<ICommandEx> clockwiseCommand;

    //counter-clockwise turn
    RefPtr<ICommandEx> counterclockwiseCommand;

    //Edit image
    //Gamma
    RefPtr<ICommandEx> editGammaCommand;
    RefPtr<OneParameter<CImagePara> > editGammaPara;
    //Bright & Contrast
    RefPtr<ICommandEx> editBriConCommand;
    RefPtr<OneParameter<CImagePara> > editBriConPara;
    //Hue & Saturation
    RefPtr<ICommandEx> editHueSatCommand;
    RefPtr<OneParameter<CImagePara> > editHueSatPara;
    //Apply
    RefPtr<ICommandEx> editApplyCommand;
    //Cancle
    RefPtr<ICommandEx> editCancleCommand;

    //Edgetry
    RefPtr<ICommandEx> edgeTryCommand;
    RefPtr<OneParameter<int> > edgeTryPara;

    //comic
    RefPtr<ICommandEx> comicCommand;

    //debug
private:
    bool debug_gray=true;

};
#endif // MAINWINDOW_H
