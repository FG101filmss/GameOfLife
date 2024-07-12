#include "MainWindow.h"
#include "DrawingPanel.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_SIZE(MainWindow::OnResize)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), m_gridSize(15)
{
    m_gameBoard.resize(m_gridSize);
    for (int i = 0; i < m_gridSize; ++i)
    {
        m_gameBoard[i].resize(m_gridSize, false);
    }

    m_drawingPanel = new DrawingPanel(this, m_gameBoard);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_drawingPanel, 1, wxEXPAND | wxALL, 0);

    this->SetSizer(sizer);
    this->Layout();

    this->Bind(wxEVT_SIZE, &MainWindow::OnResize, this);

    InitializeGrid();
}

MainWindow::~MainWindow()
{

}

void MainWindow::OnResize(wxSizeEvent& event)
{
    wxSize newSize = this->GetSize();
    m_drawingPanel->SetSize(newSize);
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