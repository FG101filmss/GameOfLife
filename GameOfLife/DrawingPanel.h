#ifndef DRAWING_PANEL_H
#define DRAWING_PANEL_H

#include <wx/wx.h>
#include <vector>

using namespace std;

class MainWindow;

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(MainWindow* parent, std::vector<std::vector<bool>>& gameBoard, wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);
    ~DrawingPanel();

    void SetSize(const wxSize& size);
    void SetGridSize(int size);

private:
    int m_gridSize;
    std::vector<std::vector<bool>>& m_gameBoard;

    void OnPaint(wxPaintEvent& event);
    void OnResize(wxSizeEvent& event);
    void OnMouseClick(wxMouseEvent& event);
    void OnMouseUp(wxMouseEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // DRAWING_PANEL_H
