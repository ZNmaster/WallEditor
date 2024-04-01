/***************************************************************
 * Name:      WallEditorMain.h
 * Purpose:   Defines Application Frame
 * Author:    ZNmaster
 * Created:   2022-10-05
 * Copyright:
 * License:   WTFPL
 **************************************************************/

#ifndef WALLEDITORMAIN_H
#define WALLEDITORMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "WallEditorApp.h"

class MyCanvas;

class WallEditorFrame: public wxFrame
{
    public:

        WallEditorFrame(wxFrame *frame, const wxString& title);
        MyCanvas   *m_canvas;
        wxBitmap   *MyMap = nullptr;

        void CreateToolbars();


        void PrepareDC(wxDC& dc) wxOVERRIDE;

        int m_backgroundMode = wxBRUSHSTYLE_SOLID;


        int         m_xLogicalOrigin;
        int         m_yLogicalOrigin;
        bool        m_xAxisReversed,
                    m_yAxisReversed;
    #if wxUSE_DC_TRANSFORM_MATRIX
        wxDouble    m_transform_dx;
        wxDouble    m_transform_dy;
        wxDouble    m_transform_scx;
        wxDouble    m_transform_scy;
        wxDouble    m_transform_rot;
    #endif // wxUSE_DC_TRANSFORM_MATRIX
        double      m_xUserScale,
                    m_yUserScale;
        int scroll_pix_per_unit;



        virtual ~WallEditorFrame();

    private:


        enum
        {
            idMenuQuit = 1000,
            idMenuAbout,
            idMenuOpen,
            idMenuUndo,
            idMenuRedo,
            idToolWall,
            idToolPillar,
            //idToolTexture,
            idToolCharacter,
            idToolEntity,
            idToolTrigger
        };

        void OnClose(wxCloseEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnUndo(wxCommandEvent& event);
        void OnRedo(wxCommandEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);

        void OnWall(wxCommandEvent& event);
        void OnPillar(wxCommandEvent& event);
        //void OnTexture(wxCommandEvent& event);
        void OnCharacter(wxCommandEvent& event);
        void OnEntity(wxCommandEvent& event);
        void OnTrigger(wxCommandEvent& event);



        wxToolBar *toolbar1;

        //To redirect KEY events from Controls
        bool ProcessEvent(wxEvent& event);

        DECLARE_EVENT_TABLE()
};


#endif // WALLEDITORMAIN_H
