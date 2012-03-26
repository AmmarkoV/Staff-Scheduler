#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ScheduleCreatorCore.h"
#include "SCPerson.h"
#include "ScheduleSorting.h"

struct Job * jobs=0;
unsigned int loaded_jobs=0;
unsigned int total_jobs=0;

struct Person * persons=0;
unsigned int loaded_persons=0;
unsigned int total_persons=0;

struct Day * year=0;
unsigned int loaded_month=2,loaded_year=2011;
unsigned int total_days=31;









/*

  HELPING FUNCIONS


*/




int ClearMonthDays(unsigned int from_date,unsigned int to_date)
{
 int day=from_date-1;
   while (day < to_date)
    {
       year[day].jobs_assigned_to_day = loaded_jobs;
       /*REFRESH JOBS ASSIGNED TO DAY!*/


       int jobid=0;
       while (jobid<loaded_jobs)
        {
          if ( year[day].job_assignments[jobid].total_persons_assigned_to != 0 )
           {
              int z=year[day].job_assignments[jobid].total_persons_assigned_to;
               while ( z>0 )
                {
                    --z;
                    Person_RemoveJobAtDay(day,year[day].job_assignments[jobid].assignment_to_person[z],jobid);
                }
           }
          ++jobid;
        }
        ++day;
    }
  return 1;
}


int SwapPersonJobsAtDaysImplementation(int execute_if_possible,unsigned int personid_1,unsigned int day_1,unsigned int personid_2,unsigned int day_2)
{
    int jobid1  = Person_GetJobAtDay(personid_1,day_1);
    int jobid2 = Person_GetJobAtDay(personid_2,day_2);

    if ( (Memory_CheckDayJobPersonAssignment(day_1,jobid1,personid_1)) && (Memory_CheckDayJobPersonAssignment(day_2,jobid2,personid_2)) )
     {
      if  ( ( Person_CanDoJob(personid_1,jobid2) ) && ( Person_CanDoJob(personid_2,jobid1) ) )
      {
        if (execute_if_possible)
        {

          persons[personid_1].possible_jobs_taken_this_month[jobid1]-=1;
          persons[personid_1].possible_jobs_taken_this_month[jobid2]+=1;

          persons[personid_2].possible_jobs_taken_this_month[jobid1]+=1;
          persons[personid_2].possible_jobs_taken_this_month[jobid2]-=1;

          Memory_SwapPersonJobsAtDays(personid_1,day_1,jobid1,personid_2,day_2,jobid2);
        }
         return 1;
      }
     }


  return 0;
}

int SwapPersonJobsAtDays(unsigned int personid_1,unsigned int day_1,unsigned int personid_2,unsigned int day_2)
{
    return SwapPersonJobsAtDaysImplementation(1,personid_1,day_1,personid_2,day_2);
}

int PersonsJobCanBeSwaped(unsigned int personid_1,unsigned int day_1,unsigned int personid_2,unsigned int day_2)
{
    return SwapPersonJobsAtDaysImplementation(0,personid_1,day_1,personid_2,day_2);
}
