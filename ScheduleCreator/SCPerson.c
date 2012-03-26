#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SCCoreMemory.h"
#include "ScheduleCreatorCore.h"
#include "ScheduleSorting.h"
#include "SCPerson.h"


int Person_Add(char * name,char *callname,unsigned int total_work,unsigned int work_per_month)
{
  if (loaded_persons >= total_persons )
    {
      fprintf(stderr,"AddPerson failed\n");
      return 0;
    }

  strcpy(persons[loaded_persons].name,name);
  strcpy(persons[loaded_persons].callname,callname);
  persons[loaded_persons].total_jobs_ever_done = total_work;
  persons[loaded_persons].jobs_per_month = work_per_month;
  ++loaded_persons;

  return 1;
}


int Person_Remove(unsigned int personid)
{
  if (loaded_persons <= personid )
    {
      fprintf(stderr,"SC_RemovePerson failed\n");
      return 0;
    }
  return RemovePersonFromArray(personid);
}

int Person_AddPossibleJob(unsigned int personid,unsigned int jobid,unsigned int max_job_times)
{
  if (personid >= loaded_persons )
    {
      fprintf(stderr,"SC_AddPossibleJobToPerson failing , person doesnt exist\n");
      return 0;
    }
  if (jobid >= loaded_jobs )
    {
      fprintf(stderr,"SC_AddPossibleJobToPerson failing , job doesnt exist\n");
      return 0;
    }
  if ( Person_CanDoJob(personid,jobid) )
    {
      fprintf(stderr,"Person can already do job\n");
      return 1;
    }
  fprintf(stderr,"SC_AddPossibleJobToPerson %u -> %u %u \n",personid,jobid,max_job_times);
  persons[personid].possible_jobs[ persons[personid].total_possible_jobs ] = jobid;
  ++persons[personid].total_possible_jobs;
  ++jobs[jobid].total_possible_persons;

  return 1;
}

int Person_RemovePossibleJob(unsigned int personid,unsigned int jobid)
{
  if (personid >= loaded_persons )
    {
      fprintf(stderr,"SC_AddPossibleJobToPerson failing , person doesnt exist\n");
      return 0;
    }
  if (jobid >= loaded_jobs )
    {
      fprintf(stderr,"SC_AddPossibleJobToPerson failing , job doesnt exist\n");
      return 0;
    }
  if ( !Person_CanDoJob(personid,jobid) )
    {
      fprintf(stderr,"Person can already not do job\n");
      return 1;
    }
  int i=0;
  while ( i < persons[personid].total_possible_jobs )
    {
      if ( persons[personid].possible_jobs[i] == jobid )
        {
          if ( i < persons[personid].total_possible_jobs - 1 )
            {
              int z=i;
              while (z < persons[personid].total_possible_jobs-1)
                {
                  persons[personid].possible_jobs[z]=persons[personid].possible_jobs[z+1];
                  ++z;
                }
            }
          else
            {
              /*ALREADY THE LAST RECORD*/
            }
          --jobs[jobid].total_possible_persons;
          --persons[personid].total_possible_jobs;
          break;
        }
      ++i;
    }
  return 1;
}





int Person_CantWorkBetweenDates(unsigned int personid,unsigned int startdate,unsigned int enddate)
{

  return 0;
}

int Person_GetSumOfThisJobForThisMonth(unsigned int personid,unsigned int jobid)
{
    int total_jobs_of_kind=0;
    int i=0;
     int z=0;
    while ( i <total_days )
     {
         z=0;
         while ( z < GetTotalJobidAssignmentsAtDay(i,jobid) )
           {
               if ( year[i].job_assignments[jobid].assignment_to_person[z] == personid ) { ++total_jobs_of_kind; }
               ++z;
           }
         ++i;
     }
  return total_jobs_of_kind;
}

int Person_GetJobAtDay(unsigned int personid,unsigned int day)
{
    int i=0;
      int z=0;
    while ( i < year[day].jobs_assigned_to_day )
     {
         z=0;
         while ( z < GetTotalJobidAssignmentsAtDay(day,i) )
           {
               if ( year[day].job_assignments[i].assignment_to_person[z] == personid ) { return i; }
               ++z;
           }
         ++i;
     }
  return 0;
}

int Person_HasVacationAtDay(unsigned int personid,unsigned int day)
{
    return year[day].persons_denied[personid];
}

int Person_HasJobAtDay(unsigned int personid,unsigned int day)
{
    if ( Person_GetJobAtDay(personid,day) != 0  ) { return 1; }
    return 0;
}

int Person_HasThisJobAtDay(unsigned int personid,unsigned int jobid,unsigned int day)
{
  int z=0;
   while ( z < GetTotalJobidAssignmentsAtDay(day,jobid) )
    {
      if ( year[day].job_assignments[jobid].assignment_to_person[z] == personid ) { return 1; }
      ++z;
    }
  return 0;
}

int Person_HasJobAtDayBeforeDay(unsigned int personid,unsigned int day)
{
    if ( day > 0 )
     {
         return Person_HasJobAtDay(personid,day-1);
     }
    return 0;
}


int Person_CanDoJob(unsigned int personid,unsigned int jobid)
{
    int i=0;
    while ( i < persons[personid].total_possible_jobs )
     {
         if ( persons[personid].possible_jobs[i] == jobid ) { return 1; }
         ++i;
     }
    return 0;
}

