#include "DrawingPanel.h"
#include "MainWindow.h"
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

const int DrawingPanel::m_cellSize = 10;

DrawingPanel::DrawingPanel(MainWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name), m_gridSize(15)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
}

DrawingPanel::~DrawingPanel()
{

}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (!gc)
    {
        wxLogError("Failed to create wxGraphicsContext.");
        return;
    }

    gc->SetPen(*wxBLACK_PEN);

    // Set fill color (brush)
    gc->SetBrush(*wxWHITE_BRUSH);

    for (int row = 0; row < m_gridSize; ++row)
    {
        for (int col = 0; col < m_gridSize; ++col)
        {
            int x = col * m_cellSize;
            int y = row * m_cellSize;

            gc->DrawRectangle(x, y, m_cellSize, m_cellSize);
        }
    }

    delete gc;
}

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
wxEND_EVENT_TABLE()
