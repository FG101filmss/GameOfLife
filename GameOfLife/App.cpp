#include "App.h"

wxIMPLEMENT_APP(App);

App::App() : mainWindow(nullptr)
{

}

App::~App()
{
    delete mainWindow;
}

bool App::OnInit()
{
    mainWindow = new MainWindow("Game of Life", wxPoint(0, 0), wxSize(200, 200));
    mainWindow->Show(true);

    return true;
}
