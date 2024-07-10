#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <wx/wx.h>
#include "DrawingPanel.h"
#include <vector>

class MainWindow : public wxFrame
{
public:
    MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~MainWindow();

    void InitializeGrid();
    void SetGridSize(int size);

private:
    DrawingPanel* m_drawingPanel;
    std::vector<std::vector<bool>> m_gameBoard;
    int m_gridSize;

    void OnResize(wxSizeEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // MAIN_WINDOW_H
