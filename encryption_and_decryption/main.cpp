#include "App.h"
#include "MainFrame.h"
#include "support_functions.h"
#include <wx/wx.h>

bool App::OnInit() {
    MainFrame *mainFrame = new MainFrame(wxT("ГОСТ Р 34.12-2018"));
    mainFrame->Show();
    mainFrame->Center();
    return true;
}

wxIMPLEMENT_APP(App); // точка входа