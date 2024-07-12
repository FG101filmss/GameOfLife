// Header Files
#include "MainWindow.h"
#include "DrawingPanel.h"
#include <wx/artprov.h>
#include <vector>

// XPM Files
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"

const int playButtonID = wxID_HIGHEST + 1;
const int pauseButtonID = wxID_HIGHEST + 2;
const int nextButtonID = wxID_HIGHEST + 3;
const int trashButtonID = wxID_HIGHEST + 4;

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_SIZE(MainWindow::OnResize)
    EVT_MENU(playButtonID, MainWindow::OnPlay)
    EVT_MENU(pauseButtonID, MainWindow::OnPause)
    EVT_MENU(nextButtonID, MainWindow::OnNext)
    EVT_MENU(trashButtonID, MainWindow::OnTrash)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), m_gridSize(15), m_generationCount(0), m_livingCellCount(0)
{
    m_gameBoard.resize(m_gridSize);
    for (int i = 0; i < m_gridSize; ++i)
    {
        m_gameBoard[i].resize(m_gridSize, false);
    }

    m_drawingPanel = new DrawingPanel(this, m_gameBoard);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_drawingPanel, 1, wxEXPAND | wxALL, 0);
    SetSizer(sizer);

    InitializeGrid();
    m_statusBar = CreateStatusBar();
    UpdateStatusBar();
    SetupToolBar();
    Layout();
}

MainWindow::~MainWindow()
{

}

void MainWindow::OnResize(wxSizeEvent& event)
{
    wxSize newSize = GetSize();
    if (m_drawingPanel)
    {
        m_drawingPanel->SetSize(newSize);
    }
    event.Skip();
}

void MainWindow::InitializeGrid()
{
    m_gameBoard.resize(m_gridSize);
    for (int i = 0; i < m_gridSize; ++i)
    {
        m_gameBoard[i].resize(m_gridSize, false);
    }

    m_drawingPanel->SetGridSize(m_gridSize);
}

void MainWindow::UpdateStatusBar()
{
    wxString status;
    status.Printf("Generation: %d, Living Cells: %d", m_generationCount, m_livingCellCount);
    SetStatusText(status, 0);
}

void MainWindow::IncrementGenerationCount()
{
    m_generationCount++;
    UpdateStatusBar();
}

void MainWindow::UpdateLivingCellCount(int count)
{
    m_livingCellCount = count;
    UpdateStatusBar();
}
// TOOL BAR, BUTTONS AND ICONS

void MainWindow::SetupToolBar()
{
    m_toolBar = CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL);

    // Buttons
    wxBitmap playIcon(play_xpm);
    wxBitmap pauseIcon(pause_xpm);
    wxBitmap nextIcon(next_xpm);
    wxBitmap trashIcon(trash_xpm);

    m_toolBar->AddTool(playButtonID, "Start", playIcon);
    m_toolBar->AddTool(pauseButtonID, "Pause", pauseIcon);
    m_toolBar->AddTool(nextButtonID, "Next", nextIcon);
    m_toolBar->AddTool(trashButtonID, "Clear", trashIcon);

    m_toolBar->Realize();
}

void MainWindow::OnPlay(wxCommandEvent& event)
{
    wxMessageBox("Start button clicked!");
}

void MainWindow::OnPause(wxCommandEvent& event)
{
    wxMessageBox("Pause button clicked!");
}

void MainWindow::OnNext(wxCommandEvent& event)
{
    wxMessageBox("Next button clicked!");
}

void MainWindow::OnTrash(wxCommandEvent& event)
{
    wxMessageBox("Trash button clicked!");
}

int MainWindow::CountLivingNeighbors(int row, int col)
{
    int livingNeighbors = 0;
    int startRow = max(row - 1, 0);
    int endRow = min(row + 1, m_gridSize - 1);
    int startCol = max(col - 1, 0);
    int endCol = min(col + 1, m_gridSize - 1);

    for (int r = startRow; r <= endRow; ++r)
    {
        for (int c = startCol; c <= endCol; ++c)
        {
            if ((r != row || c != col) && r >= 0 && r < m_gridSize && c >= 0 && c < m_gridSize && m_gameBoard[r][c])
            {
                ++livingNeighbors;
            }
        }
    }
    return livingNeighbors;
}