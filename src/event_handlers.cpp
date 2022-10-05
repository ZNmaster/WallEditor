/***************************************************************
 * Name:      events.cpp
 * Purpose:   Code for event handlers
 * Author:    ZNmaster
 * Created:   2022-10-05
 * Copyright:
 * License:   WTFPL
 **************************************************************/

#include "WallEditorMain.h"


void WallEditorFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void WallEditorFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void WallEditorFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = "WallEditor for LemonWars v0.1";
    wxMessageBox(msg, _("Welcome to..."));
}

void WallEditorFrame::OnOpen(wxCommandEvent &event)
{
    wxString msg = "Wanna open something?";
    wxMessageBox(msg, _("Welcome to..."));
}
