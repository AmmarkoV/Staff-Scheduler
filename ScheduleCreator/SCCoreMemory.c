#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ScheduleCreatorCore.h"
#include "SCCoreMemory.h"
#include "ScheduleSorting.h"


int PersonIsOk(unsigned int personid)
{
  if ( ( persons == 0 ) || ( personid>loaded_persons ) )
    {
      return 0;
    }
  return 1;
}

int CoreIsOk()
{
  if ( ( year == 0 ) || ( persons == 0 ) || ( jobs == 0 ) )
    {
      return 0;
    }
  return 1;
}


int ClearCoreJobs()
{
  unsigned int max_jobs=total_jobs;



  loaded_jobs=0;

  unsigned int z=0;
  unsigned int i=0;
  while (i <= 31)
    {
      z=0;
      while (z<max_jobs)
        {
          year[i].job_assignments[z].total_persons_assigned_to=0;
          year[i].day_locked=0;
          ++z;
        }
      ++i;
    }




  i=0;
  while (i < max_jobs )
    {
      jobs[i].name[0]=0;
      jobs[i].credits=0;
      jobs[i].difficulty=0;
      jobs[i].persons_needed=0;
      jobs[i].total_possible_persons=0;

      jobs[i].repeat_cycle=0;
      jobs[i].timetable.total_items=0;
//      jobs[i].day=0;
//      jobs[i].month=0;
 //     jobs[i].year=0;

      ++i;
    }
  return 1;
}

int ClearCorePersons()
{
  loaded_persons=0;

  unsigned int z=0;
  unsigned int i=0;
  while (i <= 31)
    {
      z=0;
      while (z<total_persons)
        {
          year[i].persons_denied[z]=0;
          ++z;
        }
      year[i].total_persons_denied = 0;
      ++i;
    }

  i=0;
  while (i < total_persons )
    {
      z=0;
      while (z<total_jobs)
        {
          persons[i].possible_jobs[z]=0;
          ++z;
        }

      z=0;
      while (z<total_jobs)
        {
          persons[i].possible_jobs_taken_this_month[z]=0;
          persons[i].possible_jobs_max_this_month[z]=0;
          ++z;
        }


      persons[i].total_possible_jobs=0; /*Arxika dn mporei na kanei kammia , paroti exoume mexri max possible*/
      persons[i].name[0]=0;
      persons[i].callname[0]=0;
      persons[i].jobs_per_month=0;
      persons[i].total_jobs_this_month=0;
      persons[i].total_jobs_ever_done=0;
      persons[i].std_deviation_jobs=0.0;
      persons[i].total_vacation_ever_taken=0;
      ++i;
    }

  return 1;
}


int ClearCore()
{
  ClearCorePersons();
  ClearCoreJobs();
  return 1;
}


int InitCore(unsigned int max_persons,unsigned int max_jobs)
{
  jobs = ( struct Job * ) malloc ( sizeof(struct Job) * ( max_jobs+1));
  total_jobs=max_jobs;

  persons = ( struct Person * ) malloc ( sizeof(struct Person) * ( max_persons+1));
  total_persons=max_persons;

  year = ( struct Day * ) malloc ( sizeof(struct Day) * ( 430 ) );

  int larger_list = max_persons +1; /*In order to be used for both person and job sorting*/
  if ( larger_list < max_jobs +1 )
    {
      larger_list = max_jobs +1;
    }
  person_sorting_1 = ( struct SortingList * ) malloc ( sizeof(struct SortingList) * ( larger_list));
  person_sorting_2 = ( struct SortingList * ) malloc ( sizeof(struct SortingList) * ( larger_list));


  unsigned int i=0;
  while (i <= 31)
    {
      year[i].job_assignments = ( struct JobAssignment * ) malloc ( sizeof(struct JobAssignment) * (max_jobs+1) );
      year[i].jobs_assigned_to_day = max_jobs;

      year[i].persons_denied = ( unsigned int * ) malloc ( sizeof(unsigned int) * ( max_persons+1 ));
      ++i;
    }

  i=0;
  while (i < max_persons )
    {
      persons[i].possible_jobs = ( unsigned int * ) malloc ( sizeof(unsigned int) * ( max_jobs+1 ));

      persons[i].possible_jobs_taken_this_month = ( unsigned int * ) malloc ( sizeof(unsigned int) * ( max_jobs+1 ));
      persons[i].possible_jobs_max_this_month = ( unsigned int * ) malloc ( sizeof(unsigned int) * ( max_jobs+1 ));

      ++i;
    }

  ClearCore();

  return 1;
}









