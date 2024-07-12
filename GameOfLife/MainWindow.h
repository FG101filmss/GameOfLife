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

    void UpdateStatusBar();
    void IncrementGenerationCount();
    void UpdateLivingCellCount(int count);

private:
    DrawingPanel* m_drawingPanel;
    vector<vector<bool>> m_gameBoard;
    int m_gridSize;
    int m_generationCount;
    int m_livingCellCount;

    wxStatusBar* m_statusBar;

    void OnResize(wxSizeEvent& event);
    void InitializeGrid();

    wxDECLARE_EVENT_TABLE();
};

#endif // MAIN_WINDOW_H
