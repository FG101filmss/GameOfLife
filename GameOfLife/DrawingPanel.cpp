#include "DrawingPanel.h"
#include "MainWindow.h"
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

DrawingPanel::DrawingPanel(MainWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name), m_gridSize(15)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
    this->Bind(wxEVT_SIZE, &DrawingPanel::OnResize, this);
}

DrawingPanel::~DrawingPanel()
{
}

void DrawingPanel::SetSize(const wxSize& size)
{
    wxPanel::SetSize(size);
    Refresh();
}

void DrawingPanel::SetGridSize(int size)
{
    m_gridSize = size;
    Refresh();
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
    gc->SetBrush(*wxWHITE_BRUSH);

    wxSize panelSize = GetClientSize();
    int cellWidth = panelSize.x / m_gridSize;
    int cellHeight = panelSize.y / m_gridSize;

    for (int row = 0; row < m_gridSize; ++row)
    {
        for (int col = 0; col < m_gridSize; ++col)
        {
            int x = col * cellWidth;
            int y = row * cellHeight;
            gc->DrawRectangle(x, y, cellWidth, cellHeight);
        }
    }

    delete gc;
}

void DrawingPanel::OnResize(wxSizeEvent& event)
{
    Refresh();
    event.Skip();
}

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_SIZE(DrawingPanel::OnResize)
wxEND_EVENT_TABLE()
