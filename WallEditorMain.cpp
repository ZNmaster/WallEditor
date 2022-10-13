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

WallEditorFrame::~WallEditorFrame()
{
    if (MyMap)
        {
            wxDELETE (MyMap);
            MyMap = nullptr;
        }

}


