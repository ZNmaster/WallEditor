/***************************************************************
 * Name:      MyCanvas.cpp
 * Purpose:   Defines Application Canvas
 * Author:    ZNmaster
 * Created:   2022-10-06
 * Copyright:
 * License:   WTFPL
 **************************************************************/


#ifndef MYCANVAS_H
#define MYCANVAS_H

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"


// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/colordlg.h"
#include "wx/image.h"
#include "wx/artprov.h"
#include "wx/dcbuffer.h"
#include "wx/dcgraph.h"
#include "wx/overlay.h"
#include "wx/graphics.h"
#include "wx/filename.h"
#include "wx/metafile.h"
#include "wx/settings.h"
#if wxUSE_SVG
#include "wx/dcsvg.h"
#endif
#if wxUSE_POSTSCRIPT
#include "wx/dcps.h"
#endif

// Standard DC supports drawing with alpha on OSX and GTK3.
#if defined(__WXOSX__) || defined(__WXGTK3__)
#define wxDRAWING_DC_SUPPORTS_ALPHA 1
#else
#define wxDRAWING_DC_SUPPORTS_ALPHA 0
#endif // __WXOSX__ || __WXGTK3__

#include "Wall.h"


class WallEditorFrame;

class MyCanvas: public wxScrolledWindow
{
public:
    MyCanvas( WallEditorFrame *parent );
    virtual ~MyCanvas();

    void OnPaint(wxPaintEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnMouseDown(wxMouseEvent &event);
    void OnMouseUp(wxMouseEvent &event);
    void OnKeyDown(wxKeyEvent &event);
    void OnKeyUp(wxKeyEvent &event);

    void ToShow(int show) { m_show = show; Refresh(); }
    int GetPage() { return m_show; }

    // set or remove the clipping region
    void Clip(bool clip) { m_clip = clip; Refresh(); }
#if wxUSE_GRAPHICS_CONTEXT
    bool HasRenderer() const { return m_renderer != NULL; }
    void UseGraphicRenderer(wxGraphicsRenderer* renderer);
    bool IsDefaultRenderer() const
    {   if ( !m_renderer ) return false;
        return m_renderer == wxGraphicsRenderer::GetDefaultRenderer();
    }
    wxGraphicsRenderer* GetRenderer() const { return m_renderer; }
    void EnableAntiAliasing(bool use) { m_useAntiAliasing = use; Refresh(); }
#endif // wxUSE_GRAPHICS_CONTEXT
    void UseBuffer(bool use) { m_useBuffer = use; Refresh(); }
    void ShowBoundingBox(bool show) { m_showBBox = show; Refresh(); }
    wxSize GetDIPDrawingSize() const;

    void Draw(wxDC& dc);

    void SetMap(wxBitmap *Map_ptr);
    wxBitmap *MyMap = nullptr;

    unsigned int toolid;

    std::vector<Wall> walls;
    std::vector<void *> undo_list;
    std::vector<unsigned int> action_log;

    //pointer to selected map object
    void *selected = nullptr;

    //drawing walls
    void draw_walls(wxDC& dc);

    //finds a distance to nearest wall end of all walls in vector
    float nearest_wallend(wxPoint& wallstart, const wxPoint& anchor);

    void undo();
    void redo();

protected:
    enum DrawMode
    {
        Draw_Normal,
        Draw_Stretch
    };

    void DrawTestLines( int x, int y, int width, wxDC &dc );
    void DrawCrossHair(int x, int y, int width, int heigth, wxDC &dc);
    void DrawTestPoly(wxDC& dc);
    void DrawTestBrushes(wxDC& dc);
    void DrawText(wxDC& dc);
    void DrawImages(wxDC& dc, DrawMode mode);
    void DrawWithLogicalOps(wxDC& dc);
#if wxDRAWING_DC_SUPPORTS_ALPHA || wxUSE_GRAPHICS_CONTEXT
    void DrawAlpha(wxDC& dc);
#endif
#if wxUSE_GRAPHICS_CONTEXT
    void DrawGraphics(wxGraphicsContext* gc);
#endif
    void DrawRegions(wxDC& dc);
    void DrawCircles(wxDC& dc);
    void DrawSplines(wxDC& dc);
    void DrawDefault(wxDC& dc);
    void DrawGradients(wxDC& dc);
    void DrawSystemColours(wxDC& dc);
    void DrawDatabaseColours(wxDC& dc);
    void DrawColour(wxDC& dc, const wxFont& mono, wxCoord x, const wxRect& r, const wxString& colourName, const wxColour& col);

    void DrawRegionsHelper(wxDC& dc, wxCoord x, bool firstTime);

private:
    WallEditorFrame *m_owner;

    int          m_show;
    wxBitmap     m_smile_bmp;
    wxIcon       m_std_icon;
    bool         m_clip;
    wxOverlay    m_overlay;
    bool         m_rubberBand;
    bool         m_ShiftKeyPressed;
    wxPoint      m_anchorpoint;
    wxPoint      m_currentpoint;
#if wxUSE_GRAPHICS_CONTEXT
    wxGraphicsRenderer* m_renderer;
    bool         m_useAntiAliasing;
#endif
    bool         m_useBuffer;
    bool         m_showBBox;
    wxSize       m_sizeDIP;

    bool delete_map_obj(void *object);

    inline void redraw_canvas();
    inline void register_deleted(void *object);
    inline void register_created(void *object);




    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};

#endif // MYCANVAS_H
