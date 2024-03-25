/***************************************************************
 * Name:      MyCanvas.cpp
 * Purpose:   Code for Application Canvas
 * Author:    ZNmaster
 * Created:   2022-10-06
 * Copyright:
 * License:   WTFPL
 **************************************************************/


#include "MyCanvas.h"
#include "WallEditorMain.h"

wxBEGIN_EVENT_TABLE(MyCanvas, wxScrolledWindow)
    EVT_PAINT  (MyCanvas::OnPaint)
    EVT_MOTION (MyCanvas::OnMouseMove)
    EVT_LEFT_DOWN (MyCanvas::OnMouseDown)
    EVT_LEFT_UP (MyCanvas::OnMouseUp)
    EVT_KEY_DOWN (MyCanvas::OnKeyDown)
    EVT_KEY_UP (MyCanvas::OnKeyUp)
wxEND_EVENT_TABLE()

MyCanvas::MyCanvas(WallEditorFrame *parent)
        : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                           wxHSCROLL | wxVSCROLL)
{
    m_owner = parent;
    //m_show = File_ShowDefault;
    //m_smile_bmp = wxBitmap(smile_xpm);
    //m_std_icon = wxArtProvider::GetIcon(wxART_INFORMATION);
    m_clip = false;
    m_rubberBand = false;
    m_ShiftKeyPressed = false;
#if wxUSE_GRAPHICS_CONTEXT
    m_renderer = NULL;
    m_useAntiAliasing = true;
#endif
    m_useBuffer = false;
    m_showBBox = false;
    m_sizeDIP = wxSize(0, 0);
    toolid = 0;
}

void MyCanvas::SetMap(wxBitmap *Map_ptr)
{
    MyMap = Map_ptr;
    wxClientDC dc(this);
    PrepareDC(dc);
    m_owner->PrepareDC(dc);
    DrawDefault(dc);
}

void MyCanvas::DrawTestBrushes(wxDC& dc)
{

}

void MyCanvas::DrawTestPoly(wxDC& dc)
{

}

void MyCanvas::DrawTestLines( int x, int y, int width, wxDC &dc )
{

}

void MyCanvas::DrawCrossHair(int x, int y, int width, int heigth, wxDC &dc)
{

}

void MyCanvas::DrawDefault(wxDC& dc)
{
   dc.DrawBitmap(*MyMap, dc.FromDIP(0), dc.FromDIP(0), true);
   draw_walls(dc);
}

void MyCanvas::draw_walls(wxDC& dc)
{
        for(std::vector<LineA>::iterator it = walls.begin(); it != walls.end(); it++)
        {
            dc.DrawLine(it->x_start, it->y_start, it->x_end, it->y_end);
            if (&(*it) == selected)
            {
                dc.DrawCircle(it->x_start, it->y_start, 5);
                dc.DrawCircle(it->x_end, it->y_end, 5);
            }
        }
}

void MyCanvas::DrawText(wxDC& dc)
{

}


static const struct
{
    wxString name;
    wxRasterOperationMode rop;
} rasterOperations[] =
{
    { "wxAND",          wxAND           },
    { "wxAND_INVERT",   wxAND_INVERT    },
    { "wxAND_REVERSE",  wxAND_REVERSE   },
    { "wxCLEAR",        wxCLEAR         },
    { "wxCOPY",         wxCOPY          },
    { "wxEQUIV",        wxEQUIV         },
    { "wxINVERT",       wxINVERT        },
    { "wxNAND",         wxNAND          },
    { "wxNO_OP",        wxNO_OP         },
    { "wxOR",           wxOR            },
    { "wxOR_INVERT",    wxOR_INVERT     },
    { "wxOR_REVERSE",   wxOR_REVERSE    },
    { "wxSET",          wxSET           },
    { "wxSRC_INVERT",   wxSRC_INVERT    },
    { "wxXOR",          wxXOR           },
};

