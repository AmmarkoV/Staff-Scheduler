#include "WorkManagment.h"

//(*InternalHeaders(WorkManagment)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(WorkManagment)
const long WorkManagment::ID_STATICBOX1 = wxNewId();
const long WorkManagment::ID_LISTCTRL1 = wxNewId();
const long WorkManagment::ID_BUTTON1 = wxNewId();
const long WorkManagment::ID_BUTTON2 = wxNewId();
const long WorkManagment::ID_RADIOBOX1 = wxNewId();
const long WorkManagment::ID_STATICTEXT1 = wxNewId();
const long WorkManagment::ID_CHECKBOX1 = wxNewId();
const long WorkManagment::ID_CHECKBOX2 = wxNewId();
const long WorkManagment::ID_CHECKBOX3 = wxNewId();
const long WorkManagment::ID_CHECKBOX4 = wxNewId();
const long WorkManagment::ID_CHECKBOX5 = wxNewId();
const long WorkManagment::ID_CHECKBOX6 = wxNewId();
const long WorkManagment::ID_CHECKBOX7 = wxNewId();
const long WorkManagment::ID_STATICTEXT2 = wxNewId();
const long WorkManagment::ID_TEXTCTRL1 = wxNewId();
const long WorkManagment::ID_STATICTEXT3 = wxNewId();
const long WorkManagment::ID_STATICTEXT4 = wxNewId();
const long WorkManagment::ID_TEXTCTRL2 = wxNewId();
const long WorkManagment::ID_STATICTEXT5 = wxNewId();
const long WorkManagment::ID_STATICTEXT6 = wxNewId();
const long WorkManagment::ID_TEXTCTRL3 = wxNewId();
const long WorkManagment::ID_STATICTEXT7 = wxNewId();
const long WorkManagment::ID_TEXTCTRL4 = wxNewId();
const long WorkManagment::ID_COMBOBOX1 = wxNewId();
const long WorkManagment::ID_TEXTCTRL5 = wxNewId();
const long WorkManagment::ID_STATICTEXT8 = wxNewId();
const long WorkManagment::ID_TEXTCTRL6 = wxNewId();
const long WorkManagment::ID_STATICTEXT9 = wxNewId();
const long WorkManagment::ID_TEXTCTRL7 = wxNewId();
const long WorkManagment::ID_LISTCTRL2 = wxNewId();
const long WorkManagment::ID_BUTTON3 = wxNewId();
const long WorkManagment::ID_COMBOBOX2 = wxNewId();
const long WorkManagment::ID_BUTTON4 = wxNewId();
const long WorkManagment::ID_STATICTEXT10 = wxNewId();
const long WorkManagment::ID_TEXTCTRL8 = wxNewId();
const long WorkManagment::ID_BUTTON5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(WorkManagment,wxDialog)
	//(*EventTable(WorkManagment)
	//*)
END_EVENT_TABLE()

