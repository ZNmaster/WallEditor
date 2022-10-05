/***************************************************************
 * Name:      WallEditorMain.h
 * Purpose:   Defines Application Frame
 * Author:    iurii ()
 * Created:   2022-10-05
 * Copyright: iurii ()
 * License:
 **************************************************************/

#ifndef WALLEDITORMAIN_H
#define WALLEDITORMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "WallEditorApp.h"

class WallEditorFrame: public wxFrame
{
    public:
        WallEditorFrame(wxFrame *frame, const wxString& title);
        ~WallEditorFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout,
            idMenuOpen
        };

        void OnClose(wxCloseEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // WALLEDITORMAIN_H
