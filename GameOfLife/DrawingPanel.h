#ifndef DRAWING_PANEL_H
#define DRAWING_PANEL_H

#include <wx/wx.h>

class MainWindow;

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(MainWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);
    ~DrawingPanel();

    void SetSize(const wxSize& size);
    void SetGridSize(int size);

private:
    int m_gridSize;

    void OnPaint(wxPaintEvent& event);
    void OnResize(wxSizeEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // DRAWING_PANEL_H
