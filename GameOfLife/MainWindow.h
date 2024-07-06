#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <wx/wx.h>
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{
public:
    MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~MainWindow();

private:
    DrawingPanel* m_drawingPanel;
};

#endif // MAIN_WINDOW_H
