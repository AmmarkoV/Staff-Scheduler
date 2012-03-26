/***************************************************************
 * Name:      StaffSchedulerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Ammar Qammaz (ammarkov@gmail.com)
 * Created:   2011-02-14
 * Copyright: Ammar Qammaz (ammarkov.ath.cx)
 * License:
 **************************************************************/

#include "StaffSchedulerMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(StaffSchedulerFrame)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/wxhtml.h>

#include "WorkManagment.h"
#include "StaffManagment.h"
#include "ScheduleCreator/ScheduleCreator.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(StaffSchedulerFrame)
const long StaffSchedulerFrame::ID_STATICBOX5 = wxNewId();
const long StaffSchedulerFrame::ID_STATICBOX4 = wxNewId();
const long StaffSchedulerFrame::ID_STATICBOX1 = wxNewId();
const long StaffSchedulerFrame::ID_STATICTEXT1 = wxNewId();
const long StaffSchedulerFrame::ID_STATICLINE1 = wxNewId();
const long StaffSchedulerFrame::ID_STATICBOX2 = wxNewId();
const long StaffSchedulerFrame::ID_BUTTON1 = wxNewId();
const long StaffSchedulerFrame::ID_BUTTON2 = wxNewId();
const long StaffSchedulerFrame::ID_BUTTON4 = wxNewId();
const long StaffSchedulerFrame::ID_LISTCTRL1 = wxNewId();
const long StaffSchedulerFrame::ID_LISTCTRL2 = wxNewId();
const long StaffSchedulerFrame::ID_BUTTON5 = wxNewId();
const long StaffSchedulerFrame::ID_LISTCTRL4 = wxNewId();
const long StaffSchedulerFrame::ID_BUTTON7 = wxNewId();
const long StaffSchedulerFrame::ID_STATICTEXT2 = wxNewId();
const long StaffSchedulerFrame::ID_TEXTCTRL1 = wxNewId();
const long StaffSchedulerFrame::ID_STATICTEXT3 = wxNewId();
const long StaffSchedulerFrame::ID_TEXTCTRL2 = wxNewId();
const long StaffSchedulerFrame::ID_BUTTON9 = wxNewId();
const long StaffSchedulerFrame::ID_BUTTON10 = wxNewId();
const long StaffSchedulerFrame::ID_COMBOBOX1 = wxNewId();
const long StaffSchedulerFrame::ID_STATICTEXT4 = wxNewId();
const long StaffSchedulerFrame::ID_STATICTEXT5 = wxNewId();
const long StaffSchedulerFrame::ID_COMBOBOX2 = wxNewId();
const long StaffSchedulerFrame::ID_HTMLWINDOW1 = wxNewId();
const long StaffSchedulerFrame::ID_STATICTEXT6 = wxNewId();
const long StaffSchedulerFrame::ID_COMBOBOX3 = wxNewId();
const long StaffSchedulerFrame::ID_BUTTON3 = wxNewId();
const long StaffSchedulerFrame::ID_BUTTON6 = wxNewId();
const long StaffSchedulerFrame::idMenuNewPersonDatabase = wxNewId();
const long StaffSchedulerFrame::idMenuLoadPersonDatabase = wxNewId();
const long StaffSchedulerFrame::idMenuSavePersonDatabase = wxNewId();
const long StaffSchedulerFrame::idMenuCombinePersonDatabase = wxNewId();
const long StaffSchedulerFrame::idMenuQuit = wxNewId();
const long StaffSchedulerFrame::idMenuCalculate = wxNewId();
const long StaffSchedulerFrame::idMenuViewDaily = wxNewId();
const long StaffSchedulerFrame::idMenuViewWeekly = wxNewId();
const long StaffSchedulerFrame::idMenuViewMonthly = wxNewId();
const long StaffSchedulerFrame::idMenuHelp = wxNewId();
const long StaffSchedulerFrame::idMenuAbout = wxNewId();
const long StaffSchedulerFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(StaffSchedulerFrame,wxFrame)
    //(*EventTable(StaffSchedulerFrame)
    //*)
END_EVENT_TABLE()


inline wxString _U(const char String[] = "")
{
  return wxString(String, wxConvUTF8);
}


