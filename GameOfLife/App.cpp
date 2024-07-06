#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

App::App()
{
}

App::~App()
{
}

bool App::OnInit()
{
    MainWindow* mainWin = new MainWindow("Game of Life", wxPoint(50, 50), wxSize(800, 600));
    mainWin->Show(true);
    return true;
}
