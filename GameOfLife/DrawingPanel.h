#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include <wx/wx.h>

class MainWindow;

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(MainWindow* parent, wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);
    ~DrawingPanel();

    void OnPaint(wxPaintEvent& event);

private:
    wxGraphicsContext* m_gc;

    wxDECLARE_EVENT_TABLE();
};

#endif // DRAWINGPANEL_H
