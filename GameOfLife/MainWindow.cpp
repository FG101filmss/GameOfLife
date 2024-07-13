// Header Files
#include "MainWindow.h"
#include "DrawingPanel.h"
#include <wx/artprov.h>

// XPM Files
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"

const int playButtonID = wxID_HIGHEST + 10000;
const int pauseButtonID = wxID_HIGHEST + 10002;
const int nextButtonID = wxID_HIGHEST + 10003;
const int trashButtonID = wxID_HIGHEST + 10004;

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_SIZE(MainWindow::OnResize)
    EVT_MENU(playButtonID, MainWindow::OnPlay)
    EVT_MENU(pauseButtonID, MainWindow::OnPause)
    EVT_MENU(nextButtonID, MainWindow::OnNext)
    EVT_MENU(trashButtonID, MainWindow::OnTrash)
    EVT_TIMER(wxID_ANY, MainWindow::OnTimer)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), m_gridSize(50), m_generationCount(0), m_livingCellCount(0), m_timerInterval(50)
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

    m_timer = new wxTimer(this, wxID_ANY);

    m_timer->Start(m_timerInterval);

    Bind(wxEVT_TIMER, &MainWindow::OnTimer, this, wxID_ANY);
}

MainWindow::~MainWindow()
{
    if (m_timer->IsRunning())
    {
        m_timer->Stop();
    }
}

void MainWindow::OnTimer(wxTimerEvent& event)
{
    NextGeneration();
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

    Bind(wxEVT_TOOL, &MainWindow::OnPlay, this, playButtonID);
    Bind(wxEVT_TOOL, &MainWindow::OnPause, this, pauseButtonID);
    Bind(wxEVT_TOOL, &MainWindow::OnNext, this, nextButtonID);
    Bind(wxEVT_TOOL, &MainWindow::OnTrash, this, trashButtonID);
}

void MainWindow::OnPlay(wxCommandEvent& event)
{
    if (!m_timer->IsRunning())
    {
        m_timer->Start(m_timerInterval);
    }
}

void MainWindow::OnPause(wxCommandEvent& event)
{
    if (m_timer->IsRunning())
    {
        m_timer->Stop();
    }
}

void MainWindow::OnNext(wxCommandEvent& event)
{
    NextGeneration();
}

void MainWindow::OnTrash(wxCommandEvent& event)
{
    for (int i = 0; i < m_gridSize; ++i)
    {
        for (int j = 0; j < m_gridSize; ++j)
        {
            m_gameBoard[i][j] = false;
        }
    }

    m_generationCount = 0;
    m_livingCellCount = 0;

    UpdateStatusBar();

    m_drawingPanel->Refresh();
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

void MainWindow::NextGeneration()
{
    vector<vector<bool>> sandbox(m_gridSize, vector<bool>(m_gridSize, false));

    int newLivingCellCount = 0;
    for (int row = 0; row < m_gridSize; ++row)
    {
        for (int col = 0; col < m_gridSize; ++col)
        {
            int livingNeighbors = 0;

            for (int drow = -1; drow <= 1; ++drow)
            {
                for (int dcol = -1; dcol <= 1; ++dcol)
                {
                    if (drow == 0 && dcol == 0)
                        continue;

                    int neighborRow = row + drow;
                    int neighborCol = col + dcol;

                    if (neighborRow >= 0 && neighborRow < m_gridSize &&
                        neighborCol >= 0 && neighborCol < m_gridSize &&
                        m_gameBoard[neighborRow][neighborCol])
                    {
                        livingNeighbors++;
                    }
                }
            }

            if (m_gameBoard[row][col])
            {
                if (livingNeighbors < 2 || livingNeighbors > 3)
                {
                    sandbox[row][col] = false;
                }
                else
                {
                    sandbox[row][col] = true;
                    newLivingCellCount++;
                }
            }
            else
            {
                if (livingNeighbors == 3)
                {
                    sandbox[row][col] = true;
                    newLivingCellCount++;
                }
                else
                {
                    sandbox[row][col] = false;
                }
            }
        }
    }

    m_gameBoard.swap(sandbox);

    m_generationCount++;
    m_livingCellCount = newLivingCellCount;

    UpdateStatusBar();
    m_drawingPanel->Refresh();
}