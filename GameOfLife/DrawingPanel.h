#ifndef DRAWING_PANEL_H
#define DRAWING_PANEL_H

#include <wx/wx.h>
#include <vector>

using namespace std;

class MainWindow;

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(MainWindow* parent, vector<vector<bool>>& gameBoard, wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);
    ~DrawingPanel();

    void SetPanelSize(const wxSize& size);
    void ToggleCellState(int row, int col);
    void SetGridSize(int size);

private:
    vector<vector<bool>>& m_gameBoard;

    void OnPaint(wxPaintEvent& event);
    void OnResize(wxSizeEvent& event);
    void OnMouseUp(wxMouseEvent& event);

    int m_gridSize;
    vector<vector<bool>> cellStates;

    wxDECLARE_EVENT_TABLE();
};

#endif // DRAWING_PANEL_H
