#include "VacationManagment.h"

//(*InternalHeaders(VacationManagment)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(VacationManagment)
const long VacationManagment::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(VacationManagment,wxDialog)
	//(*EventTable(VacationManagment)
	//*)
END_EVENT_TABLE()

VacationManagment::VacationManagment(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(VacationManagment)
	Create(parent, id, _("Vacation Managment"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(647,548));
	Move(wxDefaultPosition);
	ButtonBack = new wxButton(this, ID_BUTTON1, _("Πίσω"), wxPoint(504,504), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&VacationManagment::OnButtonBackClick);
	//*)
}

VacationManagment::~VacationManagment()
{
	//(*Destroy(VacationManagment)
	//*)
}


void VacationManagment::OnButtonBackClick(wxCommandEvent& event)
{
    Close();
}
