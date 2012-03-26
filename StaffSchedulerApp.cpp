/***************************************************************
 * Name:      StaffSchedulerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Ammar Qammaz (ammarkov@gmail.com)
 * Created:   2011-02-14
 * Copyright: Ammar Qammaz (ammarkov.ath.cx)
 * License:
 **************************************************************/

#include "StaffSchedulerApp.h"

//(*AppHeaders
#include "StaffSchedulerMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(StaffSchedulerApp);

bool StaffSchedulerApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	StaffSchedulerFrame* Frame = new StaffSchedulerFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
