// CDDAMusicJson.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <wx/wx.h>
#include <filesystem>
#include <wx/filepicker.h>
#include <CDDAFileFncs.hpp>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    void OnClick(wxCommandEvent& event);

    void OnDir(wxFileDirPickerEvent& event);

    std::filesystem::path jsonPath;
    cdda::MusicSet ms;

    wxDECLARE_EVENT_TABLE();
};


