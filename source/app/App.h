#pragma once
#include "model/model.h"
#include "viewmodel/ViewModel.h"

template <class TMainWnd>
class App
{
public:
     App(TMainWnd* p):m_mainWindow(p)
     {
     }
     void Initialize()
     {
      	// load
        m_vmdl.setImageModelRef(RefPtr<ImageModel>(&imageModel));
      	// bind
        //image
        m_mainWindow->setImageRef(m_vmdl.getQImageRef());
        m_mainWindow->setHistRef(m_vmdl.getHistRef());

      	// notification
        //m_vmdl.AddNotification(m_p->get_Notification());

      	// command
        //open
        m_mainWindow->setOpenCommand(m_vmdl.getOpenCommandRef());
        //facelift
        m_mainWindow->setFaceLiftCommand(m_vmdl.getFaceLiftCommandRef());
        //gray
        m_mainWindow->setGrayCommand(m_vmdl.getGrayCommandRef());
        //undo
        m_mainWindow->setUndoCommand(m_vmdl.getUndoCommandRef());
        //hist
        m_mainWindow->setHistCommand(m_vmdl.getHistCommandRef());
        //meibai
        m_mainWindow->setMeibaiCommand(m_vmdl.getFaceWhiteCommandRef());
        //Crystal
        m_mainWindow->setCrystalCommand(m_vmdl.getCrystalCommandRef());
        //reancient
        m_mainWindow->setAncientCommand(m_vmdl.getReancientCommandRef());
        //pencil
        m_mainWindow->setPencilCommand(m_vmdl.getPencilCommandRef());
        //gauss
        m_mainWindow->setGaussCommand(m_vmdl.getGaussCommandRef());
        //HorizontalFlip
        m_mainWindow->setHorizontalFlipCommand(m_vmdl.getHorizontalCommandRef());
        //VerticleFlip
        m_mainWindow->setVerticleFlipCommand(m_vmdl.getVerticalCommandRef());
        //ClockwiseRot
        m_mainWindow->setClockwiseCommand(m_vmdl.getClockRotCommandRef());
        //AntiClockwiseRot
        m_mainWindow->setCounterclockwiseCommand(m_vmdl.getAntiCloRotCommandRef());
        //EditBriConCommand
        m_mainWindow->setEditBriConCommand(m_vmdl.getLuminContrasCommandRef());
        //EditHueSatCommand
        m_mainWindow->setEditHueSatCommand(m_vmdl.getHueSaturaCommandRef());
        //EditGammaCommand
        m_mainWindow->setEditGammaCommand(m_vmdl.getGammaCommandRef());
        //EditApplyCommand
        m_mainWindow->setEditApplyCommand(m_vmdl.getDoAdjustCommandRef());
        //EditCancelCommand
        m_mainWindow->setEditCancleCommand(m_vmdl.getDoCancelCommandRef());
        //setRedoCommand
        m_mainWindow->setRedoCommand(m_vmdl.getRedoCommandRef());
        //setEdgeCommand
        m_mainWindow->setEdgeTryCommand(m_vmdl.getEdgeCommandRef());
        //setComicCommand
        m_mainWindow->setComicCommand(m_vmdl.getAcgCommandRef());


     }

private:
    TMainWnd*  m_mainWindow;
    ImageModel imageModel;
    ViewModel  m_vmdl;
};
 
