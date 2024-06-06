#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>

class MainFrame: public wxFrame {
public:
	MainFrame(const wxString& title);
private:
	wxTextCtrl* m_textCtrl_1;
	wxTextCtrl* m_textCtrl_2;
	wxTextCtrl* m_textCtrl_3;
	wxChoice* choice;

	void OnHelpButtonClicked(wxCommandEvent& evt);
	void OnButtonClicked(wxCommandEvent& evt);
};

#endif