void MyCanvas::DrawImages(wxDC& dc, DrawMode mode)
{

}

void MyCanvas::DrawWithLogicalOps(wxDC& dc)
{

}

#if wxDRAWING_DC_SUPPORTS_ALPHA || wxUSE_GRAPHICS_CONTEXT
void MyCanvas::DrawAlpha(wxDC& dc)
{

}
#endif // wxDRAWING_DC_SUPPORTS_ALPHA || wxUSE_GRAPHICS_CONTEXT

#if wxUSE_GRAPHICS_CONTEXT

// modeled along Robin Dunn's GraphicsContext.py sample

void MyCanvas::DrawGraphics(wxGraphicsContext* gc)
{

}
#endif // wxUSE_GRAPHICS_CONTEXT

void MyCanvas::DrawCircles(wxDC& dc)
{

}

void MyCanvas::DrawSplines(wxDC& dc)
{

}

void MyCanvas::DrawGradients(wxDC& dc)
{

}

void MyCanvas::DrawSystemColours(wxDC& dc)
{

}

void MyCanvas::DrawDatabaseColours(wxDC& dc)
{

}

void MyCanvas::DrawColour(wxDC& dc, const wxFont& mono, wxCoord x, const wxRect& r, const wxString& colourName, const wxColour& col)
{

}

void MyCanvas::DrawRegions(wxDC& dc)
{

}

void MyCanvas::DrawRegionsHelper(wxDC& dc, wxCoord x, bool firstTime)
{

}

wxSize MyCanvas::GetDIPDrawingSize() const
{
    return m_sizeDIP;
}

void MyCanvas::Draw(wxDC& pdc)
{

#if wxUSE_GRAPHICS_CONTEXT
    wxGCDC gdc;

    if ( m_renderer )
    {
        wxGraphicsContext* context;
        if ( wxPaintDC *paintdc = wxDynamicCast(&pdc, wxPaintDC) )
        {
            context = m_renderer->CreateContext(*paintdc);
        }
        else if ( wxMemoryDC *memdc = wxDynamicCast(&pdc, wxMemoryDC) )
        {
            context = m_renderer->CreateContext(*memdc);
        }
#if wxUSE_METAFILE && defined(wxMETAFILE_IS_ENH)
        else if ( wxMetafileDC *metadc = wxDynamicCast(&pdc, wxMetafileDC) )
        {
            context = m_renderer->CreateContext(*metadc);
        }
#endif
        else
        {
            wxFAIL_MSG( "Unknown wxDC kind" );
            return;
        }

        context->SetAntialiasMode(m_useAntiAliasing ? wxANTIALIAS_DEFAULT : wxANTIALIAS_NONE);

        gdc.SetBackground(GetBackgroundColour());
        gdc.SetGraphicsContext(context);
    }

    wxDC &dc = m_renderer ? static_cast<wxDC&>(gdc) : pdc;
#else
    wxDC &dc = pdc ;
#endif

    // Adjust scrolled contents for screen drawing operations only.
    if ( wxDynamicCast(&pdc, wxBufferedPaintDC) ||
         wxDynamicCast(&pdc, wxPaintDC) )
    {
        PrepareDC(dc);
    }

    m_owner->PrepareDC(dc);

    dc.SetBackgroundMode( m_owner->m_backgroundMode );

    /*
    if ( m_owner->m_backgroundBrush.IsOk() )
        dc.SetBackground( m_owner->m_backgroundBrush );
    if ( m_owner->m_colourForeground.IsOk() )
        dc.SetTextForeground( m_owner->m_colourForeground );
    if ( m_owner->m_colourBackground.IsOk() )
        dc.SetTextBackground( m_owner->m_colourBackground );

    if ( m_owner->m_textureBackground) {
        if ( ! m_owner->m_backgroundBrush.IsOk() ) {
            dc.SetBackground(wxBrush(wxColour(0, 128, 0)));
        }
    }
    */

    dc.Clear();


    //____________________________________-
    // put draw here

    if (MyMap) {
        DrawDefault(dc);
    }



    // Adjust drawing area dimensions only if screen drawing is invoked.
    if ( wxDynamicCast(&pdc, wxBufferedPaintDC) ||
         wxDynamicCast(&pdc, wxPaintDC) )
    {
        wxCoord x0, y0;
        dc.GetDeviceOrigin(&x0, &y0);
        m_sizeDIP.x = dc.ToDIP(dc.LogicalToDeviceX(dc.MaxX()) - x0) + 1;
        m_sizeDIP.y = dc.ToDIP(dc.LogicalToDeviceY(dc.MaxY()) - y0) + 1;
    }

}