WorkManagment::WorkManagment(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(WorkManagment)
	Create(parent, id, _("Job Managment"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(647,548));
	Move(wxDefaultPosition);
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Στοιχεία Εργασίας"), wxPoint(280,8), wxSize(344,280), 0, _T("ID_STATICBOX1"));
	WorkList = new wxListCtrl(this, ID_LISTCTRL1, wxPoint(8,48), wxSize(256,456), 0, wxDefaultValidator, _T("ID_LISTCTRL1"));
	Button1 = new wxButton(this, ID_BUTTON1, _("Προσθήκη"), wxPoint(8,504), wxSize(152,29), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("Αφαίρεση"), wxPoint(176,504), wxSize(88,29), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Ημερίσιες"),
		_("Έκτατες")
	};
	JobType = new wxRadioBox(this, ID_RADIOBOX1, _("Εργασίες"), wxPoint(8,8), wxSize(256,32), 2, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Ημερομηνίες"), wxPoint(288,56), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	CheckBoxMonday = new wxCheckBox(this, ID_CHECKBOX1, _("Δευτέρα"), wxPoint(296,72), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBoxMonday->SetValue(true);
	CheckBoxTuesday = new wxCheckBox(this, ID_CHECKBOX2, _("Τρίτη"), wxPoint(296,96), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	CheckBoxTuesday->SetValue(true);
	CheckBoxWednesday = new wxCheckBox(this, ID_CHECKBOX3, _("Τετάρτη"), wxPoint(296,120), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	CheckBoxWednesday->SetValue(true);
	CheckBoxThursday = new wxCheckBox(this, ID_CHECKBOX4, _("Πέμπτη"), wxPoint(296,144), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	CheckBoxThursday->SetValue(true);
	CheckBoxFriday = new wxCheckBox(this, ID_CHECKBOX5, _("Παρασκευή"), wxPoint(296,168), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	CheckBoxFriday->SetValue(true);
	CheckBoxSaturday = new wxCheckBox(this, ID_CHECKBOX6, _("Σάββατο"), wxPoint(296,192), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	CheckBoxSaturday->SetValue(true);
	CheckBoxSunday = new wxCheckBox(this, ID_CHECKBOX7, _("Κυριακή"), wxPoint(296,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	CheckBoxSunday->SetValue(true);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Μετράει ώς "), wxPoint(416,128), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	Credits = new wxTextCtrl(this, ID_TEXTCTRL1, _("1"), wxPoint(512,120), wxSize(32,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("υπηρεσία"), wxPoint(552,128), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Απαιτεί "), wxPoint(416,64), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	PersonsNeeded = new wxTextCtrl(this, ID_TEXTCTRL2, _("1"), wxPoint(480,58), wxSize(32,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("άτομο/α"), wxPoint(520,64), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Επίπεδο Δυσκολίας"), wxPoint(416,96), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	Difficulty = new wxTextCtrl(this, ID_TEXTCTRL3, _("1"), wxPoint(568,88), wxSize(32,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Σύνολο ωρών ανα μέρα"), wxPoint(416,160), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	HoursPerDay = new wxTextCtrl(this, ID_TEXTCTRL4, _("0"), wxPoint(584,152), wxSize(32,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	TypeOfJob = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxPoint(416,192), wxSize(200,27), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	TypeOfJob->SetSelection( TypeOfJob->Append(_("Ημερήσια")) );
	TypeOfJob->Append(_("Έκτακτη"));
	Day = new wxTextCtrl(this, ID_TEXTCTRL5, _("00"), wxPoint(416,232), wxSize(40,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	Day->Disable();
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("/"), wxPoint(464,236), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	Month = new wxTextCtrl(this, ID_TEXTCTRL6, _("00"), wxPoint(480,232), wxSize(40,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	Month->Disable();
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("/"), wxPoint(528,236), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	Year = new wxTextCtrl(this, ID_TEXTCTRL7, _("2011"), wxPoint(544,232), wxSize(72,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
	Year->Disable();
	PersonList = new wxListCtrl(this, ID_LISTCTRL2, wxPoint(296,320), wxSize(288,144), 0, wxDefaultValidator, _T("ID_LISTCTRL2"));
	ButtonBack = new wxButton(this, ID_BUTTON3, _("Πίσω"), wxPoint(536,504), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	ComboBoxPerson = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxPoint(296,288), wxSize(288,27), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	ButtonAddJobToPerson = new wxButton(this, ID_BUTTON4, _("+"), wxPoint(590,286), wxSize(29,29), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Περιγραφή"), wxPoint(336,30), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	JobName = new wxTextCtrl(this, ID_TEXTCTRL8, wxEmptyString, wxPoint(416,24), wxSize(200,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
	ButtonRemoveJobFromPerson = new wxButton(this, ID_BUTTON5, _("-"), wxPoint(590,320), wxSize(29,29), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	Center();

	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&WorkManagment::OnButtonBackClick);
	//*)
}

WorkManagment::~WorkManagment()
{
	//(*Destroy(WorkManagment)
	//*)
}


void WorkManagment::OnButtonBackClick(wxCommandEvent& event)
{
    Close();
}
