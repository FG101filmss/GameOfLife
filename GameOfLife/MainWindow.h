#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <wx/wx.h>
#include "DrawingPanel.h"
#include <vector>

using namespace std;

class MainWindow : public wxFrame
{
public:
    MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~MainWindow();

private:
    DrawingPanel* m_drawingPanel;
    std::vector<std::vector<bool>> m_gameBoard;
    int m_gridSize;

    void OnResize(wxSizeEvent& event);
    void InitializeGrid();

    wxDECLARE_EVENT_TABLE();
};

#endif // MAIN_WINDOW_H
