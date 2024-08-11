// CDDAMusicJson.cpp : Defines the entry point for the application.
// C:/Users/danke/OneDrive/Desktop/Giochi/CDDA/dda/userdata/sound/Otopack/music

#include <wx/sizer.h>
#include <wx/button.h>
#include <CDDAMusicJson.hpp>

//nlohmann::json j2(ms);
//std::cout << std::setw(4) << j2;
wxIMPLEMENT_APP(MyApp);

auto mButton1ID = wxWindow::NewControlId();
auto mDirPickerID = wxWindow::NewControlId();

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_BUTTON(mButton1ID, MyFrame::OnClick)
	EVT_DIRPICKER_CHANGED(mDirPickerID, MyFrame::OnDir)
wxEND_EVENT_TABLE()

bool MyApp::OnInit() {
	MyFrame* frame = new MyFrame();
	frame->Show(true);
	return true;
}

MyFrame::MyFrame()
	: wxFrame{ nullptr, wxID_ANY, "Hello World" }, ms{ true } {

	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);

	
	auto mButton1 = new wxButton(this, mButton1ID, wxT("Create musicset.json"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(mButton1, 1, wxALL | wxEXPAND, 10);

	auto mDirPicker = new wxDirPickerCtrl(this, mDirPickerID, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE);
	bSizer1->Add(mDirPicker, 1, wxALL | wxEXPAND, 10);

	this->SetSizer(bSizer1);
	this->Layout();
	this->SetMaxSize(wxSize{ 400, 200 });
	this->SetMinSize(wxSize{ 400, 200 });
	this->Centre(wxBOTH);

}



void MyFrame::OnClick(wxCommandEvent& event) {

	ms.getMusic(jsonPath);
	cdda::writeMusicSet(ms, jsonPath);
	wxLogMessage("musicset.json written at '%s'", jsonPath.string());
}

void MyFrame::OnDir(wxFileDirPickerEvent& event) {
	wxLogMessage("The directory changed to '%s'", event.GetPath());
	jsonPath.assign(event.GetPath().ToStdString());
}