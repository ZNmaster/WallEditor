/***************************************************************
 * Name:      WallEditorApp.cpp
 * Purpose:   Code for Application Class
 * Author:    iurii ()
 * Created:   2022-10-05
 * Copyright: iurii ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "WallEditorApp.h"
#include "WallEditorMain.h"

IMPLEMENT_APP(WallEditorApp);

bool WallEditorApp::OnInit()
{
    WallEditorFrame* frame = new WallEditorFrame(0L, _("Walls Editor"));

    frame->Show();

    return true;
}
