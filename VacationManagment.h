#ifndef VACATIONMANAGMENT_H
#define VACATIONMANAGMENT_H

//(*Headers(VacationManagment)
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class VacationManagment: public wxDialog
{
	public:

		VacationManagment(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~VacationManagment();

		//(*Declarations(VacationManagment)
		wxButton* ButtonBack;
		//*)

	protected:

		//(*Identifiers(VacationManagment)
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(VacationManagment)
		void OnButtonBackClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
