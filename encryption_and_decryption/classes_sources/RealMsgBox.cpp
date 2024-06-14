#include "../classes/RealMsgBox.h"
#include <wx/wx.h>

int RealMsgBox::Show(const wxString &message, const wxString &caption,
                     int style, wxWindow *parent) {
    return wxMessageBox(message, caption, style, parent);
}