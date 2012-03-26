#ifndef WORKMANAGMENT_H
#define WORKMANAGMENT_H

//(*Headers(WorkManagment)
#include <wx/listctrl.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/combobox.h>
//*)

class WorkManagment: public wxDialog
{
	public:

		WorkManagment(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~WorkManagment();

		//(*Declarations(WorkManagment)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		wxTextCtrl* JobName;
		wxButton* ButtonRemoveJobFromPerson;
		wxTextCtrl* Year;
		wxTextCtrl* Day;
		wxStaticText* StaticText2;
		wxTextCtrl* Credits;
		wxButton* ButtonAddJobToPerson;
		wxButton* Button1;
		wxCheckBox* CheckBoxSaturday;
		wxStaticText* StaticText6;
		wxTextCtrl* HoursPerDay;
		wxListCtrl* PersonList;
		wxTextCtrl* Month;
		wxStaticText* StaticText8;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticBox* StaticBox1;
		wxButton* Button2;
		wxCheckBox* CheckBoxSunday;
		wxListCtrl* WorkList;
		wxTextCtrl* PersonsNeeded;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxButton* ButtonBack;
		wxCheckBox* CheckBoxMonday;
		wxCheckBox* CheckBoxWednesday;
		wxComboBox* TypeOfJob;
		wxCheckBox* CheckBoxFriday;
		wxRadioBox* JobType;
		wxTextCtrl* Difficulty;
		wxStaticText* StaticText4;
		wxComboBox* ComboBoxPerson;
		wxCheckBox* CheckBoxThursday;
		wxCheckBox* CheckBoxTuesday;
		//*)

	protected:

		//(*Identifiers(WorkManagment)
		static const long ID_STATICBOX1;
		static const long ID_LISTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_RADIOBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT7;
		static const long ID_TEXTCTRL4;
		static const long ID_COMBOBOX1;
		static const long ID_TEXTCTRL5;
		static const long ID_STATICTEXT8;
		static const long ID_TEXTCTRL6;
		static const long ID_STATICTEXT9;
		static const long ID_TEXTCTRL7;
		static const long ID_LISTCTRL2;
		static const long ID_BUTTON3;
		static const long ID_COMBOBOX2;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT10;
		static const long ID_TEXTCTRL8;
		static const long ID_BUTTON5;
		//*)

	private:

		//(*Handlers(WorkManagment)
		void OnButtonBackClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
