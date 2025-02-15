#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <wx/wx.h>
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/timer.h>
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
    // Member Variables
    DrawingPanel* m_drawingPanel;
    vector<vector<bool>> m_gameBoard;
    int m_gridSize;
    int m_generationCount;
    int m_livingCellCount;


    // UI Components
    wxStatusBar* m_statusBar;
    wxToolBar* m_toolBar;

    //Timer
    wxTimer* m_timer;
    bool m_timerRunning;
    int m_timerInterval;


    // Methods
    void SetupToolBar();
    void InitializeGrid();


    // Event Handlers
    void OnResize(wxSizeEvent& event);
    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnTrash(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);

    int CountLivingNeighbors(int row, int col);

    void NextGeneration();

    wxDECLARE_EVENT_TABLE();
};

#endif // MAIN_WINDOW_H
