#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "exif.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //actions
    //file
    ui->save->setEnabled(false);
    ui->save_as->setEnabled(false);
    ui->close->setEnabled(false);
    //edit
    ui->undo->setEnabled(false);
    ui->redo->setEnabled(false);
    ui->origin->setEnabled(false);
    //filter
    ui->ancient->setEnabled(false);
    ui->crystal->setEnabled(false);
    ui->pencil->setEnabled(false);
    ui->gauss->setEnabled(false);
    ui->gray->setEnabled(false);
    ui->actionComics->setEnabled(false);
    ui->edge->setEnabled(false);
    //meirong
    ui->facelift->setEnabled(false);
    ui->whiten->setEnabled(false);
    //image
    ui->fanzhuan->setEnabled(false);
    ui->xuanzhuan->setEnabled(false);
    ui->counterclockwise->setEnabled(false);
    ui->horizontalflip->setEnabled(false);

    //buttons
    //hist
    ui->showred->setEnabled(false);
    ui->showblue->setEnabled(false);
    ui->showgreen->setEnabled(false);
    //editimg
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->hsBright->setEnabled(false);
    ui->hsContrast->setEnabled(false);
    ui->hsGamma->setEnabled(false);
    ui->hsHue->setEnabled(false);
    ui->hsSat->setEnabled(false);
    ui->dsbBright->setEnabled(false);
    ui->dsbContrast->setEnabled(false);
    ui->dsbGamma->setEnabled(false);
    ui->dsbHue->setEnabled(false);
    ui->dsbSat->setEnabled(false);
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setStyleSheet(QString("QMenu::item{ background-color: blue}"));

    xqgv=ui->graphicsView;
    connect(xqgv,SIGNAL(mousemove(int,int)),this,SLOT(showmessage(int,int)));

    UpdateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}
QString int2QString(int n) {
    char buf[10];
    sprintf(buf, "%d", n);
    std::string b = buf;
    return QString::fromStdString(b);
}

QString float2QString(float n) {
    char buf[10];
    sprintf(buf, "%.2f", n);
    std::string b = buf;
    return QString::fromStdString(b);
}

void MainWindow::showExif(){
    Cexif exif;
    EXIFINFO *pexif=(EXIFINFO *)malloc(sizeof(EXIFINFO));
    if(pexif==NULL)
       return;

    FILE *fp=fopen(presentfile.toStdString().c_str(),"rb");
          exif.DecodeExif(fp);
    exif.getExifinfo(pexif);
    fclose(fp);

    QString str;
    //宽度
    str = int2QString(pexif->Width);
    if (str.isEmpty())
        ui->l1_1->setText("None");
    else
        ui->l1_1->setText(str);
    str.clear();

    //高度
    str = int2QString(pexif->Height);
    if (str.isEmpty())
        ui->l1_2->setText("None");
    else
        ui->l1_2->setText(str);
    str.clear();

    //曝光时间
//    str = float2QString(pexif->ExposureTime);
    if (str.isEmpty())
        ui->l1_3->setText("None");
    else
    {
        int basetime=(int)(1.0/pexif->ExposureTime);
        str=QString("1 / %1 s").arg(basetime);
        ui->l1_3->setText(str);
    }
    str.clear();

    //光圈大小
    str = float2QString(pexif->ApertureFNumber);
    if (str.isEmpty())
        ui->l1_4->setText("None");
    else
        ui->l1_4->setText(str);
    str.clear();

    //测光方式
    QString cgfs;
    str = int2QString(pexif->MeteringMode);
    if (str.isEmpty())
        ui->l1_5->setText("None");
    else
    {
        if(str=="6")
        {
            cgfs=QString("Super focused");
        }
        else if(str=="2")
        {
            cgfs=QString("Center Focused");
        }
        else if(str=="5")
        {
            cgfs=QString("Five Area");
        }
        else
        {
            cgfs=QString("None");
        }
        ui->l1_5->setText(cgfs);
    }
    str.clear();

    //曝光模式
    str = int2QString(pexif->ExposureProgram);
    if (str.isEmpty())
       ui->l1_6->setText("None");
    else
    {
        if(str=="2")
        {
            str=QString("Program");
        }
        else if(str=="3")
        {
            str=QString("Aperture priority");
        }
        else if(str=="4")
        {
            str=QString("Shutter priority");
        }
        else if(str=="5")
        {
            str=QString("Manual");
        }
        else if(str=="6")
        {
            str=QString("Default");
        }
        else
        {
            str=QString("Other");
        }
    }

    //曝光补偿
    str = float2QString(pexif->ExposureBias);
    if (str.isEmpty())
        ui->l1_7->setText("None");
    else
        ui->l1_7->setText(str);
    str.clear();

    //相机信息
    str = QString::fromUtf8(pexif->CameraModel);
    if (str.isEmpty())
       ui->l1_8->setText("None");
    else
       ui->l1_8->setText(str);
    str.clear();
}