void StaffSchedulerFrame::ReflectSCCoreToForm()
{
  StaffList->DeleteAllItems();
  DailyJobList->DeleteAllItems();
  VacationList->DeleteAllItems();

  wxString query_wxstr;
  int personid=1;
  while ( personid < SC_GetTotalPersons() )
   {
        query_wxstr.clear();
        query_wxstr<<_U(SC_GetPersons_Str(personid,0));
        long tmp = StaffList->InsertItem(personid,query_wxstr, 0);
        StaffList->SetItemData(tmp, personid);

        query_wxstr.clear();
        query_wxstr<<_U(SC_GetPersons_Str(personid,1));
        StaffList->SetItem(tmp, 1, query_wxstr);

       ++personid;
   }


  //DailyJobList->ClearAll();
  int jobid=1;
  while ( jobid < SC_GetTotalJobs() )
   {
       query_wxstr.clear();
       query_wxstr<<_U(SC_GetJobs_Str(jobid,0));
       long tmp = DailyJobList->InsertItem(jobid,query_wxstr, 0);
       DailyJobList->SetItemData(tmp, jobid);

       query_wxstr.clear();
       //_U(SC_GetPersons_Str(personid,1));
       query_wxstr<<wxT("1");
       DailyJobList->SetItem(tmp, 1, query_wxstr);

       ++jobid;
   }

}

