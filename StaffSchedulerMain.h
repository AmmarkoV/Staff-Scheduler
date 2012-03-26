/***************************************************************
 * Name:      StaffSchedulerMain.h
 * Purpose:   Defines Application Frame
 * Author:    Ammar Qammaz (ammarkov@gmail.com)
 * Created:   2011-02-14
 * Copyright: Ammar Qammaz (ammarkov.ath.cx)
 * License:
 **************************************************************/

#ifndef STAFFSCHEDULERMAIN_H
#define STAFFSCHEDULERMAIN_H

//(*Headers(StaffSchedulerFrame)
#include <wx/listctrl.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/html/htmlwin.h>
#include <wx/combobox.h>
#include <wx/statusbr.h>
//*)

class StaffSchedulerFrame: public wxFrame
{
    public:

        StaffSchedulerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~StaffSchedulerFrame();

        void ReflectSCCoreToForm();

    private:

        //(*Handlers(StaffSchedulerFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButtonAddRemoveStaffClick(wxCommandEvent& event);
        void OnButtonAddRemoveDailyJobsClick(wxCommandEvent& event);
        void OnButtonAddRemoveOneTimeJobsClick(wxCommandEvent& event);
        void OnButtonAddRemoveVacationsClick(wxCommandEvent& event);
        void OnButtonCalculateRemainingDaysClick(wxCommandEvent& event);
        void OnButtonSwapJobsDaysPeopleClick(wxCommandEvent& event);
        void OnButtonViewDayClick(wxCommandEvent& event);
        void OnButtonViewMonthClick(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnButtonPrevViewSelectionClick(wxCommandEvent& event);
        void OnButtonNextViewSelectionClick(wxCommandEvent& event);
        void OnViewSelectionSelect(wxCommandEvent& event);
        //*)

        //(*Identifiers(StaffSchedulerFrame)
        static const long ID_STATICBOX5;
        static const long ID_STATICBOX4;
        static const long ID_STATICBOX1;
        static const long ID_STATICTEXT1;
        static const long ID_STATICLINE1;
        static const long ID_STATICBOX2;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON4;
        static const long ID_LISTCTRL1;
        static const long ID_LISTCTRL2;
        static const long ID_BUTTON5;
        static const long ID_LISTCTRL4;
        static const long ID_BUTTON7;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL2;
        static const long ID_BUTTON9;
        static const long ID_BUTTON10;
        static const long ID_COMBOBOX1;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_COMBOBOX2;
        static const long ID_HTMLWINDOW1;
        static const long ID_STATICTEXT6;
        static const long ID_COMBOBOX3;
        static const long ID_BUTTON3;
        static const long ID_BUTTON6;
        static const long idMenuNewPersonDatabase;
        static const long idMenuLoadPersonDatabase;
        static const long idMenuSavePersonDatabase;
        static const long idMenuCombinePersonDatabase;
        static const long idMenuQuit;
        static const long idMenuCalculate;
        static const long idMenuViewDaily;
        static const long idMenuViewWeekly;
        static const long idMenuViewMonthly;
        static const long idMenuHelp;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(StaffSchedulerFrame)
        wxMenuItem* MenuItem8;
        wxMenuItem* MenuItem7;
        wxStaticText* ComputationStatus;
        wxStaticBox* StaticBox5;
        wxButton* ButtonAddRemoveStaff;
        wxButton* ButtonPrevViewSelection;
        wxTextCtrl* Year;
        wxMenuItem* MenuItem5;
        wxStaticText* StaticText2;
        wxMenu* Menu3;
        wxButton* Button1;
        wxButton* ButtonNextViewSelection;
        wxButton* ButtonCalculateRemainingDays;
        wxListCtrl* DailyJobList;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem11;
        wxTextCtrl* Month;
        wxStaticText* StaticText1;
        wxComboBox* ViewSelection;
        wxStaticText* StaticText3;
        wxStaticBox* StaticBox1;
        wxMenuItem* MenuItem10;
        wxButton* Button2;
        wxButton* ButtonAddRemoveDailyJobs;
        wxStaticBox* StaticBox2;
        wxMenuItem* MenuItem3;
        wxButton* ButtonSwapJobsDaysPeople;
        wxStaticText* StaticText5;
        wxButton* ButtonAddRemoveVacations;
        wxHtmlWindow* HtmlWindow1;
        wxStatusBar* StatusBar1;
        wxMenuItem* MenuItem6;
        wxListCtrl* VacationList;
        wxStaticLine* StaticLine1;
        wxComboBox* FromMonthDay;
        wxComboBox* ToMonthDay;
        wxStaticText* StaticText4;
        wxListCtrl* StaffList;
        wxStaticBox* StaticBox4;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // STAFFSCHEDULERMAIN_H