void MainWindow::UpdateUI()
{

    //QMessageBox::information(this,tr("ui"),tr("ui"));
    if(!filearu)
    {
        //actions
        //file
        ui->save->setEnabled(false);
        ui->save_as->setEnabled(false);
        ui->close->setEnabled(false);
        //edit
        ui->undo->setEnabled(false);
        ui->redo->setEnabled(false);
        ui->origin->setEnabled(false);
        //filter
        ui->ancient->setEnabled(false);
        ui->crystal->setEnabled(false);
        ui->pencil->setEnabled(false);
        ui->gauss->setEnabled(false);
        ui->gray->setEnabled(false);
        ui->actionComics->setEnabled(false);
        ui->edge->setEnabled(false);
        //meirong
        ui->facelift->setEnabled(false);
        ui->whiten->setEnabled(false);
        //image
        ui->fanzhuan->setEnabled(false);
        ui->xuanzhuan->setEnabled(false);
        ui->counterclockwise->setEnabled(false);
        ui->horizontalflip->setEnabled(false);

        //buttons
        //hist
        ui->showred->setEnabled(false);
        ui->showblue->setEnabled(false);
        ui->showgreen->setEnabled(false);
        //editimg
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->hsBright->setEnabled(false);
        ui->hsContrast->setEnabled(false);
        ui->hsGamma->setEnabled(false);
        ui->hsHue->setEnabled(false);
        ui->hsSat->setEnabled(false);
        ui->dsbBright->setEnabled(false);
        ui->dsbContrast->setEnabled(false);
        ui->dsbGamma->setEnabled(false);
        ui->dsbHue->setEnabled(false);
        ui->dsbSat->setEnabled(false);
        this->setWindowTitle("丑图秀秀 - Xiuxiu");
    }
    else
    {

        this->setWindowTitle("丑图秀秀 - Xiuxiu( "+presentfile+" )");
        //actions
        //file
        ui->save->setEnabled(true);
        ui->save_as->setEnabled(true);
        ui->close->setEnabled(true);
        //edit
        ui->undo->setEnabled(true);
        ui->redo->setEnabled(true);
        ui->origin->setEnabled(true);
        //filter
        ui->ancient->setEnabled(true);
        ui->crystal->setEnabled(true);
        ui->pencil->setEnabled(true);
        ui->gauss->setEnabled(true);
        ui->gray->setEnabled(true);
        ui->actionComics->setEnabled(true);
        ui->edge->setEnabled(true);
        //meirong
        ui->facelift->setEnabled(true);
        ui->whiten->setEnabled(true);
        //image
        ui->fanzhuan->setEnabled(true);
        ui->xuanzhuan->setEnabled(true);
        ui->counterclockwise->setEnabled(true);
        ui->horizontalflip->setEnabled(true);

        //buttons
        //hist
        ui->showred->setEnabled(true);
        ui->showblue->setEnabled(true);
        ui->showgreen->setEnabled(true);
        //editimg
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->hsBright->setEnabled(true);
        ui->hsContrast->setEnabled(true);
        ui->hsGamma->setEnabled(true);
        ui->hsHue->setEnabled(true);
        ui->hsSat->setEnabled(true);
        ui->dsbBright->setEnabled(true);
        ui->dsbContrast->setEnabled(true);
        ui->dsbGamma->setEnabled(true);
        ui->dsbHue->setEnabled(true);
        ui->dsbSat->setEnabled(true);

        QPixmap pixscene;
        pixscene=QPixmap(QPixmap::fromImage(img.Deref()));
        //pixscene=QPixmap(":/resource/png/back.png");
        xDrawPixtoGView(pixscene,ui->graphicsView,xPERSPECTIVE);
        pmPresent=pixscene;
        UpdateHist();
    }
}

