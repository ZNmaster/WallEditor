/***************************************************************
 * Name:      WallEditorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    ZNmaster
 * Created:   2022-10-05
 * Copyright:
 * License:   WTFPL
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "WallEditorMain.h"
#include "MyCanvas.h"

BEGIN_EVENT_TABLE(WallEditorFrame, wxFrame)
    EVT_CLOSE(WallEditorFrame::OnClose)
    EVT_MENU(idMenuOpen, WallEditorFrame::OnOpen)
    EVT_MENU(idMenuQuit, WallEditorFrame::OnQuit)
    EVT_MENU(idMenuAbout, WallEditorFrame::OnAbout)
    EVT_TOOL(idToolWall, WallEditorFrame::OnWall)
    EVT_TOOL(idToolPillar, WallEditorFrame::OnPillar)
    //EVT_TOOL(idToolTexture, WallEditorFrame::OnTexture)
    EVT_TOOL(idToolCharacter, WallEditorFrame::OnCharacter)
    EVT_TOOL(idToolEntity, WallEditorFrame::OnEntity)
    EVT_TOOL(idToolTrigger, WallEditorFrame::OnTrigger)

    /*
    EVT_MOTION(WallEditorFrame::OnMouseMove)
    EVT_PAINT(WallEditorFrame::OnPaint)
    #ifdef __WXGTK__
    EVT_WINDOW_CREATE(WallEditorFrame::OnWindowCreate)
    #endif
    */

END_EVENT_TABLE()

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}



WallEditorFrame::WallEditorFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
    //init
    m_xLogicalOrigin = 0;
    m_yLogicalOrigin = 0;
    m_xAxisReversed =
    m_yAxisReversed = false;
#if wxUSE_DC_TRANSFORM_MATRIX
    m_transform_dx = 0.0;
    m_transform_dy = 0.0;
    m_transform_scx = 1.0;
    m_transform_scy = 1.0;
    m_transform_rot = 0.0;
#endif // wxUSE_DC_TRANSFORM_MATRIX
    m_xUserScale = 1.0;
    m_yUserScale = 1.0;

    scroll_pix_per_unit = 10;