int Person_WillBeAbleToDoJobAtDay(unsigned int personid,unsigned int jobid,unsigned int day,unsigned int tight_schedule)
{
  int person_had_job_before_day = 0;
  if ( !tight_schedule ) { person_had_job_before_day=Person_HasJobAtDayBeforeDay(personid,day); } /*If we are not on a tight schedule find about the day before*/

  if ((Person_CanDoJob(personid,jobid)) && (!Person_HasJobAtDay(personid,day)) && ( (!person_had_job_before_day)  ) && (!Person_HasVacationAtDay(personid,day)) )
   {
       return 1;
   }
   return 0;
}

int Person_AssignJobAtDay(unsigned int day ,unsigned int personid,unsigned int jobid)
{
  if ( Person_GetJobAtDay(personid,day) ==  jobid )  { fprintf(stderr,"Person (%u ) already assigned to job ( %u ) on day %u ",personid,jobid,day); return 0; }


  if (! Memory_AddDayJobPersonAssignment(day,jobid,personid) ) { fprintf(stderr,"Error  Memory_AddDayJobPersonAssignment "); return 0; }

  persons[personid].possible_jobs_taken_this_month[jobid]+=1;
  persons[personid].total_jobs_this_month+=jobs[jobid].credits ;
  return 1;
}

int Person_RemoveJobAtDay(unsigned int day ,unsigned int personid,unsigned int jobid)
{
  if ( Person_HasThisJobAtDay(personid,jobid,day)  )
   {
     if (!Memory_RemoveDayJobPersonAssignment(day,jobid,personid) ) { fprintf(stderr,"Error  Memory_RemoveDayJobPersonAssignment "); return 0; }

     persons[personid].possible_jobs_taken_this_month[jobid]-=1;
     persons[personid].total_jobs_this_month-=jobs[jobid].credits ;
   }
  return 1;
}


int ReplaceJobOfPersonWithOtherPerson(unsigned int day,unsigned int personid)
{
    unsigned int job_to_replace=Person_GetJobAtDay(personid,day);
    if (job_to_replace == 0 ) { return 0; }
    SortPeopleBetterForJobFirst(person_sorting_2,job_to_replace);

    unsigned int new_personid=1;
    unsigned int i=1;
   fprintf(stderr,"ReplaceJob(%s)OfPerson(%s)WithOtherPerson in day %u \n",jobs[job_to_replace].name,persons[personid].name,day);
   while ( i < loaded_persons )
     {

        new_personid = person_sorting_2[i].index;
        if (Person_WillBeAbleToDoJobAtDay(new_personid,job_to_replace,day,0))
          {
             fprintf(stderr,"%s CAN replace him.. \n",persons[personid].name);
             Person_RemoveJobAtDay(day,personid,job_to_replace);
             Person_AssignJobAtDay(day,new_personid,job_to_replace);
             return new_personid;
          } else
          {
              fprintf(stderr,"%s can`t replace him.. \n",persons[personid].name);
          }


         ++i;
     }


  return 0;
}




int Internal_AssignAddRemoveVacationToPerson(int add,unsigned int personid,unsigned int day_start , unsigned int total_days_of_vacation)
{
  int day = day_start-1;
  while (day < day_start+total_days_of_vacation )
   {
     if (add)
     {
       if (!year[day].persons_denied[personid])
        {
         year[day].persons_denied[personid]=1;
         ++year[day].total_persons_denied;
        }
     } else
     {
       if (year[day].persons_denied[personid])
       {
        year[day].persons_denied[personid]=0;
        --year[day].total_persons_denied;
       }
     }
     ++day;
   }
  return 1;
}

int Person_AddVacation(unsigned int personid,unsigned int day_start , unsigned int total_days_of_vacation)
{
  return Internal_AssignAddRemoveVacationToPerson(1,personid,day_start,total_days_of_vacation);
}

int Person_RemoveVacation(unsigned int personid,unsigned int day_start , unsigned int total_days_of_vacation)
{
  return Internal_AssignAddRemoveVacationToPerson(0,personid,day_start,total_days_of_vacation);
}


/*
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
           GETTERS / SETTERS  ACCESS
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/


char * Person_GetSValue(unsigned int personid,unsigned int field)
{
  fprintf(stderr,"SC_GetPersonsStr(%u,%u)\n",personid,field);
  switch (field)
    {
    case 0 :
      return persons[personid].name;
      break;
    case 1 :
      return persons[personid].callname;
      break;
    };
  return 0;
}

void Person_SetSValue(unsigned int personid,unsigned int field,char * str)
{
  fprintf(stderr,"SC_SetPersonsStr(%u,%u,%s)\n",personid,field,str);
  switch (field)
    {
    case 0 :
      strcpy(persons[personid].name,str);
      return;
      break;
    case 1 :
      strcpy(persons[personid].callname,str);
      return;
      break;
    };
  return;
}

int Person_GetIValue(unsigned int personid,unsigned int field)
{
  switch (field)
    {
    case 1 :
      return persons[personid].jobs_per_month;
      break;
    };

  return  0;
}

int GetTotalPersons()
{
  return  loaded_persons;
}


int Person_GetTotalPossibleJobs(unsigned int personid)
{
  return  persons[personid].total_possible_jobs;
}

int Person_GetPossibleJobsInt(unsigned int personid,unsigned int field)
{
  if ( field >= Person_GetTotalPossibleJobs(personid) )
    {
      return 0;
    }
  return persons[personid].possible_jobs[field];
}

int Person_GetPossibleJobsNumber(unsigned int personid,unsigned int field)
{
  if ( field >= Person_GetTotalPossibleJobs(personid) )
    {
      return 0;
    }
  return 0;
}

/*
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
           GETTERS / SETTERS  ACCESS
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

