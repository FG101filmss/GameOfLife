#include "DrawingPanel.h"
#include "MainWindow.h"
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_SIZE(DrawingPanel::OnResize)
EVT_LEFT_UP(DrawingPanel::OnMouseUp)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(MainWindow* parent, std::vector<std::vector<bool>>& gameBoard, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name), m_gridSize(15), m_gameBoard(gameBoard)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
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

    wxSize panelSize = GetClientSize();
    int cellWidth = panelSize.x / m_gridSize;
    int cellHeight = panelSize.y / m_gridSize;

    for (int row = 0; row < m_gridSize; ++row)
    {
        for (int col = 0; col < m_gridSize; ++col)
        {
            int x = col * cellWidth;
            int y = row * cellHeight;

            if (m_gameBoard[row][col])
            {
                gc->SetBrush(*wxLIGHT_GREY_BRUSH);
            }
            else
            {
                gc->SetBrush(*wxWHITE_BRUSH);
            }

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

void DrawingPanel::OnMouseUp(wxMouseEvent& event)
{
    wxPoint mousePos = event.GetPosition();
    wxSize panelSize = GetClientSize();
    int cellWidth = panelSize.x / m_gridSize;
    int cellHeight = panelSize.y / m_gridSize;

    int col = mousePos.x / cellWidth;
    int row = mousePos.y / cellHeight;

    if (row >= 0 && row < m_gridSize && col >= 0 && col < m_gridSize)
    {
        m_gameBoard[row][col] = !m_gameBoard[row][col];
        Refresh();
    }
}