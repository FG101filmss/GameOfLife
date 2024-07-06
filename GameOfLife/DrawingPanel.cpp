#include "DrawingPanel.h"
#include "MainWindow.h"
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

DrawingPanel::DrawingPanel(MainWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name), m_gridSize(15) // Default grid size
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
    this->Bind(wxEVT_SIZE, &DrawingPanel::OnResize, this); // Bind resize event
}

DrawingPanel::~DrawingPanel()
{
    // Destructor implementation if needed
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear(); // Clear the drawing context

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (!gc)
    {
        wxLogError("Failed to create wxGraphicsContext.");
        return;
    }

    // Set outline color (pen)
    gc->SetPen(*wxBLACK_PEN); // Black pen

    // Set fill color (brush)
    gc->SetBrush(*wxWHITE_BRUSH); // White brush

    // Calculate cell width and height
    wxSize panelSize = GetClientSize(); // Get the size of the DrawingPanel
    int cellWidth = panelSize.x / m_gridSize; // Calculate cell width
    int cellHeight = panelSize.y / m_gridSize; // Calculate cell height

    // Draw grid of rectangles
    for (int row = 0; row < m_gridSize; ++row)
    {
        for (int col = 0; col < m_gridSize; ++col)
        {
            int x = col * cellWidth; // Calculate x-coordinate
            int y = row * cellHeight; // Calculate y-coordinate

            // Draw rectangle
            gc->DrawRectangle(x, y, cellWidth, cellHeight);
        }
    }

    delete gc; // Clean up wxGraphicsContext
}

void DrawingPanel::OnResize(wxSizeEvent& event)
{
    Refresh(); // Refresh the panel to trigger a repaint
    event.Skip(); // Continue processing the event
}

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_SIZE(DrawingPanel::OnResize)
wxEND_EVENT_TABLE()
