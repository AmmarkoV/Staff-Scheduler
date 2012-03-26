#ifndef STAFFMANAGMENT_H
#define STAFFMANAGMENT_H

//(*Headers(StaffManagment)
#include <wx/listctrl.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/combobox.h>
//*)

class StaffManagment: public wxDialog
{
	public:
       int last_selected_personid;
       int last_selected_jobid;
       int block_autosave;
		StaffManagment(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~StaffManagment();


		//(*Declarations(StaffManagment)
		wxStaticText* StaticText9;
		wxStaticText* StaticText2;
		wxComboBox* JobToAdd;
		wxStaticText* StaticText6;
		wxTextCtrl* TextCtrlComments;
		wxStaticText* StaticText8;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticBox* StaticBox1;
		wxComboBox* ComboBoxRank;
		wxButton* ButtonAddPerson;
		wxButton* ButtonAddJob;
		wxStaticBox* StaticBox2;
		wxButton* ButtonRemoveJobsToPersonMonth;
		wxTextCtrl* JobsPerMonth;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxButton* ButtonBack;
		wxTextCtrl* TextCtrlName;
		wxButton* ButtonRemovePerson;
		wxTextCtrl* JobToAddTimes;
		wxTextCtrl* TextCtrlSurname;
		wxListCtrl* EnlistedJobs;
		wxButton* ButtonAddJobsToPersonMonth;
		wxStaticText* StaticText4;
		wxListCtrl* StaffList;
		wxButton* ButtonRemoveJob;
		//*)

	protected:

		//(*Identifiers(StaffManagment)
		static const long ID_STATICBOX2;
		static const long ID_STATICBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_LISTCTRL1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT4;
		static const long ID_LISTCTRL3;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_BUTTON7;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL4;
		static const long ID_BUTTON8;
		static const long ID_BUTTON9;
		static const long ID_STATICTEXT6;
		static const long ID_BUTTON1;
		static const long ID_COMBOBOX2;
		static const long ID_STATICTEXT7;
		static const long ID_TEXTCTRL5;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		//*)

	private:
        void RefreshList();
        void LoadPersonIDToForm(int personid);
		//(*Handlers(StaffManagment)
		void OnButtonBackClick(wxCommandEvent& event);
		void OnStaffListBeginDrag(wxListEvent& event);
		void OnButtonAddPersonClick(wxCommandEvent& event);
		void OnButtonAddJobsToPersonMonthClick(wxCommandEvent& event);
		void OnButtonRemoveJobsToPersonMonthClick(wxCommandEvent& event);
		void OnButtonAddJobClick(wxCommandEvent& event);
		void OnButtonRemoveJobClick(wxCommandEvent& event);
		void OnEnlistedJobsBeginDrag(wxListEvent& event);
		void OnTextCtrlNameText(wxCommandEvent& event);
		void OnButtonRemovePersonClick(wxCommandEvent& event);
		void OnTextCtrlSurnameText(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