int CloseCore()
{
  ClearCore();

  unsigned int i=0;
  while (i <= 31)
    {
      free(year[i].job_assignments);
      free(year[i].persons_denied);
      ++i;
    }


  i=0;
  while (i < loaded_persons )
    {
      free(  persons[i].possible_jobs );

      free(  persons[i].possible_jobs_taken_this_month );
      free(  persons[i].possible_jobs_max_this_month  );

      ++i;
    }

  free(jobs);
  free(persons);
  free(year);
  free(person_sorting_1);
  free(person_sorting_2);


  jobs=0;
  loaded_jobs=0;
  total_jobs=0;

  persons=0;
  loaded_persons=0;
  total_persons=0;

  year=0;
  total_days=0;

  person_sorting_1=0;
  person_sorting_2=0;

  return 1;
}


int SwapPersons(unsigned int personid1,unsigned int personid2)
{
  char tmpstr[128];
  unsigned int * tmp_int_ptr;
  unsigned int tmp_int;


  strcpy(tmpstr,persons[personid1].name);
  strcpy(persons[personid1].name,persons[personid2].name);
  strcpy(persons[personid2].name,tmpstr);

  strcpy(tmpstr,persons[personid1].callname);
  strcpy(persons[personid1].callname,persons[personid2].callname);
  strcpy(persons[personid2].callname,tmpstr);

  tmp_int_ptr = persons[personid1].possible_jobs;
  persons[personid1].possible_jobs=persons[personid2].possible_jobs;
  persons[personid2].possible_jobs=tmp_int_ptr;

  tmp_int_ptr = persons[personid1].possible_jobs_taken_this_month;
  persons[personid1].possible_jobs_taken_this_month=persons[personid2].possible_jobs_taken_this_month;
  persons[personid2].possible_jobs_taken_this_month=tmp_int_ptr;

  tmp_int_ptr = persons[personid1].possible_jobs_max_this_month;
  persons[personid1].possible_jobs_max_this_month=persons[personid2].possible_jobs_max_this_month;
  persons[personid2].possible_jobs_max_this_month=tmp_int_ptr;

  tmp_int = persons[personid1].total_possible_jobs;
  persons[personid1].total_possible_jobs=persons[personid2].total_possible_jobs;
  persons[personid2].total_possible_jobs=tmp_int;

  tmp_int = persons[personid1].jobs_per_month;
  persons[personid1].jobs_per_month=persons[personid2].jobs_per_month;
  persons[personid2].jobs_per_month=tmp_int;

  tmp_int = persons[personid1].total_jobs_this_month;
  persons[personid1].total_jobs_this_month=persons[personid2].total_jobs_this_month;
  persons[personid2].total_jobs_this_month=tmp_int;

  tmp_int = persons[personid1].total_jobs_ever_done;
  persons[personid1].total_jobs_ever_done=persons[personid2].total_jobs_ever_done;
  persons[personid2].total_jobs_ever_done=tmp_int;

  tmp_int = persons[personid1].total_vacation_ever_taken;
  persons[personid1].total_vacation_ever_taken=persons[personid2].total_vacation_ever_taken;
  persons[personid2].total_vacation_ever_taken=tmp_int;

  tmp_int = persons[personid1].std_deviation_jobs;
  persons[personid1].std_deviation_jobs=persons[personid2].std_deviation_jobs;
  persons[personid2].std_deviation_jobs=tmp_int;

  return 1;
}


