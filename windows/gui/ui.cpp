// Preconversion assistant
// Copyright (C) 2026 Red Hat Inc.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include <config.h>

#include <wx/wx.h>

class MyApp : public wxApp
{
public:
  bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
  MyFrame ();
 
private:
  void OnHello (wxCommandEvent& event);
  void OnExit (wxCommandEvent& event);
  void OnAbout (wxCommandEvent& event);
};

bool
MyApp::OnInit ()
{
  MyFrame *frame = new MyFrame();
  frame->Show();
  return true;
}

MyFrame::MyFrame ()
  : wxFrame(nullptr, wxID_ANY,
            TITLE " " PACKAGE_VERSION_FULL)
{
  wxMenu *menuFile = new wxMenu;
  menuFile->Append (wxID_EXIT);

  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append (wxID_ABOUT);

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append (menuFile, "&File");
  menuBar->Append (menuHelp, "&Help");

  SetMenuBar(menuBar);
  Bind (wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
  Bind (wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void
MyFrame::OnExit (wxCommandEvent& event)
{
    Close (true);
}

void
MyFrame::OnAbout (wxCommandEvent& event)
{
    wxMessageBox (TITLE " " PACKAGE_VERSION_FULL "\n"
                  URL,
                  TITLE,
                  wxOK | wxICON_INFORMATION);
}
