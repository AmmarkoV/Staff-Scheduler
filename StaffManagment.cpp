#include "StaffManagment.h"

#include "ScheduleCreator/ScheduleCreator.h"

#include <wx/msgdlg.h>
//(*InternalHeaders(StaffManagment)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(StaffManagment)
const long StaffManagment::ID_STATICBOX2 = wxNewId();
const long StaffManagment::ID_STATICBOX1 = wxNewId();
const long StaffManagment::ID_STATICTEXT1 = wxNewId();
const long StaffManagment::ID_LISTCTRL1 = wxNewId();
const long StaffManagment::ID_TEXTCTRL1 = wxNewId();
const long StaffManagment::ID_STATICTEXT2 = wxNewId();
const long StaffManagment::ID_TEXTCTRL2 = wxNewId();
const long StaffManagment::ID_COMBOBOX1 = wxNewId();
const long StaffManagment::ID_STATICTEXT3 = wxNewId();
const long StaffManagment::ID_TEXTCTRL3 = wxNewId();
const long StaffManagment::ID_STATICTEXT4 = wxNewId();
const long StaffManagment::ID_LISTCTRL3 = wxNewId();
const long StaffManagment::ID_BUTTON5 = wxNewId();
const long StaffManagment::ID_BUTTON6 = wxNewId();
const long StaffManagment::ID_BUTTON7 = wxNewId();
const long StaffManagment::ID_STATICTEXT5 = wxNewId();
const long StaffManagment::ID_TEXTCTRL4 = wxNewId();
const long StaffManagment::ID_BUTTON8 = wxNewId();
const long StaffManagment::ID_BUTTON9 = wxNewId();
const long StaffManagment::ID_STATICTEXT6 = wxNewId();
const long StaffManagment::ID_BUTTON1 = wxNewId();
const long StaffManagment::ID_COMBOBOX2 = wxNewId();
const long StaffManagment::ID_STATICTEXT7 = wxNewId();
const long StaffManagment::ID_TEXTCTRL5 = wxNewId();
const long StaffManagment::ID_BUTTON2 = wxNewId();
const long StaffManagment::ID_STATICTEXT8 = wxNewId();
const long StaffManagment::ID_STATICTEXT9 = wxNewId();
//*)

BEGIN_EVENT_TABLE(StaffManagment,wxDialog)
	//(*EventTable(StaffManagment)
	//*)
END_EVENT_TABLE()


inline wxString _U2(const char String[] = "")
{
  return wxString(String, wxConvUTF8);
}


void StaffManagment::RefreshList()
{
  StaffList->DeleteAllItems();
  wxString query_wxstr;
  int personid=1;
  while ( personid < SC_GetTotalPersons() )
   {

        query_wxstr.clear();

        query_wxstr<<_U2(SC_GetPersons_Str(personid,0));
        long tmp = StaffList->InsertItem(personid,query_wxstr, 0);
        StaffList->SetItemData(tmp, personid);

        query_wxstr.clear();
        query_wxstr<<_U2(SC_GetPersons_Str(personid,1));
        StaffList->SetItem(tmp, 1, query_wxstr);

       ++personid;
   }

  JobToAdd->Clear();
  int jobid=1;
  while ( jobid < SC_GetTotalJobs() )
   {
       JobToAdd->Append(_U2(SC_GetJobs_Str(jobid,0)));
       ++jobid;
   }

}

void StaffManagment::LoadPersonIDToForm(int personid)
{
    block_autosave = 1;

    fprintf(stderr,"LoadPersonIDToForm(%u -> %u ) called \n",personid,personid+1);
    ++personid;
    last_selected_personid = personid;
    wxString query_wxstr;

    query_wxstr.clear(); query_wxstr<<_U2(SC_GetPersons_Str(personid,0));
    TextCtrlSurname->SetValue(query_wxstr);

    query_wxstr.clear(); query_wxstr<<_U2(SC_GetPersons_Str(personid,1));
    TextCtrlName->SetValue(query_wxstr);


   fprintf(stderr,"he has %u jobs \n",SC_GetTotalPersonPossibleJobs(personid));

  EnlistedJobs->DeleteAllItems();
  int jobid=0;
  while ( jobid < SC_GetTotalPersonPossibleJobs(personid) )
   {
        query_wxstr.clear();

        query_wxstr<<_U2(SC_GetJobs_Str(SC_GetPersonsPossibleJobsInt(personid,jobid),0));
        long tmp = EnlistedJobs->InsertItem(jobid,query_wxstr, 0);
        EnlistedJobs->SetItemData(tmp, jobid);

        query_wxstr.clear();
        if ( SC_GetPersonsPossibleJobsNumber(personid,jobid) > 0 )
          {
             query_wxstr<<SC_GetPersonsPossibleJobsNumber(personid,jobid);
          } else
          {
            query_wxstr<<_U2("Χωρίς Όριο");
          }

        EnlistedJobs->SetItem(tmp, 1, query_wxstr);

       ++jobid;
   }

    block_autosave = 0;
}