#if wxUSE_GRAPHICS_CONTEXT
void MyCanvas::UseGraphicRenderer(wxGraphicsRenderer* renderer)
{
    m_renderer = renderer;
    if (renderer)
    {
        int major, minor, micro;
        renderer->GetVersion(&major, &minor, &micro);
        wxString str = wxString::Format("Graphics renderer: %s %i.%i.%i",
                         renderer->GetName(), major, minor, micro);
        m_owner->SetStatusText(str, 1);
    }
    else
    {
        m_owner->SetStatusText(wxEmptyString, 1);
    }

    Refresh();
}
#endif // wxUSE_GRAPHICS_CONTEXT


#if wxUSE_DC_TRANSFORM_MATRIX
#include "wx/valnum.h"

class TransformDataDialog : public wxDialog
{
public:
    TransformDataDialog(wxWindow* parent, wxDouble dx, wxDouble dy, wxDouble scx, wxDouble scy, wxDouble rotAngle)
        : wxDialog(parent, wxID_ANY, "Affine transformation parameters")
        , m_dx(dx)
        , m_dy(dy)
        , m_scx(scx)
        , m_scy(scy)
        , m_rotAngle(rotAngle)
    {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        const int border = wxSizerFlags::GetDefaultBorder();
        wxFlexGridSizer* paramSizer = new wxFlexGridSizer(2, wxSize(border, border));
        paramSizer->Add(new wxStaticText(this, wxID_ANY, "Translation X:"), wxSizerFlags().CentreVertical());
        wxFloatingPointValidator<wxDouble> val_dx(1, &m_dx, wxNUM_VAL_NO_TRAILING_ZEROES);
        paramSizer->Add(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, val_dx), wxSizerFlags().CentreVertical());
        paramSizer->Add(new wxStaticText(this, wxID_ANY, "Translation Y:"), wxSizerFlags().CentreVertical());
        wxFloatingPointValidator<wxDouble> val_dy(1, &m_dy, wxNUM_VAL_NO_TRAILING_ZEROES);
        paramSizer->Add(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, val_dy), wxSizerFlags().CentreVertical());
        paramSizer->Add(new wxStaticText(this, wxID_ANY, "Scale X (0.2 - 5):"), wxSizerFlags().CentreVertical());
        wxFloatingPointValidator<wxDouble> val_scx(2, &m_scx, wxNUM_VAL_NO_TRAILING_ZEROES);
        paramSizer->Add(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, val_scx), wxSizerFlags().CentreVertical());
        paramSizer->Add(new wxStaticText(this, wxID_ANY, "Scale Y (0.2 - 5):"), wxSizerFlags().CentreVertical());
        wxFloatingPointValidator<wxDouble> val_scy(2, &m_scy, wxNUM_VAL_NO_TRAILING_ZEROES);
        paramSizer->Add(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, val_scy), wxSizerFlags().CentreVertical());
        paramSizer->Add(new wxStaticText(this, wxID_ANY, "Rotation angle (deg):"), wxSizerFlags().CentreVertical());
        wxFloatingPointValidator<wxDouble> val_rot(1, &m_rotAngle, wxNUM_VAL_NO_TRAILING_ZEROES);
        paramSizer->Add(new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, val_rot), wxSizerFlags().CentreVertical());
        sizer->Add(paramSizer, wxSizerFlags().DoubleBorder());

        wxSizer *btnSizer = CreateSeparatedButtonSizer(wxOK | wxCANCEL);
        sizer->Add(btnSizer, wxSizerFlags().Expand().Border());

        SetSizerAndFit(sizer);
    }

    virtual bool TransferDataFromWindow() wxOVERRIDE
    {
        if ( !wxDialog::TransferDataFromWindow() )
            return false;

        if ( m_scx < 0.2 || m_scx > 5.0 || m_scy < 0.2 || m_scy > 5.0 )
        {
            if ( !wxValidator::IsSilent() )
                wxBell();

            return false;
        }

        return true;
    }

    void GetTransformationData(wxDouble* dx, wxDouble* dy, wxDouble* scx, wxDouble* scy, wxDouble* rotAngle) const
    {
        if ( dx )
            *dx = m_dx;

        if ( dy )
            *dy = m_dy;

        if ( scx )
            *scx = m_scx;

        if ( scy )
            *scy = m_scy;

        if ( rotAngle )
            *rotAngle = m_rotAngle;
    }

