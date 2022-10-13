/***************************************************************
 * Name:      events.cpp
 * Purpose:   Code for event handlers
 * Author:    ZNmaster
 * Created:   2022-10-05
 * Copyright:
 * License:   WTFPL
 **************************************************************/

#include "WallEditorMain.h"
#include "MyCanvas.h"


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



//MyCanvas

void MyCanvas::OnPaint(wxPaintEvent &WXUNUSED(event))
{

    if ( m_useBuffer )
    {
        wxBufferedPaintDC bpdc(this);
        Draw(bpdc);
    }
    else
    {
        wxPaintDC pdc(this);
        Draw(pdc);
    }
}


void MyCanvas::OnMouseMove(wxMouseEvent &event)
{
#if wxUSE_STATUSBAR
    {
        wxClientDC dc(this);
        PrepareDC(dc);
        m_owner->PrepareDC(dc);

        wxPoint pos = dc.DeviceToLogical(event.GetPosition());
        wxPoint dipPos = dc.ToDIP(pos);
        wxString str;
        str.Printf( "Mouse position: %d,%d", pos.x, pos.y );
        if ( pos != dipPos )
            str += wxString::Format("; DIP position: %d,%d", dipPos.x, dipPos.y);
        m_owner->SetStatusText( str );
    }

    if ( m_rubberBand )
    {
        int x,y, xx, yy ;
        event.GetPosition(&x,&y);
        CalcUnscrolledPosition( x, y, &xx, &yy );
        m_currentpoint = wxPoint( xx , yy ) ;
        wxRect newrect ( m_anchorpoint , m_currentpoint ) ;

        wxClientDC dc( this ) ;
        PrepareDC( dc ) ;

        wxDCOverlay overlaydc( m_overlay, &dc );
        overlaydc.Clear();
#ifdef __WXMAC__
        dc.SetPen( *wxGREY_PEN );
        dc.SetBrush( wxColour( 192,192,192,64 ) );
#else
        dc.SetPen( wxPen( *wxLIGHT_GREY, 2 ) );
        dc.SetBrush( *wxTRANSPARENT_BRUSH );
#endif
        dc.DrawRectangle( newrect );
    }
#else
    wxUnusedVar(event);
#endif // wxUSE_STATUSBAR
}

void MyCanvas::OnMouseDown(wxMouseEvent &event)
{
    int x,y,xx,yy ;
    event.GetPosition(&x,&y);
    CalcUnscrolledPosition( x, y, &xx, &yy );
    m_anchorpoint = wxPoint( xx , yy ) ;
    m_currentpoint = m_anchorpoint ;
    m_rubberBand = true ;
    CaptureMouse() ;
}

void MyCanvas::OnMouseUp(wxMouseEvent &event)
{
    if ( m_rubberBand )
    {
        ReleaseMouse();
        {
            wxClientDC dc( this );
            PrepareDC( dc );
            wxDCOverlay overlaydc( m_overlay, &dc );
            overlaydc.Clear();
        }
        m_overlay.Reset();
        m_rubberBand = false;

        wxPoint endpoint = CalcUnscrolledPosition(event.GetPosition());

        // Don't pop up the message box if nothing was actually selected.
        if ( endpoint != m_anchorpoint )
        {
            wxLogMessage("Selected rectangle from (%d, %d) to (%d, %d)",
                         m_anchorpoint.x, m_anchorpoint.y,
                         endpoint.x, endpoint.y);
        }
    }
}
