#include "MainWindow.h"

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    m_drawingPanel = new DrawingPanel(this); // Instantiate DrawingPanel with this as the parent
}

MainWindow::~MainWindow()
{
    // Destructor implementation if needed
}