StaffManagment::StaffManagment(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(StaffManagment)
	Create(parent, id, _("Staff Managment"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(647,548));
	Move(wxDefaultPosition);
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("Εργασίες ατόμου προς ανάθεση"), wxPoint(280,240), wxSize(360,240), 0, _T("ID_STATICBOX2"));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Στοιχεία Επιλεγμένου Ατόμου"), wxPoint(272,8), wxSize(368,224), 0, _T("ID_STATICBOX1"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Όνομα"), wxPoint(280,80), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaffList = new wxListCtrl(this, ID_LISTCTRL1, wxPoint(8,32), wxSize(256,472), wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL1"));
	TextCtrlName = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(280,104), wxSize(160,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Επίθετο"), wxPoint(456,80), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	TextCtrlSurname = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxPoint(456,104), wxSize(160,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	ComboBoxRank = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxPoint(352,40), wxSize(265,27), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Βαθμός"), wxPoint(288,44), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	TextCtrlComments = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxPoint(280,160), wxSize(336,24), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Σχόλια"), wxPoint(280,136), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	EnlistedJobs = new wxListCtrl(this, ID_LISTCTRL3, wxPoint(296,320), wxSize(288,144), wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL3"));
	ButtonRemovePerson = new wxButton(this, ID_BUTTON5, _("Αφαίρεση"), wxPoint(176,504), wxSize(88,29), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	ButtonAddPerson = new wxButton(this, ID_BUTTON6, _("Προσθήκη"), wxPoint(8,504), wxSize(168,29), 0, wxDefaultValidator, _T("ID_BUTTON6"));
	ButtonBack = new wxButton(this, ID_BUTTON7, _("Πίσω"), wxPoint(480,504), wxSize(152,32), 0, wxDefaultValidator, _T("ID_BUTTON7"));
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Εργασίες άνα μήνα"), wxPoint(280,206), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	JobsPerMonth = new wxTextCtrl(this, ID_TEXTCTRL4, _("0"), wxPoint(424,200), wxSize(64,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	JobsPerMonth->SetMaxLength(3);
	ButtonAddJobsToPersonMonth = new wxButton(this, ID_BUTTON8, _("+"), wxPoint(496,200), wxSize(32,24), 0, wxDefaultValidator, _T("ID_BUTTON8"));
	ButtonRemoveJobsToPersonMonth = new wxButton(this, ID_BUTTON9, _("-"), wxPoint(528,200), wxSize(32,24), 0, wxDefaultValidator, _T("ID_BUTTON9"));
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Ανθρώπινο Δυναμικό"), wxPoint(8,8), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	ButtonAddJob = new wxButton(this, ID_BUTTON1, _("+"), wxPoint(592,288), wxSize(32,24), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	JobToAdd = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxPoint(296,288), wxDefaultSize, 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX2"));
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("x"), wxPoint(504,288), wxSize(16,16), 0, _T("ID_STATICTEXT7"));
	JobToAddTimes = new wxTextCtrl(this, ID_TEXTCTRL5, _("0"), wxPoint(528,288), wxSize(56,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	ButtonRemoveJob = new wxButton(this, ID_BUTTON2, _("-"), wxPoint(592,320), wxSize(32,24), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Μέγιστος αρ."), wxPoint(528,264), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Εργασίες"), wxPoint(296,264), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	Center();

	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&StaffManagment::OnStaffListBeginDrag);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&StaffManagment::OnTextCtrlNameText);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&StaffManagment::OnTextCtrlSurnameText);
	Connect(ID_LISTCTRL3,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&StaffManagment::OnEnlistedJobsBeginDrag);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffManagment::OnButtonRemovePersonClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffManagment::OnButtonAddPersonClick);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffManagment::OnButtonBackClick);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffManagment::OnButtonAddJobsToPersonMonthClick);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffManagment::OnButtonRemoveJobsToPersonMonthClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffManagment::OnButtonAddJobClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StaffManagment::OnButtonRemoveJobClick);
	//*)

    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&StaffManagment::OnStaffListBeginDrag);
    Connect(ID_LISTCTRL3,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&StaffManagment::OnEnlistedJobsBeginDrag);

    wxListItem col0;
    col0.SetId(0);
    col0.SetText( wxT(" Επίθετο ") );
    col0.SetWidth(140);
    StaffList->InsertColumn(0, col0);

    wxListItem col1;
    col1.SetId(0);
    col1.SetText( wxT(" Όνομα  ") );
    col1.SetWidth(90);
    StaffList->InsertColumn(1, col1);


    wxListItem seccol0;
    seccol0.SetId(0);
    seccol0.SetText( wxT(" Περιγραφή Εργασίας ") );
    seccol0.SetWidth(170);
    EnlistedJobs->InsertColumn(0, seccol0);

    wxListItem seccol1;
    seccol1.SetId(0);
    seccol1.SetText( wxT(" Αριθμός  ") );
    seccol1.SetWidth(90);
    EnlistedJobs->InsertColumn(1, seccol1);

    block_autosave=1;
	last_selected_personid=0;
	RefreshList();
}

