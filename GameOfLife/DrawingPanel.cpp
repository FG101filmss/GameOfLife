#include "DrawingPanel.h"
#include "MainWindow.h"
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

DrawingPanel::DrawingPanel(MainWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name), m_gc(nullptr)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
}

DrawingPanel::~DrawingPanel()
{
    if (m_gc)
        delete m_gc;
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    if (!m_gc)
        m_gc = wxGraphicsContext::Create(dc);

    if (!m_gc)
    {
        wxLogError("Failed to create wxGraphicsContext.");
        return;
    }

    m_gc->SetPen(*wxBLACK_PEN);

    m_gc->SetBrush(*wxWHITE_BRUSH);

    m_gc->DrawRectangle(50, 50, 100, 100);
}

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
wxEND_EVENT_TABLE()