int RemovePersonFromArray(unsigned int personid)
{
  if ( loaded_persons == 0 )
    {
      return 1;
    }
  int i=personid;
  while  ( i < loaded_persons-1 )
    {
      SwapPersons(i,i+1);
      ++i;
    }
  --loaded_persons;
  return 1;
}


unsigned int GetTotalJobidAssignmentsAtDay(unsigned int day,unsigned int jobid)
{
    return year[day].job_assignments[jobid].total_persons_assigned_to;
}

int Memory_CheckDayJobPersonAssignment(unsigned int day,unsigned int jobid,unsigned int personid)
{
    int i=0;
    while ( i<GetTotalJobidAssignmentsAtDay(day,jobid) )
      {
         if ( year[day].job_assignments[jobid].assignment_to_person[i] == personid )
           {
             return 1;
           }
         ++i;
      }
    return 0;
}

int Memory_AddDayJobPersonAssignment(unsigned int day,unsigned int jobid,unsigned int personid)
{
    if ( GetTotalJobidAssignmentsAtDay(day,jobid) >= MAX_PERSONS_PER_JOB )
      {
          fprintf(stderr,"Could not add job to person , we are past the maximum memory for each job \n");
          return 0;
      }

    if ( GetTotalJobidAssignmentsAtDay(day,jobid) >= jobs[jobid].persons_needed )
      {
          fprintf(stderr,"Could not add job to person , Job is full of people \n");
          return 0;
      }
    // GetTotalJobidAssignmentsAtDay(day,jobid) is year[day].job_assignments[jobid].total_persons_assigned_to
    int i=year[day].job_assignments[jobid].total_persons_assigned_to;
    year[day].job_assignments[jobid].assignment_to_person[i]=personid;
    ++year[day].job_assignments[jobid].total_persons_assigned_to;

    return 1;
}



int Memory_RemoveDayJobPersonAssignment(unsigned int day,unsigned int jobid,unsigned int personid)
{
    int total_persons_on_job_day = year[day].job_assignments[jobid].total_persons_assigned_to;
    if ( total_persons_on_job_day  <= 0 )
      {
          return 1;
      }

    int i=0;
    while ( i < total_persons_on_job_day )
      {
         if ( year[day].job_assignments[jobid].assignment_to_person[i] == personid )
            {
                year[day].job_assignments[jobid].assignment_to_person[i]=year[day].job_assignments[jobid].assignment_to_person[total_persons_on_job_day-1];
                --year[day].job_assignments[jobid].total_persons_assigned_to;
                return 1;
            }
         ++i;
      }


    return 1;
}


int Memory_SwapPersonJobsAtDays(unsigned int personid_1,unsigned int day_1,unsigned int jobid_1,unsigned int personid_2,unsigned int day_2,unsigned int jobid_2)
{
    if ( ( !Memory_CheckDayJobPersonAssignment(day_1,jobid_1,personid_1) ) || ( !Memory_CheckDayJobPersonAssignment(day_2,jobid_2,personid_2) ) )
     {
          fprintf(stderr,"Error Memory_SwapPersonJobsAtDays persons %u and %u dont share jobs %u %u at days %u and %u\n",personid_1,personid_2,jobid_1,jobid_2,day_1,day_2);
     }

    Memory_RemoveDayJobPersonAssignment(day_1,jobid_1,personid_1);
    Memory_RemoveDayJobPersonAssignment(day_2,jobid_2,personid_2);
    Memory_AddDayJobPersonAssignment(day_1,jobid_1,personid_2);
    Memory_AddDayJobPersonAssignment(day_2,jobid_2,personid_1);

    return 1;
}


int Error(char * description)
{
  fprintf(stderr,"Error : %s \n",description);
  return 0;
}

