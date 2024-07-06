#include "MainWindow.h"

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), m_drawingPanel(nullptr)
{
    m_drawingPanel = new DrawingPanel(this);
    Centre();
}

MainWindow::~MainWindow()
{
    if (m_drawingPanel)
        delete m_drawingPanel;
}

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
wxEND_EVENT_TABLE()
