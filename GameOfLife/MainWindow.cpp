#include "MainWindow.h"

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), m_gridSize(15)
{
    m_drawingPanel = new DrawingPanel(this);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_drawingPanel, 1, wxEXPAND | wxALL, 0);
    SetSizer(sizer);

    InitializeGrid();

    Bind(wxEVT_SIZE, &MainWindow::OnResize, this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::InitializeGrid()
{
    m_gameBoard.resize(m_gridSize);
    for (int i = 0; i < m_gridSize; ++i) {
        m_gameBoard[i].resize(m_gridSize, false);
    }
    m_drawingPanel->SetGridSize(m_gridSize);
}

void MainWindow::SetGridSize(int size)
{
    m_gridSize = size;
    InitializeGrid();
}

void MainWindow::OnResize(wxSizeEvent& event)
{
    wxSize newSize = GetSize();
    m_drawingPanel->SetSize(newSize);
    event.Skip();
}

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnResize)
wxEND_EVENT_TABLE()