void MainWindow::UpdateHist()
{
    QPixmap histpix;
    if(!filearu || img.Deref().isGrayscale())
    //if(!filearu || debug_gray)
    {
        //filter
        ui->actionComics->setEnabled(false);
        ui->ancient->setEnabled(false);
        ui->crystal->setEnabled(false);
        ui->pencil->setEnabled(false);
        ui->gray->setEnabled(false);
        //buttons
        //hist
        ui->showred->setEnabled(false);
        ui->showblue->setEnabled(false);
        ui->showgreen->setEnabled(false);
        //editimg
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->hsBright->setEnabled(false);
        ui->hsContrast->setEnabled(false);
        ui->hsGamma->setEnabled(false);
        ui->hsHue->setEnabled(false);
        ui->hsSat->setEnabled(false);
        ui->dsbBright->setEnabled(false);
        ui->dsbContrast->setEnabled(false);
        ui->dsbGamma->setEnabled(false);
        ui->dsbHue->setEnabled(false);
        ui->dsbSat->setEnabled(false);
    }
    if(filearu)
    {
        if(!img.Deref().isGrayscale())
        //if(!debug_gray)
        {
            //histCommand.Deref().Exec();
            QImage redimg, greenimg, blueimg;
            redimg=hist.Deref().getRedHistogram();
            greenimg=hist.Deref().getGreenHistogram();
            blueimg=hist.Deref().getBlueHistogram();
            QImage histimg(redimg.size(),redimg.format());
            switch(histstatus)
            {
            case 0: histimg=redimg; break;
            case 1: histimg=greenimg; break;
            case 2: histimg=blueimg; break;
            default: QMessageBox::information(this, tr("error! unexpected histstatus"), tr("unexpected histstatus"));
            }
            histpix=QPixmap(QPixmap::fromImage(histimg));

        }
        else
        {
            histpix=QPixmap(":/resource/png/blank.png");
        }
        xDrawPixtoGView(histpix,ui->hist,xFULLFILL);
    }
}

//slot: open
void MainWindow::on_open_triggered()
{
    on_pushButton_2_clicked();
    QString fileName = QFileDialog::getOpenFileName(
                this, "open image file",
                ".",
                "Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
    if(!fileName.isEmpty())
    {
        presentfile=fileName;
        filearu=true;

        OneParameter<QString> *namePara = new OneParameter<QString>;
        namePara->setPara(fileName);
        RefPtr<OneParameter<QString> > *openPara = new RefPtr<OneParameter<QString> >(namePara);
        openCommand.Deref().SetParameter(RefPtrHelper::TypeCast<OneParameter<QString>,ICommandParameter >(*openPara));

        openCommand.Deref().Exec();
        pmOrigin=QPixmap(QPixmap::fromImage(img.Deref()));
        showExif();
        UpdateUI();
    }
}

//Slot: Save
void MainWindow::on_save_triggered()
{
    if (!presentfile.isNull())
    {
        img.Deref().save(presentfile);
    }
}

//Slot: Save_as
void MainWindow::on_save_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),"",tr("Save as (*.jpg)"));
    if (!fileName.isNull())
    {
        img.Deref().save(fileName);
    }
}