#if wxUSE_MENUS
    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    fileMenu->Append(idMenuOpen, _("&Open\tCtrl-O"), _("Open file"));
    mbar->Append(fileMenu, _("&File"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
    mbar->Append(helpMenu, _("&Help"));

    SetMenuBar(mbar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello Code::Blocks user!"),0);
    SetStatusText(wxbuildinfo(short_f), 1);
#endif // wxUSE_STATUSBAR


    /*
    wxPanel *panel = new wxPanel(this, -1);
    wxBoxSizer *vbox = new wxBoxSizer(wxHORIZONTAL);

    wxImage::AddHandler(new wxPNGHandler);
    wxStaticBitmap *st1 = new wxStaticBitmap(panel, wxID_ANY,
          wxBitmap("Level.png"));
    //wxStaticText *st1 =  new wxStaticText(panel, wxID_ANY,
    //    wxT("Text to DISPLAY"));

    vbox->Add(st1, 1, wxALIGN_TOP| wxALIGN_LEFT);

    vbox->Add(-1, 25);

    panel->SetSizer(vbox);

    Centre();*/

    m_canvas = new MyCanvas( this );

    //wxImage::AddHandler(new wxPNGHandler);

    wxInitAllImageHandlers();

    wxBitmap my_image;

    my_image.LoadFile("Level.png", wxBITMAP_TYPE_PNG);



    //scroll size (x -> 10 pixels per unit -> 300 units -> 3000 pixels)
    m_canvas->SetScrollbars( scroll_pix_per_unit, scroll_pix_per_unit, 100, 240 );



    SetSize(FromDIP(wxSize(800, 700)));
    Center(wxBOTH);
    CreateToolbars();


}

void WallEditorFrame::PrepareDC(wxDC& dc)
{
#if wxUSE_DC_TRANSFORM_MATRIX
    if ( dc.CanUseTransformMatrix() )
    {
        wxAffineMatrix2D mtx;
        mtx.Translate(m_transform_dx, m_transform_dy);
        mtx.Rotate(wxDegToRad(m_transform_rot));
        mtx.Scale(m_transform_scx, m_transform_scy);
        dc.SetTransformMatrix(mtx);
    }
#endif // wxUSE_DC_TRANSFORM_MATRIX
    dc.SetLogicalOrigin( dc.FromDIP(m_xLogicalOrigin), dc.FromDIP(m_yLogicalOrigin) );
    dc.SetAxisOrientation( !m_xAxisReversed, m_yAxisReversed );
    dc.SetUserScale( m_xUserScale, m_yUserScale );
    //dc.SetMapMode( m_mapMode );
}

void WallEditorFrame::CreateToolbars()
{
    wxBitmap exit(wxT("exit.PNG"), wxBITMAP_TYPE_PNG);
    wxBitmap newb(wxT("test.PNG"), wxBITMAP_TYPE_PNG);
    wxBitmap open(wxT("test.PNG"), wxBITMAP_TYPE_PNG);
    wxBitmap save(wxT("test.PNG"), wxBITMAP_TYPE_PNG);
    wxBitmap send(wxT("test.PNG"), wxBITMAP_TYPE_PNG);

    wxBitmap wall(wxT("wall.PNG"), wxBITMAP_TYPE_PNG);
    wxBitmap pillar(wxT("pillar.PNG"), wxBITMAP_TYPE_PNG);
    wxBitmap tex_sel(wxT("tex_sel.PNG"), wxBITMAP_TYPE_PNG);
    wxBitmap character(wxT("char.PNG"), wxBITMAP_TYPE_PNG);
    wxBitmap entity(wxT("entity.PNG"), wxBITMAP_TYPE_PNG);
    wxBitmap trigger(wxT("trigger.PNG"), wxBITMAP_TYPE_PNG);

    //wxPanel *panel = new wxPanel(this, -1);

    //wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    auto toolbar1 = this->CreateToolBar (wxBORDER_NONE|wxTB_FLAT|wxTB_TEXT);
    toolbar1->SetToolBitmapSize(wxSize(32, 32));
    //toolbar1->AddTool(idMenuFile_New, wxT("New"), newb);
    //toolbar1->AddTool(idMenuFile_Send, wxT("Send"), send);
    toolbar1->AddTool(idMenuOpen, wxT("Open"), open);
    //toolbar1->AddTool(idMenuFile_Save, wxT("Save"), save);
    toolbar1->AddTool(idToolWall, wxT("Wall tool"), wall);
    toolbar1->AddTool(idToolPillar, wxT("Pillar tool"), pillar);
    //toolbar1->AddTool(idToolTexture, wxT("Texture selector tool"), tex_sel);
    toolbar1->AddTool(idToolCharacter, wxT("Character tool"), character);
    toolbar1->AddTool(idToolEntity, wxT("Entity tool"), entity);
    toolbar1->AddTool(idToolTrigger, wxT("Trigger tool"), trigger);

    toolbar1->AddTool(wxID_EXIT, wxT("Exit application"), exit);

    toolbar1->Realize();

    //vbox->Add(toolbar1, 0, wxEXPAND);

        Connect(wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED,
        wxCommandEventHandler(WallEditorFrame::OnQuit));

    //panel->SetSizer(vbox);

    Centre();


    return;
}

void WallEditorFrame::OnWall(wxCommandEvent& event)
{
     if (m_canvas->toolid == 1)
     {
         m_canvas->toolid = 0;
     }
     else
     {
         m_canvas->toolid = 1;
     }
}

void WallEditorFrame::OnPillar(wxCommandEvent& event)
{
    wxLogMessage("Pillar");
}

/*void WallEditorFrame::OnTexture(wxCommandEvent& event)
{

}
*/

void WallEditorFrame::OnCharacter(wxCommandEvent& event)
{
    wxLogMessage("Character");
}

void WallEditorFrame::OnEntity(wxCommandEvent& event)
{
    wxLogMessage("Entity");
}

void WallEditorFrame::OnTrigger(wxCommandEvent& event)
{
    wxLogMessage("Trigger");
}

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

    //temp pointer to the old image to delete bitmap after a new one is set (otherwise the app will crash)
    wxBitmap *temp_bitmap = nullptr;

    if (MyMap)
    {
        temp_bitmap = MyMap;

        //m_canvas->SetMap(nullptr);
        //wxDELETE (MyMap);
        //MyMap = nullptr;
        //m_canvas->SetMap(MyMap);
    }

    bool File_loaded = false;

    MyMap = new wxBitmap;

    wxFileDialog openFileDialog(this);

    if (openFileDialog.ShowModal() == wxID_OK)
      {
          wxString fileName = openFileDialog.GetPath();
          File_loaded = MyMap->LoadFile(fileName, wxBITMAP_TYPE_ANY);
      }
    else return;

    if (File_loaded)
    {
        m_canvas->SetMap(MyMap);
        if (temp_bitmap) wxDELETE(temp_bitmap);
    }

    else return;

    int units_x = MyMap->GetWidth() / scroll_pix_per_unit;
    int units_y = MyMap->GetHeight() / scroll_pix_per_unit;

    m_canvas->SetScrollbars( scroll_pix_per_unit*m_xUserScale, scroll_pix_per_unit*m_yUserScale, units_x, units_y );


    //wxString msg = "Wanna open something?";
    //wxMessageBox(msg, _("Welcome to..."));

    //wxInitAllImageHandlers();

    //wxImage image(wxT("Level.png"), wxBITMAP_TYPE_PNG);
    //wxClientDC dc(m_canvas);

    //m_canvas->Draw(dc);


}

WallEditorFrame::~WallEditorFrame()
{
    if (MyMap)
        {
            wxDELETE (MyMap);
            MyMap = nullptr;
        }

}


