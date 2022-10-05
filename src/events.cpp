/***************************************************************
 * Name:      events.cpp
 * Purpose:   Defines Event table
 * Author:    ZNmaster
 * Created:   2022-10-05
 * Copyright:
 * License:   WTFPL
 **************************************************************/

#include "WallEditorMain.h"

BEGIN_EVENT_TABLE(WallEditorFrame, wxFrame)
    EVT_CLOSE(WallEditorFrame::OnClose)
    EVT_MENU(idMenuOpen, WallEditorFrame::OnOpen)
    EVT_MENU(idMenuQuit, WallEditorFrame::OnQuit)
    EVT_MENU(idMenuAbout, WallEditorFrame::OnAbout)

END_EVENT_TABLE()