//Slot:Close
void MainWindow::on_close_triggered()
{
    filearu=false;
    closeCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::on_facelift_triggered()
{
    faceLiftCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::on_whiten_triggered()
{
    whitendia=new whitenDialog;
    whitendia->show();
    connect(whitendia,SIGNAL(whitenpara(int)),this,SLOT(whitenpara(int)));
    connect(whitendia,SIGNAL(whitenapply()),this,SLOT(whitenapply()));
    connect(whitendia,SIGNAL(whitencancel()),this,SLOT(whitencancel()));
    UpdateUI();
}

void MainWindow::on_pencil_triggered()
{
    pencilCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::on_crystal_triggered()
{
    crystalCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::on_ancient_triggered()
{
    ancientCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::on_gray_triggered()
{
    grayCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::on_undo_triggered()
{
    undoCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::on_gauss_triggered()
{
    gaussCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::on_showred_clicked()
{
    histstatus = 0;
    UpdateUI();
}

void MainWindow::on_showgreen_clicked()
{
    histstatus = 1;
    UpdateUI();
}

void MainWindow::on_showblue_clicked()
{
    histstatus = 2;
    UpdateUI();
}

void MainWindow::on_fanzhuan_triggered()
{
    verticleflipCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::on_xuanzhuan_triggered()
{
    clockwiseCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::on_horizontalflip_triggered()
{
    horizontalflipCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::resizeEvent(QResizeEvent *resizeevent)
{
    UpdateUI();
}

void MainWindow::on_counterclockwise_triggered()
{
    counterclockwiseCommand.Deref().Exec();
    UpdateUI();
}


void MainWindow::on_origin_triggered()
{
    diaContrast = new Dialog(this,pmOrigin,pmPresent);
    diaContrast->show();
}


void MainWindow::on_dsbBright_valueChanged(double arg1)
{
    int _hsBright=dtoint(arg1);
    ui->hsBright->setValue(_hsBright);
    editimage(xBRICON);
}

void MainWindow::on_dsbContrast_valueChanged(double arg1)
{
    int _hsContrast=dtoint(arg1);
    ui->hsContrast->setValue(_hsContrast);
    editimage(xBRICON);
}

void MainWindow::on_dsbSat_valueChanged(double arg1)
{
    int _hsSat=dtoint(arg1);
    ui->hsSat->setValue(_hsSat);
    editimage(xHUESAT);
}

void MainWindow::on_dsbHue_valueChanged(double arg1)
{
    int _hsHue=dtoint(arg1);
    ui->hsHue->setValue(_hsHue);
    editimage(xHUESAT);
}

void MainWindow::on_dsbGamma_valueChanged(double arg1)
{
    int _hsGamma=dtoint(arg1);
    ui->hsGamma->setValue(_hsGamma);
    editimage(xGAMMA);
}

void MainWindow::on_hsBright_sliderMoved(int position)
{
    double _dsbBright=inttod(position);
    ui->dsbBright->setValue(_dsbBright);
    editimage(xBRICON);
}

void MainWindow::on_hsContrast_sliderMoved(int position)
{
    double _dsbContrast=inttod(position);
    ui->dsbContrast->setValue(_dsbContrast);
    editimage(xBRICON);
}

void MainWindow::on_hsSat_sliderMoved(int position)
{
    double _dsbSat=inttod(position);
    ui->dsbSat->setValue(_dsbSat);
    editimage(xHUESAT);
}

void MainWindow::on_hsHue_sliderMoved(int position)
{
    double _dsbHue=inttod(position);
    ui->dsbHue->setValue(_dsbHue);
    editimage(xHUESAT);
}

void MainWindow::on_hsGamma_sliderMoved(int position)
{
    double _dsbGamma=inttod(position);
    ui->dsbGamma->setValue(_dsbGamma);
    editimage(xGAMMA);
}

void MainWindow::editimage(xEditType edittype)
{
    CImagePara _editPara;
    _editPara.bright=dtopara(ui->dsbBright->value());
    _editPara.contrast=dtopara(ui->dsbContrast->value());
    _editPara.gamma=dtopara(ui->dsbGamma->value());
    _editPara.hue=dtopara(ui->dsbHue->value());
    _editPara.saturation=dtopara(ui->dsbSat->value());

    OneParameter<CImagePara> *editPara = new OneParameter<CImagePara>;
    editPara->setPara(_editPara);
    RefPtr<OneParameter<CImagePara> > *editParaRef = new RefPtr<OneParameter<CImagePara> >(editPara);
    switch(edittype)
    {
    case xGAMMA: editGammaCommand.Deref().SetParameter(RefPtrHelper::TypeCast<OneParameter<CImagePara>,ICommandParameter >(*editParaRef));
        editGammaCommand.Deref().Exec();
        break;
    case xBRICON: editBriConCommand.Deref().SetParameter(RefPtrHelper::TypeCast<OneParameter<CImagePara>,ICommandParameter >(*editParaRef));
        editBriConCommand.Deref().Exec();
        break;
    case xHUESAT: editHueSatCommand.Deref().SetParameter(RefPtrHelper::TypeCast<OneParameter<CImagePara>,ICommandParameter >(*editParaRef));
        editHueSatCommand.Deref().Exec();
        break;
    default: break;
    }
    UpdateUI();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->dsbBright->setValue(0.0);
    ui->dsbContrast->setValue(0.0);
    ui->dsbGamma->setValue(0.0);
    ui->dsbHue->setValue(0.0);
    ui->dsbSat->setValue(0.0);
    if(filearu)
    {
        editCancleCommand.Deref().Exec();
    }
    UpdateUI();
}

void MainWindow::on_pushButton_clicked()
{
    editApplyCommand.Deref().Exec();
    ui->dsbBright->setValue(0.0);
    ui->dsbContrast->setValue(0.0);
    ui->dsbGamma->setValue(0.0);
    ui->dsbHue->setValue(0.0);
    ui->dsbSat->setValue(0.0);
    UpdateUI();
}

void MainWindow::on_redo_triggered()
{
    redoCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::on_edge_triggered()
{
    edgedia=new edgeDialog;
    connect(edgedia,SIGNAL(edgetry(int)),this,SLOT(edgeTry(int)));
    connect(edgedia,SIGNAL(edgeapply()),this,SLOT(edgeApply()));
    connect(edgedia,SIGNAL(edgecancel()),this,SLOT(edgeCancel()));
    edgedia->show();

    UpdateUI();
}

void MainWindow::edgeApply()
{
    //QMessageBox::information(this,"edgeapply","edgeapply");
    editApplyCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::edgeTry(int para)
{
    //QMessageBox::information(this,"edgetry","edgetry");
    OneParameter<int> *edgePara = new OneParameter<int>;
    edgePara->setPara(para);
    RefPtr<OneParameter<int> > *edgeParaSend = new RefPtr<OneParameter<int> >(edgePara);
    edgeTryCommand.Deref().SetParameter(RefPtrHelper::TypeCast<OneParameter<int>,ICommandParameter >(*edgeParaSend));

    edgeTryCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::edgeCancel()
{
    //QMessageBox::information(this,"edgec","edgec");
    editCancleCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::showmessage(int x,int y)
{
    QString m=QString("(%1,%2)").arg(x).arg(y);
    ui->ll->setText(m);
}

void MainWindow::on_ll_triggered()
{
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    qpLastPos = event->globalPos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
//    int dx=event->globalX()-qpLastPos.x();
//    int dy=event->globalY()-qpLastPos.y();
//    qpLastPos=event->globalPos();
//    move(x()+dx,y()+dy);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
//    int dx=event->globalX()-qpLastPos.x();
//    int dy=event->globalY()-qpLastPos.y();
//    move(x()+dx,y()+dy);
}

void MainWindow::on_hsBright_valueChanged(int value)
{
    on_hsBright_sliderMoved(value);
}

void MainWindow::on_hsContrast_valueChanged(int value)
{
    on_hsContrast_sliderMoved(value);
}

void MainWindow::on_hsSat_valueChanged(int value)
{
    on_hsSat_sliderMoved(value);
}

void MainWindow::on_hsHue_valueChanged(int value)
{
    on_hsHue_sliderMoved(value);
}

void MainWindow::on_hsGamma_valueChanged(int value)
{
    on_hsGamma_sliderMoved(value);
}

void MainWindow::on_actionComics_triggered()
{
    comicCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::whitenpara(int para)
{
    //QMessageBox::information(this,"wp","wp");
    OneParameter<int> *wpara = new OneParameter<int>;
    wpara->setPara(para);
    RefPtr<OneParameter<int> > *wparasend = new RefPtr<OneParameter<int> >(wpara);
    meibaiCommand.Deref().SetParameter(RefPtrHelper::TypeCast<OneParameter<int>,ICommandParameter >(*wparasend));
    meibaiCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::whitenapply()
{
    //QMessageBox::information(this,"wa","wa");
    editApplyCommand.Deref().Exec();
    UpdateUI();
}

void MainWindow::whitencancel()
{
    //QMessageBox::information(this,"wc","wc");
    editCancleCommand.Deref().Exec();
    UpdateUI();
}
