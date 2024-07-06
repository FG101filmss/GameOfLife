#ifndef DRAWING_PANEL_H
#define DRAWING_PANEL_H

#include <wx/wx.h>

class MainWindow; // Forward declaration

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(MainWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);
    ~DrawingPanel();

private:
    void OnPaint(wxPaintEvent& event);
    void OnResize(wxSizeEvent& event); // Method to handle resize events

    int m_gridSize;

    wxDECLARE_EVENT_TABLE();
};

#endif // DRAWING_PANEL_H