StaffManagment::~StaffManagment()
{
	//(*Destroy(StaffManagment)
	//*)
}


void StaffManagment::OnButtonBackClick(wxCommandEvent& event)
{
    Close();
}

void StaffManagment::OnStaffListBeginDrag(wxListEvent& event)
{
    int index=event.GetIndex();

     if ( SC_GetTotalPersons()<=index) { fprintf(stderr,"Index for persons supplied by gui %u is out of bounds %u \n",index,SC_GetTotalPersons()); return; }

     LoadPersonIDToForm(index);
     Refresh();
}

void StaffManagment::OnButtonAddPersonClick(wxCommandEvent& event)
{
  SC_AddPerson((char *)"ΕΠΙΘΕΤΟ",(char *)"ΟΝΟΜΑ",0,14);
  RefreshList();
}


void StaffManagment::OnButtonRemovePersonClick(wxCommandEvent& event)
{
   SC_RemovePerson(last_selected_personid);
   RefreshList();
}

void StaffManagment::OnButtonAddJobsToPersonMonthClick(wxCommandEvent& event)
{
    wxString curval = JobsPerMonth->GetValue();
    long value;
    if(!curval.ToLong(&value)) { wxMessageBox(wxT("Παρακαλώ εισάγετε έναν αριθμό στο πεδίο εργασίες ανα μήνα"),wxT("Staff Managment")); }
    value+=1;
    curval.clear(); curval<<value;
    JobsPerMonth->SetValue(curval);
}

void StaffManagment::OnButtonRemoveJobsToPersonMonthClick(wxCommandEvent& event)
{
    wxString curval = JobsPerMonth->GetValue();
    long value;
    if(!curval.ToLong(&value)) { wxMessageBox(wxT("Παρακαλώ εισάγετε έναν αριθμό στο πεδίο εργασίες ανα μήνα"),wxT("Staff Managment")); }
    if ( value == 0 ) { return ; }
    value-=1;
    curval.clear(); curval<<value;
    JobsPerMonth->SetValue(curval);
}

void StaffManagment::OnButtonAddJobClick(wxCommandEvent& event)
{
    int jobid = JobToAdd->GetCurrentSelection()+1;
    fprintf(stderr,"OnButtonAddJobClick( job %u - %s ) called \n",jobid,SC_GetJobs_Str(jobid,0));
    long value=0;
    wxString curval = JobsPerMonth->GetValue();
    if(!curval.ToLong(&value)) { value=0; }

    SC_AddPossibleJobToPerson(last_selected_personid,jobid,value);
    LoadPersonIDToForm(last_selected_personid-1);
}

void StaffManagment::OnButtonRemoveJobClick(wxCommandEvent& event)
{
    int jobid = SC_GetPersonsPossibleJobsInt(last_selected_personid,last_selected_jobid);
    fprintf(stderr,"OnButtonRemoveJobClick( job %u - %s ) called \n",jobid,SC_GetJobs_Str(jobid,0));
    SC_RemovePossibleJobFromPerson(last_selected_personid,jobid);
    LoadPersonIDToForm(last_selected_personid-1);
}

void StaffManagment::OnEnlistedJobsBeginDrag(wxListEvent& event)
{
     int index=event.GetIndex();
     last_selected_jobid = index;
     Refresh();
}

void StaffManagment::OnTextCtrlNameText(wxCommandEvent& event)
{
    if ( block_autosave ) { return ; }
    fprintf(stderr,"CallName changed\n");
    char newstr[1024]={0};
    wxString new_wxstr=TextCtrlName->GetValue();
    strcpy( newstr ,(const char*) new_wxstr.mb_str(wxConvUTF8));
    SC_SetPersons_Str(last_selected_personid,1,newstr);
    RefreshList();
}


void StaffManagment::OnTextCtrlSurnameText(wxCommandEvent& event)
{
    if ( block_autosave ) { return ; }
    fprintf(stderr,"Name changed\n");
    char newstr[1024]={0};
    wxString new_wxstr=TextCtrlSurname->GetValue();
    strcpy( newstr ,(const char*) new_wxstr.mb_str(wxConvUTF8));
    SC_SetPersons_Str(last_selected_personid,0,newstr);
    RefreshList();
}
