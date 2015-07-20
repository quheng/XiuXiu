#pragma once
#include <QImage>
#include <QString>
#include <model/model.h>
#include "common/common.h"
#include "command/opencommand.h"
#include "command/faceliftcommand.h"
#include "command/graycommand.h"
#include "command/undocommand.h"
#include "command/histcommand.h"
#include "command/crystalcommand.h"
#include "command/facewhitecommand.h"
#include "command/reancientcommand.h"
#include "command/pencilcommand.h"
#include "command/gausscommand.h"
#include "command/horizontalcommand.h"
#include "command/verticalcommand.h"
#include "command/clockrotcommand.h"
#include "command/anticlorotcommand.h"
#include "command/luminandcontras.h"
#include "command/gammacommand.h"
#include "command/hueandsaturation.h"
#include "command/doadjustcommand.h"
#include "command/docancelcommand.h"
#include "command/redocommand.h"
#include "command/edgecommand.h"
#include "command/acgcommand.h"


class ViewModel
           :public OpenCommand<ViewModel>
           ,public FaceLiftCommand<ViewModel>
           ,public GrayCommand<ViewModel>
           ,public UndoCommand<ViewModel>
           ,public HistCommand<ViewModel>
           ,public CrystalCommand<ViewModel>
           ,public FaceWhiteCommand<ViewModel>
           ,public ReancientCommand<ViewModel>
           ,public PencilCommand<ViewModel>
           ,public GaussCommand<ViewModel>
           ,public HorizontalCommand<ViewModel>
           ,public VerticalCommand<ViewModel>
           ,public ClockRotCommand<ViewModel>
           ,public AntiCloRotCommand<ViewModel>
           ,public LuminContrasCommand<ViewModel>
           ,public GammaCommand<ViewModel>
           ,public HueSaturaCommand<ViewModel>
           ,public DoAdjustCommand<ViewModel>
           ,public DoCancelCommand<ViewModel>
           ,public RedoCommand<ViewModel>
           ,public EdgeCommand<ViewModel>
           ,public AcgCommand<ViewModel>

{
private:
    QImage image;
    CQHistogram hist;
    RefPtr<ImageModel> m_ImageModel;

public:
    ViewModel();
    void setImageModelRef(const RefPtr<ImageModel>& imageModel) throw();

    RefPtr<QImage> getQImageRef();
    RefPtr<CQHistogram> getHistRef();
    RefPtr<ImageModel> getImageModelRef() throw();

    QImage& getQImage();
    void setQImage(const QImage& img);

    CQHistogram& getHist();
    void setHist(CQHistogram& value);
};

ViewModel::ViewModel()
       :OpenCommand<ViewModel>(this)
       ,FaceLiftCommand<ViewModel>(this)
       ,GrayCommand<ViewModel>(this)
       ,UndoCommand<ViewModel>(this)
       ,HistCommand<ViewModel>(this)
       ,CrystalCommand<ViewModel>(this)
       ,FaceWhiteCommand<ViewModel>(this)
       ,ReancientCommand<ViewModel>(this)
       ,PencilCommand<ViewModel>(this)
       ,GaussCommand<ViewModel>(this)
       ,HorizontalCommand<ViewModel>(this)
       ,VerticalCommand<ViewModel>(this)
       ,ClockRotCommand<ViewModel>(this)
       ,AntiCloRotCommand<ViewModel>(this)
       ,LuminContrasCommand<ViewModel>(this)
       ,GammaCommand<ViewModel>(this)
       ,HueSaturaCommand<ViewModel>(this)
       ,DoAdjustCommand<ViewModel>(this)
       ,DoCancelCommand<ViewModel>(this)
       ,RedoCommand<ViewModel>(this)
       ,EdgeCommand<ViewModel>(this)
       ,AcgCommand<ViewModel>(this)
{}

void ViewModel::setImageModelRef(const RefPtr<ImageModel>& imageModel) throw()
{
    m_ImageModel = imageModel;
}

RefPtr<ImageModel> ViewModel::getImageModelRef() throw()
{
    return m_ImageModel;
}

inline RefPtr<QImage> ViewModel::getQImageRef(){
    return RefPtr<QImage>(&image);
}

RefPtr<CQHistogram> ViewModel::getHistRef(){
    return RefPtr<CQHistogram>(&hist);
}

inline void ViewModel:: setQImage(const QImage& img){
    image = img;
}

inline QImage& ViewModel::getQImage(){
    return image;
}

inline CQHistogram& ViewModel::getHist(){
    return hist;
}

void ViewModel::setHist(CQHistogram& value){
    hist = value;
}
