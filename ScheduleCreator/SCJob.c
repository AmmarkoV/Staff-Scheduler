#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SCCoreMemory.h"
#include "ScheduleCreatorCore.h"
#include "ScheduleSorting.h"
#include "SCJob.h"

int JobIsOk(unsigned int jobid)
{
  if ( ( jobs == 0 ) || ( jobid>loaded_jobs ) )
    {
      return 0;
    }
  return 1;
}

int Job_Add(char * name,unsigned int units,unsigned int persons_needed)
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


int Job_Remove(char * name,unsigned int units,unsigned int persons_needed)
{
   fprintf(stderr,"Job Remove Not Implemented !!!!!!!\n");
  return 0;
}


int Job_NeedsMorePersonsAtDay(unsigned int day,unsigned int jobid)
{
    if ( year[day].job_assignments[jobid].total_persons_assigned_to < jobs[jobid].persons_needed ) { return 1; }
    if ( year[day].job_assignments[jobid].total_persons_assigned_to >= jobs[jobid].persons_needed ) { fprintf(stderr,"Job_NeedsMorePersonsAtDay mismatch total \n"); return 0; }
    return 0;
}


int Job_AddToTimeTable(unsigned int jobid,signed int day_diff,unsigned int start_h,unsigned int start_m,unsigned int end_h,unsigned int end_m)
{
  if ( !JobIsOk(jobid) ) { fprintf(stderr,"Job is not ok! \n"); return 0; }
  if ( jobs[jobid].timetable.total_items >= MAX_TIMETABLE_ITEMS ) { fprintf(stderr,"Cannot add more segments to timetable \n"); return 0; }

  int timetable_item_id = jobs[jobid].timetable.total_items;

  jobs[jobid].timetable.item[timetable_item_id].day_difference_to_today = day_diff;

  jobs[jobid].timetable.item[timetable_item_id].from_hour = start_h;
  jobs[jobid].timetable.item[timetable_item_id].from_minute = start_m;
  jobs[jobid].timetable.item[timetable_item_id].to_hour = end_h;
  jobs[jobid].timetable.item[timetable_item_id].to_minute = end_m;

  ++jobs[jobid].timetable.total_items;
  return 1;
}

int Job_RemoveFromTimeTable(unsigned int jobid,signed int day_diff,unsigned int start_h,unsigned int start_m,unsigned int end_h,unsigned int end_m)
{
  return 0;
}

int Job_GetPersonsNeeded(unsigned int jobid)
{
    return jobs[jobid].persons_needed;
}

int Job_SetSValue(unsigned int jobid,unsigned int field,char * str)
{
  fprintf(stderr,"Job_SetSValue Not Implemented !!!!!!!\n");
  return  0;
}

char * Job_GetSValue(unsigned int jobid,unsigned int field)
{
  return  jobs[jobid].name;
}

int Job_SetIValue(unsigned int jobid,unsigned int field,int val)
{
  fprintf(stderr,"Job_SetIValue Not Implemented !!!!!!!\n");
  return  0;
}

int Job_GetIValue(unsigned int jobid,unsigned int field)
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

int GetTotalJobs()
{
  return  loaded_jobs;
}

unsigned int GetJobIDFromJobName(char * name)
{
  unsigned int jobid = 0;
  while ( jobid < loaded_jobs )
    {
      fprintf(stderr,"Comparing `%s` with `%s`\n",name,jobs[jobid].name);
      if ( strcmp(name,jobs[jobid].name) == 0 )
        {
          fprintf(stderr," OK\n");
          return jobid;
        }
      ++jobid;
    }
  fprintf(stderr," Failed\n");
  return 0;
}

