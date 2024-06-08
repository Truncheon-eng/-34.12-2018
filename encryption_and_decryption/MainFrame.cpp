#include "classes/MainFrame.h"
#include "support_functions.h"
#include <wx/wx.h>
#include <wx/stream.h>

MainFrame::MainFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition,
	wxSize(400, 300), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {

	wxPanel* panel = new wxPanel(this, wxID_ANY);

	wxArrayString choices;
    choices.Add(wxT("Зашифрование"));
    choices.Add(wxT("Расшифрование"));

    wxButton* helpButton = new wxButton(panel, wxID_ANY, "?", wxPoint(375, 0), wxSize(20, 20));
    wxButton* sourceButton = new wxButton(panel, wxID_ANY, "i", wxPoint(355, 0), wxSize(20, 20));

    wxStaticText* label_mode = new wxStaticText(panel, wxID_ANY, wxT("Мод: "), wxPoint(10, 10), wxDefaultSize);
    choice = new wxChoice(panel, wxID_ANY, wxPoint(40, 8), wxDefaultSize, choices);
    choice->Select(0);

    wxStaticText* label_input_file = new wxStaticText(panel, wxID_ANY, wxT("Путь к исходному файлу:"), 
    	wxPoint(10, 35), wxDefaultSize);
    m_textCtrl_1 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 55), wxSize(250, -1));

    wxStaticText* label_key_file = new wxStaticText(panel, wxID_ANY, wxT("Путь к файлу с ключом:"), wxPoint(10, 75));
	m_textCtrl_2 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 95), wxSize(250, -1));

	wxStaticText* label_output_file = new wxStaticText(panel, wxID_ANY, wxT("Путь к выходному файлу:"), wxPoint(10, 115));
	m_textCtrl_3 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 135), wxSize(250, -1));

	wxButton* button = new wxButton(panel, wxID_ANY, wxT("Далее"), wxPoint(10, 160), wxSize(40, -1));

	button -> Bind(wxEVT_BUTTON, &OnButtonClicked, this);
	helpButton -> Bind(wxEVT_BUTTON, &OnHelpButtonClicked, this);
	sourceButton -> Bind(wxEVT_BUTTON, &OnSourceButtonClicked, this);
}

void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
	bool mode = choice->GetSelection();
	std::string path_to_input_file = (m_textCtrl_1 -> GetValue()).ToStdString();
	std::string path_to_key_file = (m_textCtrl_2 -> GetValue()).ToStdString();
	std::string path_to_output_file = (m_textCtrl_3 -> GetValue()).ToStdString();

	m_textCtrl_1 -> Clear();
	m_textCtrl_2 -> Clear();
	m_textCtrl_3 -> Clear();

	bool checked_input_file = path_to_input_file_is_valid(path_to_input_file);
	bool checked_keyfile_file = key_is_valid(path_to_key_file);
	bool checked_output_file = path_to_output_file_is_valid(path_to_output_file);

	if(!checked_input_file) {
		wxMessageBox(wxT("Вставьте путь к корректному исходному файлу!"), wxT("Ошибка!"), 
			wxOK | wxICON_ERROR, this);
	} else if(!checked_keyfile_file) {
		wxMessageBox(wxT("Вставьте путь к корректному файлу с ключом!"), wxT("Ошибка!"), 
			wxOK | wxICON_ERROR, this);
	} else if(!checked_output_file) {
		wxMessageBox(wxT("Вставьте путь к корректному выходному файлу!"), wxT("Ошибка!"), 
			wxOK | wxICON_ERROR, this);
	} else {
		std::pair<std::vector<uint64_t>, std::vector<char>> data_vectors = get_data(path_to_input_file);
		write_to_file(path_to_output_file, decrypt_or_encrypt(path_to_key_file, 
			mode, std::move(data_vectors.first)), data_vectors.second);
		wxMessageBox(wxString::Format(wxT("%s прошло успешно!"), choice->GetStringSelection()));
	}
}

void MainFrame::OnHelpButtonClicked(wxCommandEvent& evt) {
    std::string filePath = "../helpinfo/helpinfo.txt";
    std::string information;
    std::ifstream input_(filePath);

    std::string line;
    while (std::getline(input_, line)) {
        information += line + "\n";
    }
    input_.close();
    wxString wxInformation(information.c_str(), wxConvUTF8);

    wxMessageBox(wxInformation, wxT("Справка"), wxOK | wxICON_INFORMATION, this);
}

void MainFrame::OnSourceButtonClicked(wxCommandEvent& evt) {
    wxString url = "https://internet-law.ru/gosts/gost/70509/";
    if (!wxLaunchDefaultBrowser(url)) {
        wxMessageBox(wxT("Невозможно открыть браузер!"), wxT("Ошибка!"), wxOK | wxICON_ERROR, this);
    }
}