private:
    wxDouble m_dx;
    wxDouble m_dy;
    wxDouble m_scx;
    wxDouble m_scy;
    wxDouble m_rotAngle;
};
#endif // wxUSE_DC_TRANSFORM_MATRIX

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
//#if wxUSE_STATUSBAR
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

        switch (toolid)
        {
        case 0:
        {
            wxRect newrect ( m_anchorpoint , m_currentpoint ) ;

        wxClientDC dc( this ) ;
        PrepareDC( dc ) ;

        wxDCOverlay overlaydc( m_overlay, &dc );
        overlaydc.Clear();
#ifdef __WXMAC__
        dc.SetPen( *wxGREY_PEN );
        dc.SetBrush( wxColour( 192,192,192,64 ) );
#else
        if (m_ShiftKeyPressed)
        {
            dc.SetPen( wxPen( *wxRED, 2 ) );
        }
        else
        {
           dc.SetPen( wxPen( *wxLIGHT_GREY, 2 ) );
        }

        dc.SetBrush( *wxTRANSPARENT_BRUSH );
#endif
        dc.DrawRectangle( newrect );
        break;
        }
        case 1:
            {
                wxClientDC dc( this ) ;
                PrepareDC( dc ) ;

                wxDCOverlay overlaydc( m_overlay, &dc );
                overlaydc.Clear();
#ifdef __WXMAC__
                dc.SetPen( *wxGREY_PEN );
                dc.SetBrush( wxColour( 192,192,192,64 ) );
#else
                // Set line color to cyan, fill color to yellow
                dc.SetPen(wxPen(*wxCYAN, 2, wxSOLID));
                dc.SetBrush(wxBrush(*wxYELLOW, wxSOLID));
#endif
                if (m_ShiftKeyPressed)
                {
                    unsigned int delta_x = abs(m_anchorpoint.x - m_currentpoint.x);
                    unsigned int delta_y = abs(m_anchorpoint.y - m_currentpoint.y);

                    if (delta_x <= delta_y)
                    {
                        m_currentpoint.x = m_anchorpoint.x;
                    }
                    else
                    {
                        m_currentpoint.y = m_anchorpoint.y;
                    }
                }
                dc.DrawLine(m_anchorpoint.x, m_anchorpoint.y, m_currentpoint.x, m_currentpoint.y);
            break;
            }

        }

    }
