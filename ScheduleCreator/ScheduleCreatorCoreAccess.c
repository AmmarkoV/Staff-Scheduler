#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SCCoreMemory.h"
#include "ScheduleCreatorCore.h"
#include "ScheduleCreatorCoreAccess.h"


/*
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
           PERSONS DATA ACCESS
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/
int CoreAddPerson(char * name,char *callname,unsigned int total_work,unsigned int work_per_month)
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


int CoreRemovePerson(unsigned int personid)
{
  if (loaded_persons <= personid )
    {
      fprintf(stderr,"SC_RemovePerson failed\n");
      return 0;
    }
  return RemovePersonFromArray(personid);
}

int CorePersonCantWorkBetweenDates(unsigned int personid,unsigned int startdate,unsigned int enddate)
{

  return 0;
}

int CoreAddPossibleJobToPerson(unsigned int personid,unsigned int jobid,unsigned int max_job_times)
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
  if ( PersonCanDoJob(personid,jobid) )
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

int CoreRemovePossibleJobFromPerson(unsigned int personid,unsigned int jobid)
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
  if ( !PersonCanDoJob(personid,jobid) )
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

/*
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
           PERSONS DATA ACCESS
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/


/*

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

*/




/*
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
           JOBS DATA ACCESS
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/
int CoreAddJob(char * name,unsigned int units,unsigned int persons_needed)
{
  if (loaded_jobs >= total_jobs )
    {
      fprintf(stderr,"Jobs are full !\n");
      return 0;
    }

  strcpy(jobs[loaded_jobs].name,name);
  jobs[loaded_jobs].credits = units;
  jobs[loaded_jobs].persons_needed = persons_needed;
  ++loaded_jobs;

  return 1;
}





char * CoreGetJobsStr(unsigned int jobid,unsigned int field)
{
  return  jobs[jobid].name;
}

int CoreGetJobsInt(unsigned int jobid,unsigned int field)
{
  switch (field)
    {
    case 1 :
      return jobs[jobid].credits;
      break;
    case 2 :
      return jobs[jobid].total_possible_persons;
      break;
    case 3 :
      return jobs[jobid].persons_needed;
      break;
    };

  return  0;
}

int CoreGetTotalJobs()
{
  return  loaded_jobs;
}
/*
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
           PERSONS DATA ACCESS
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/


/*

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

*/



/*
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
           GETTERS / SETTERS  ACCESS
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/


char * CoreGetPersonsStr(unsigned int personid,unsigned int field)
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

void CoreSetPersonsStr(unsigned int personid,unsigned int field,char * str)
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

int CoreGetPersonsInt(unsigned int personid,unsigned int field)
{
  switch (field)
    {
    case 1 :
      return persons[personid].jobs_per_month;
      break;
    };

  return  0;
}

int CoreGetTotalPersons()
{
  return  loaded_persons;
}


int CoreGetTotalPersonPossibleJobs(unsigned int personid)
{
  return  persons[personid].total_possible_jobs;
}

int CoreGetPersonsPossibleJobsInt(unsigned int personid,unsigned int field)
{
  if ( field >= CoreGetTotalPersonPossibleJobs(personid) )
    {
      return 0;
    }
  return persons[personid].possible_jobs[field];
}

int CoreGetPersonsPossibleJobsNumber(unsigned int personid,unsigned int field)
{
  if ( field >= CoreGetTotalPersonPossibleJobs(personid) )
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
