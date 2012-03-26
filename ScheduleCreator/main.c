#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ScheduleCreatorCore.h"
#include "SCPerson.h"
#include "SCJob.h"
#include "SchedulePrintouts.h"
#include "ScheduleSolver.h"
#include "SCCoreMemory.h"
#include "ScheduleCreatorFileIO.h"

char * SC_Version()
{
    return (char *) " Schedule Creator 0.12 Pre-Alpha ";
}

int SC_Init(unsigned int max_persons,unsigned int max_jobs)
{
  srand ( time(NULL) );
  int i = InitCore(max_persons,max_jobs);
  AutoLoad();
  return i;
}


int SC_Close()
{
  AutoSave();
  return CloseCore();
}

/*
       BASIC FUNCTIONS ADD & REMOVE DATABASE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/
int SC_AddPerson(char * name,char *callname,unsigned int total_work,unsigned int work_per_month)
{
  return Person_Add(name,callname,total_work,work_per_month);
}


int SC_RemovePerson(unsigned int personid)
{
  return Person_Remove(personid);
}

int SC_PersonCantWorkBetweenDates(unsigned int personid,unsigned int startdate,unsigned int enddate)
{
  return Person_CantWorkBetweenDates(personid,startdate,enddate);
}

int SC_AddPossibleJobToPerson(unsigned int personid,unsigned int jobid,unsigned int max_job_times)
{
  return Person_AddPossibleJob(personid,jobid,max_job_times);
}

int SC_RemovePossibleJobFromPerson(unsigned int personid,unsigned int jobid)
{
  return Person_RemovePossibleJob(personid,jobid);
}

int SC_AddJob(char * name,unsigned int units,unsigned int persons_needed)
{
  return Job_Add(name,units,persons_needed);
}

int SC_AddJobTimeTable(unsigned int jobid,signed int from_time,signed int to_time)
{
  return 0;
}
/*
       BASIC FUNCTIONS ADD & REMOVE DATABASE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/


int SC_SetDate(unsigned int day,unsigned int month,unsigned int year)
{
  return 1;
}

int SC_Compute(unsigned int from_day,unsigned int from_month,unsigned int from_year,unsigned int days)
{
  Solve(1,31);
  ImproveSolutionBySwapping(1,31);
  ImproveSolutionBySwapping(1,31);
  return 1;
}

int SC_Printout()
{
  PrintOutHtml("Graphs/daily_month.html");
  PrintOutDistributionHTML("Graphs/distribution.html");
  PrintOutVacationsHTML("Graphs/monthly.html");
  PrintOutNVerticalDaystHtml("Graphs/vertical.html",3);
  return 1;
}


int SC_Test()
{


  /*

      SC_AddJob("ΕΞΟΔΟΣ",0); // 0
      SC_AddJob("ΣΚΟΠΙΑ.2",1); // 3
      SC_AddJob("ΠΕΡΙΠO.1",1); // 4
      SC_AddJob("ΠΕΡΙΠO.3",1); // 5
      SC_AddJob("ΘΑΛΑΜO.1",1); // 6
      SC_AddJob("ΘΑΛΑΜO.2",1); // 7
      SC_AddJob("ΘΑΛΑΜO.3",1); // 8
      SC_AddJob("ΜΑΓΕΙΡΙΑ",1); // 9


      SC_AddPerson("Κανένας"," ",0,0); // 0
      SC_AddPerson("ΓΚΑΜΑΖ","ΑΜΜΑΡ",0,14); // 1

      int i=4;
       while ( i <= 22)
        {
            SC_AddPossibleJobToPerson(i,3,0);
            SC_AddPossibleJobToPerson(i,4,0);
            SC_AddPossibleJobToPerson(i,5,0);
            SC_AddPossibleJobToPerson(i,6,0);
            SC_AddPossibleJobToPerson(i,7,0);
            SC_AddPossibleJobToPerson(i,8,0);
            SC_AddPossibleJobToPerson(i,9,0);
            ++i;
        }

            SC_AddPossibleJobToPerson(23,6,0);
            SC_AddPossibleJobToPerson(23,7,0);
            SC_AddPossibleJobToPerson(23,8,0);

            SC_AddPossibleJobToPerson(24,9,0);

      SC_AddPossibleJobToPerson(1,1,0);
      SC_AddPossibleJobToPerson(2,1,0);
      SC_AddPossibleJobToPerson(3,1,0);

      SC_AddPossibleJobToPerson(4,2,0);
      SC_AddPossibleJobToPerson(5,2,0);
      SC_AddPossibleJobToPerson(6,2,0);
      SC_AddPossibleJobToPerson(7,2,0);
      SC_AddPossibleJobToPerson(8,2,0);
  */

  Person_AddVacation(4, 14 ,5);
  Person_AddVacation(1, 18 ,5);
  Person_AddVacation(12, 8 ,15);
  Person_AddVacation(22, 5 ,5);
  Person_AddVacation(24, 10 ,4);
  Person_AddVacation(7, 16 ,4);



  return 1;
}


char * SC_GetJobs_Str(unsigned int jobid,unsigned int field)
{
  return  Job_GetSValue(jobid,field);
}

int SC_GetJobs_Int(unsigned int jobid,unsigned int field)
{
  return  Job_GetIValue(jobid,field);
}

int SC_GetTotalJobs()
{
  return  GetTotalJobs();
}


char * SC_GetPersons_Str(unsigned int personid,unsigned int field)
{
  return Person_GetSValue(personid,field);
}

void SC_SetPersons_Str(unsigned int personid,unsigned int field,char * str)
{
  return Person_SetSValue(personid,field,str);
}

int SC_GetPersons_Int(unsigned int personid,unsigned int field)
{
  return  Person_GetIValue(personid,field);
}

int SC_GetTotalPersons()
{
  return  GetTotalPersons();
}


int SC_GetTotalPersonPossibleJobs(unsigned int personid)
{
  return Person_GetTotalPossibleJobs(personid);
}

int SC_GetPersonsPossibleJobsInt(unsigned int personid,unsigned int field)
{
  return Person_GetPossibleJobsInt(personid,field);
}

int SC_GetPersonsPossibleJobsNumber(unsigned int personid,unsigned int field)
{
  return Person_GetPossibleJobsNumber(personid,field);
}