StaffSchedulerFrame::StaffSchedulerFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(StaffSchedulerFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;
    wxMenuItem* MenuItem9;

    Create(parent, id, _("Staff Scheduler "), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(1024,591));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    StaticBox5 = new wxStaticBox(this, ID_STATICBOX5, _("Ημερομηνίες Υπολογισμού"), wxPoint(272,424), wxSize(240,128), 0, _T("ID_STATICBOX5"));
    StaticBox4 = new wxStaticBox(this, ID_STATICBOX4, _("Άδειες"), wxPoint(24,368), wxSize(240,184), 0, _T("ID_STATICBOX4"));
    StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Ανθρώπινο Δυναμικό"), wxPoint(16,8), wxSize(248,168), 0, _T("ID_STATICBOX1"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Μήνας Απρίλιος , απομένουν 0 ημέρες "), wxPoint(280,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(16,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxPoint(272,32), wxSize(728,1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("Ημερήσιες Εργασίες"), wxPoint(16,192), wxSize(248,184), 0, _T("ID_STATICBOX2"));
    ButtonAddRemoveStaff = new wxButton(this, ID_BUTTON1, _("Προσθαφαίρεση Προσωπικού"), wxPoint(24,160), wxSize(232,29), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    ButtonAddRemoveDailyJobs = new wxButton(this, ID_BUTTON2, _("Προσθαφαίρεση Εργασιών"), wxPoint(24,336), wxSize(232,29), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    ButtonAddRemoveVacations = new wxButton(this, ID_BUTTON4, _("Προσθαφαίρεση Αδειών"), wxPoint(32,512), wxSize(224,29), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    StaffList = new wxListCtrl(this, ID_LISTCTRL1, wxPoint(24,24), wxSize(232,136), wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL1"));
    DailyJobList = new wxListCtrl(this, ID_LISTCTRL2, wxPoint(24,208), wxSize(232,128), wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL2"));
    ButtonCalculateRemainingDays = new wxButton(this, ID_BUTTON5, _("Κατανομή Εργασιών"), wxPoint(536,488), wxSize(472,32), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    wxFont ButtonCalculateRemainingDaysFont(17,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonCalculateRemainingDays->SetFont(ButtonCalculateRemainingDaysFont);
    VacationList = new wxListCtrl(this, ID_LISTCTRL4, wxPoint(32,384), wxSize(224,128), wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL4"));
    ButtonSwapJobsDaysPeople = new wxButton(this, ID_BUTTON7, _("Εναλλαγή Εργασιών / Ημερών / Ατόμων"), wxPoint(536,456), wxSize(472,32), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    wxFont ButtonSwapJobsDaysPeopleFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonSwapJobsDaysPeople->SetFont(ButtonSwapJobsDaysPeopleFont);
    ComputationStatus = new wxStaticText(this, ID_STATICTEXT2, _("Δεν έχει γίνει κατανομή εργασιών.."), wxPoint(672,520), wxSize(232,17), wxALIGN_CENTRE, _T("ID_STATICTEXT2"));
    Month = new wxTextCtrl(this, ID_TEXTCTRL1, _("02"), wxPoint(344,456), wxSize(48,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("/"), wxPoint(400,456), wxSize(16,24), 0, _T("ID_STATICTEXT3"));
    Year = new wxTextCtrl(this, ID_TEXTCTRL2, _("2011"), wxPoint(424,456), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    Button1 = new wxButton(this, ID_BUTTON9, _("+"), wxPoint(304,456), wxSize(24,24), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    Button2 = new wxButton(this, ID_BUTTON10, _("-"), wxPoint(280,456), wxSize(24,24), 0, wxDefaultValidator, _T("ID_BUTTON10"));
    FromMonthDay = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxPoint(272,512), wxSize(104,27), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    FromMonthDay->SetSelection( FromMonthDay->Append(_("Σήμερα")) );
    StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("Από"), wxPoint(272,488), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("Έως"), wxPoint(376,488), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    ToMonthDay = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxPoint(384,512), wxSize(120,27), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
    ToMonthDay->SetSelection( ToMonthDay->Append(_("Τέλος Μήνα")) );
    HtmlWindow1 = new wxHtmlWindow(this, ID_HTMLWINDOW1, wxPoint(272,40), wxSize(728,384), wxHW_SCROLLBAR_AUTO|wxFULL_REPAINT_ON_RESIZE, _T("ID_HTMLWINDOW1"));
    HtmlWindow1->LoadPage(_("Graphs/start.html"));
    HtmlWindow1->SetExtraStyle( HtmlWindow1->GetExtraStyle() | wxWS_EX_VALIDATE_RECURSIVELY );
    StaticText5 = new wxStaticText(this, ID_STATICTEXT6, _("Επιλογή Προβολής"), wxPoint(536,432), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    ViewSelection = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxPoint(728,430), wxSize(232,26), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX3"));
    ViewSelection->SetSelection( ViewSelection->Append(_("Μηνιαία κατάσταση")) );
    ViewSelection->Append(_("Ημερήσια κατάσταση"));
    ViewSelection->Append(_("Διασπορά Υπηρεσιών"));
    ButtonPrevViewSelection = new wxButton(this, ID_BUTTON3, _("<"), wxPoint(680,430), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    ButtonNextViewSelection = new wxButton(this, ID_BUTTON6, _(">"), wxPoint(970,430), wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem9 = new wxMenuItem(Menu1, idMenuNewPersonDatabase, _("Δημιουργία Βάσης Προσωπικού"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem9);
    Menu1->AppendSeparator();
    MenuItem3 = new wxMenuItem(Menu1, idMenuLoadPersonDatabase, _("Άνοιγμα Βάσης Προσωπικού"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu1, idMenuSavePersonDatabase, _("Αποθήκευση Βάσης Προσωπικού"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem5 = new wxMenuItem(Menu1, idMenuCombinePersonDatabase, _("Συνδυασμός Βάσεων Προσωπικού"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem5);
    Menu1->AppendSeparator();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Έξοδος\tAlt-F4"), _("Έξοδος από την εφαρμογή"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&Αρχείο"));
    Menu3 = new wxMenu();
    MenuItem10 = new wxMenuItem(Menu3, idMenuCalculate, _("Κατανομή Εργασιών"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem10);
    Menu3->AppendSeparator();
    MenuItem6 = new wxMenuItem(Menu3, idMenuViewDaily, _("Προβολή Ημερήσιας Κατάστασης"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem6);
    MenuItem7 = new wxMenuItem(Menu3, idMenuViewWeekly, _("Προβολή Εβδομαδιαίας Κατάστασης"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem7);
    MenuItem8 = new wxMenuItem(Menu3, idMenuViewMonthly, _("Προβολή Εβδομαδιαίας Κατάστασης"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem8);
    MenuBar1->Append(Menu3, _("Εξαγωγή Καταστάσεων"));
    Menu2 = new wxMenu();
    MenuItem11 = new wxMenuItem(Menu2, idMenuHelp, _("Βοήθεια"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem11);
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("Δημιουργός\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    Center();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffSchedulerFrame::OnButtonAddRemoveStaffClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffSchedulerFrame::OnButtonAddRemoveDailyJobsClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffSchedulerFrame::OnButtonAddRemoveVacationsClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffSchedulerFrame::OnButtonCalculateRemainingDaysClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffSchedulerFrame::OnButtonSwapJobsDaysPeopleClick);
    Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&StaffSchedulerFrame::OnViewSelectionSelect);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffSchedulerFrame::OnButtonPrevViewSelectionClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffSchedulerFrame::OnButtonNextViewSelectionClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&StaffSchedulerFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&StaffSchedulerFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&StaffSchedulerFrame::OnClose);
    //*)


    /* HTML WINDOW --------------- */
     wxFileName fname(wxT("Graphs/start.html"));
       HtmlWindow1->LoadFile(fname);
    /* HTML WINDOW --------------- */


    wxListItem col0;
    col0.SetId(0);
    col0.SetText( wxT(" Επίθετο ") );
    col0.SetWidth(150);
    StaffList->InsertColumn(0, col0);

    wxListItem col1;
    col1.SetId(0);
    col1.SetText( wxT("Όνομα") );
    col1.SetWidth(60);
    StaffList->InsertColumn(1, col1);


    wxListItem colb0;
    colb0.SetId(0);
    colb0.SetText( wxT("Περιγραφή") );
    colb0.SetWidth(120);
    DailyJobList->InsertColumn(0, colb0);

    wxListItem colb1;
    colb1.SetId(0);
    colb1.SetText( wxT("Πλήθος") );
    colb1.SetWidth(80);
    DailyJobList->InsertColumn(1, colb1);


    wxListItem colc0;
    colc0.SetId(0);
    colc0.SetText( wxT("Άτομο") );
    colc0.SetWidth(150);
    VacationList->InsertColumn(0, colc0);

    wxListItem colc1;
    colc1.SetId(0);
    colc1.SetText( wxT("Ημέρες") );
    colc1.SetWidth(60);
    VacationList->InsertColumn(1, colc1);


    SC_Init(100,14);
    SC_Test();
    ReflectSCCoreToForm();
}

StaffSchedulerFrame::~StaffSchedulerFrame()
{
    SC_Close();
    //(*Destroy(StaffSchedulerFrame)
    //*)
}

void StaffSchedulerFrame::OnQuit(wxCommandEvent& event)
{
    //SC_Close();
    Close();
}

void StaffSchedulerFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg;

    msg << wxT("Το Πρόγραμμα αυτό είναι κατασκευασμένο από τον Αμμάρ Γκαμάζ");
    msg << wxT("http://ammar.gr.\n\n");
    msg << wxbuildinfo(long_f);
    msg << wxT("\n");
    wxMessageBox(msg, _("Staff Scheduler..."));
}



void StaffSchedulerFrame::OnButtonAddRemoveStaffClick(wxCommandEvent& event)
{
    StaffManagment manage_staff(0);
    manage_staff.ShowModal();
}

void StaffSchedulerFrame::OnButtonAddRemoveDailyJobsClick(wxCommandEvent& event)
{
    WorkManagment manage_works(0);
    manage_works.ShowModal();
}

void StaffSchedulerFrame::OnButtonAddRemoveOneTimeJobsClick(wxCommandEvent& event)
{
    WorkManagment manage_works(0);
    manage_works.ShowModal();
}

void StaffSchedulerFrame::OnButtonAddRemoveVacationsClick(wxCommandEvent& event)
{
}

void StaffSchedulerFrame::OnButtonCalculateRemainingDaysClick(wxCommandEvent& event)
{
    wxFileName fname(wxT("Graphs/working.html"));
    HtmlWindow1->LoadFile(fname);
    int i=SC_Compute();
    if ( i )
     {
       SC_Printout();
       ComputationStatus->SetLabel(wxT("Επιτυχής κατανομή εργασιών ...!"));
       wxFileName fname(wxT("Graphs/monthly.html"));
       HtmlWindow1->LoadFile(fname);
       HtmlWindow1->SetScale(0.9,0.9);
     } else
     {
       wxFileName fname(wxT("Graphs/failed.html"));
       HtmlWindow1->LoadFile(fname);
       ComputationStatus->SetLabel(wxT("Aπoτυχία κατανομής εργασιών !!!"));
     }
}

void StaffSchedulerFrame::OnButtonSwapJobsDaysPeopleClick(wxCommandEvent& event)
{
}

void StaffSchedulerFrame::OnButtonViewDayClick(wxCommandEvent& event)
{
    SC_Printout();
}

void StaffSchedulerFrame::OnButtonViewMonthClick(wxCommandEvent& event)
{
    SC_Printout();

}

void StaffSchedulerFrame::OnClose(wxCloseEvent& event)
{
    Close();
}

void StaffSchedulerFrame::OnButtonPrevViewSelectionClick(wxCommandEvent& event)
{
      if ( ViewSelection->GetSelection() == 0 )
      {
         ViewSelection->SetSelection(2);
      } else
      {
         ViewSelection->SetSelection(ViewSelection->GetSelection()-1);
      }

      OnViewSelectionSelect(event);
}

void StaffSchedulerFrame::OnButtonNextViewSelectionClick(wxCommandEvent& event)
{
    if ( ViewSelection->GetSelection() == 2 )
      {
         ViewSelection->SetSelection(0);
      } else
      {
         ViewSelection->SetSelection(ViewSelection->GetSelection()+1);
      }

      OnViewSelectionSelect(event);
}

void StaffSchedulerFrame::OnViewSelectionSelect(wxCommandEvent& event)
{
    if ( ViewSelection->GetSelection() == 0 )
      {
        wxFileName fname(wxT("Graphs/monthly.html"));
        HtmlWindow1->LoadFile(fname);
        HtmlWindow1->SetScale(0.9,0.9);
      } else
    if ( ViewSelection->GetSelection() == 1 )
      {
        wxFileName fname(wxT("Graphs/vertical.html"));
        HtmlWindow1->LoadFile(fname);
        HtmlWindow1->SetScale(0.9,0.9);
      } else
    if ( ViewSelection->GetSelection() == 2 )
      {
        wxFileName fname(wxT("Graphs/distribution.html"));
        HtmlWindow1->LoadFile(fname);
        HtmlWindow1->SetScale(0.9,0.9);
      }

}
