/***************************************************************
 * Name:      events.cpp
 * Purpose:   Defines Event table
 * Author:    ZNmaster
 * Created:   2022-10-05
 * Copyright:
 * License:   WTFPL
 **************************************************************/

#include "WallEditorMain.h"
#include "MyCanvas.h"

// ----------------------------------------------------------------------------
// MyCanvas
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them.
wxBEGIN_EVENT_TABLE(MyCanvas, wxScrolledWindow)
    EVT_PAINT  (MyCanvas::OnPaint)
    EVT_MOTION (MyCanvas::OnMouseMove)
    EVT_LEFT_DOWN (MyCanvas::OnMouseDown)
    EVT_LEFT_UP (MyCanvas::OnMouseUp)
wxEND_EVENT_TABLE()


BEGIN_EVENT_TABLE(WallEditorFrame, wxFrame)
    EVT_CLOSE(WallEditorFrame::OnClose)
    EVT_MENU(idMenuOpen, WallEditorFrame::OnOpen)
    EVT_MENU(idMenuQuit, WallEditorFrame::OnQuit)
    EVT_MENU(idMenuAbout, WallEditorFrame::OnAbout)

    /*
    EVT_MOTION(WallEditorFrame::OnMouseMove)
    EVT_PAINT(WallEditorFrame::OnPaint)
    #ifdef __WXGTK__
    EVT_WINDOW_CREATE(WallEditorFrame::OnWindowCreate)
    #endif
    */

END_EVENT_TABLE()


