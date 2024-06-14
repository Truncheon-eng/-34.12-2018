#include "App.h"
#include "MainFrame.h"
#include "RealMsgBox.h"
#include "support_functions.h"
#include <wx/wx.h>

bool App::OnInit() {
    RealMsgBox msg;
    MainFrame *mainFrame = new MainFrame(wxT("ГОСТ Р 34.12-2018"), &msg);
    mainFrame->Show();
    mainFrame->Center();
    return true;
}

wxIMPLEMENT_APP(App); // точка входа