//#else
//    wxUnusedVar(event);
//#endif // wxUSE_STATUSBAR
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

    switch (toolid)
    {
        //no tool selected
        case 0:
            {
              break;
            }

        //wall tool
        case 1:
            {
                wxPoint wallstart(-1, -1);
                float dist = nearest_wallend(wallstart, m_anchorpoint);

                if (wallstart.x != -1)
                {

                    if (dist < 10)
                    {
                        m_anchorpoint = wallstart;
                    }

                }

                break;
        }
        //selection tool
        case 2:
            {
                float ref_dist = 999999999;
                void *current_selected = nullptr;

                for(std::vector<LineA>::iterator it = walls.begin(); it != walls.end(); it++)
                {
                    float dist1 = it->shortest_dist(m_anchorpoint.x, m_anchorpoint.y);

                    if(dist1 < ref_dist)
                    {
                        current_selected = &(*it);
                        ref_dist = dist1;
                    }
                }

                float select_tool_range = 150;
                if (current_selected && (ref_dist < select_tool_range))
                {
                    selected = current_selected;
                    Refresh();
                    Update();
                }
                break;
            }
        default :
            {
                break;
            }

    }

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

        switch(toolid)
        {

        //no tool selected
        case 0:
            {
            // Don't pop up the message box if nothing was actually selected.
            if ( endpoint != m_anchorpoint )
            {
                wxLogMessage("Selected rectangle from (%d, %d) to (%d, %d)",
                             m_anchorpoint.x, m_anchorpoint.y,
                             endpoint.x, endpoint.y);
                             m_ShiftKeyPressed = false;


            }
            break;
            }
        //walls tool selected
        case 1:
            {
                if (m_ShiftKeyPressed)
                {
                    unsigned int delta_x = abs(m_anchorpoint.x - endpoint.x);
                    unsigned int delta_y = abs(m_anchorpoint.y - endpoint.y);

                    if (delta_x <= delta_y)
                    {
                        endpoint.x = m_anchorpoint.x;
                    }
                    else
                    {
                        endpoint.y = m_anchorpoint.y;
                    }
                }

                LineA wall(m_anchorpoint.x, m_anchorpoint.y, endpoint.x, endpoint.y);

                walls.push_back(wall);
                std::vector<LineA>::iterator it = walls.end();
                it--;
                selected = &(*it);

                /*
                wxClientDC dc( this ) ;
                PrepareDC( dc ) ;

                wxDCOverlay overlaydc( m_overlay, &dc );
                overlaydc.Clear();
#ifdef __WXMAC__
                dc.SetPen( *wxGREY_PEN );
                dc.SetBrush( wxColour( 192,192,192,64 ) );
#else
                // Set line color to cyan, fill color to yellow
                dc.SetPen(wxPen(*wxCYAN, 2, wxSOLID));
                dc.SetBrush(wxBrush(*wxBLACK, wxSOLID));
#endif
                dc.DrawLine(m_anchorpoint.x, m_anchorpoint.y, endpoint.x, endpoint.y);
                */
                Refresh();
                Update();

                break;
            }

        }


    }
}

void MyCanvas::OnKeyDown(wxKeyEvent &event)
{
    int KeyCode = event.GetKeyCode();
    if (KeyCode == WXK_SHIFT)
        {
            m_ShiftKeyPressed = true;
        }
    else
        {
            m_ShiftKeyPressed = false;
        }
}

void MyCanvas::OnKeyUp(wxKeyEvent &event)
{

    int KeyCode = event.GetKeyCode();
    m_ShiftKeyPressed = false;

}

float MyCanvas::nearest_wallend(wxPoint& wallstart, const wxPoint& anchor)
{
    float distance = 999999999;

    for(auto wall:walls)
    {
        Line line1(wall.x_start, wall.y_start, anchor.x, anchor.y);
        Line line2(wall.x_end, wall.y_end, anchor.x, anchor.y);
        if (line1.len < distance)
        {
            distance = line1.len;
            wallstart.x = wall.x_start;
            wallstart.y = wall.y_start;
        }
        if (line2.len < distance)
        {
            distance = line2.len;
            wallstart.x = wall.x_end;
            wallstart.y = wall.y_end;
        }
    }

    return distance;
}

MyCanvas::~MyCanvas()
{
    //dtor
}
