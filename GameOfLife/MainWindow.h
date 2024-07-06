#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{
public:
    MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~MainWindow();

private:
    DrawingPanel* m_drawingPanel;

    wxDECLARE_EVENT_TABLE();
};

#endif // MAINWINDOW_H
