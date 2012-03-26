#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ScheduleCreatorCore.h"
#include "SCPerson.h"
#include "SCJob.h"
#include "ScheduleSolver.h"
#include "ScheduleSorting.h"

unsigned int TRY_TO_BALANCE_JOBS = 1;



int FindPersonWithLessJobsForJob(unsigned int day,unsigned int jobid,unsigned int tight_schedule)
{
    int selected_personid=0;
    persons[selected_personid].total_jobs_this_month=10000;


    if (TRY_TO_BALANCE_JOBS)  { SortPeopleBetterForJobFirst(person_sorting_1,jobid); }

    int person_iterator=1;
    int personid=1;
    while (person_iterator<loaded_persons)
    {
      if (TRY_TO_BALANCE_JOBS)
       {
          personid=person_sorting_1[person_iterator].index;
          if (( personid < 1 ) || ( personid >= loaded_persons ))
            {
                fprintf(stderr,"Erroneous value returned by Sorting function (day %u,job %u,person %u)!\n",day,jobid,personid);
                personid=person_iterator;
            }
       }  else
       {
         personid=person_iterator;
       }


      if ( persons[selected_personid].total_jobs_this_month > persons[personid].total_jobs_this_month )
      {
         if (Person_WillBeAbleToDoJobAtDay(personid,jobid,day,tight_schedule) )
          {
              selected_personid = personid;
          }
      }
       ++person_iterator;
    }

    return selected_personid;
}



int Solve(unsigned int from_day,unsigned int to_day)
{
   if ( from_day > to_day ) { return 0; }
   if ( loaded_jobs == 0 ) { return 0; }
   if ( loaded_persons == 0 ) { return 0; }

   ClearMonthDays(from_day,to_day);
   unsigned int personid=1;
   int day=from_day-1;
   while (day < to_day)
    {
      int jobid=1;
      while ( jobid < year[day].jobs_assigned_to_day )
      {
        if ( year[day].day_locked ) { fprintf(stderr,"Day %u is locked !\n",day); }
          else
        if ( jobs[jobid].total_possible_persons > 0 )
        {
          int slots_to_fill=0;
          while ( slots_to_fill < Job_GetPersonsNeeded(jobid) )
          {


         personid=FindPersonWithLessJobsForJob(day,jobid,0);
         if ( personid == 0 )
           {
             fprintf(stderr,"Could not find person with loose timing .. \n");
             personid=FindPersonWithLessJobsForJob(day,jobid,1);
             if ( personid == 0 )
             {
               if ( ReplaceJobOfPersonWithOtherPerson(day,person_sorting_1[1].index) )
                {
                     personid = person_sorting_1[1].index;
                }

               if ( personid == 0 )
                {
                 fprintf(stderr," neither with strict! \n FAILED TO FILL JOB %s :(  \n",jobs[jobid].name);
                 break;
                }
             } else
             {
              fprintf(stderr," but found with strict \n");
             }
           }

           if (Person_WillBeAbleToDoJobAtDay(personid,jobid,day,1))
            {
              Person_AssignJobAtDay(day,personid,jobid);
            }

            ++slots_to_fill;
          }

        } else
        {
            fprintf(stderr,"JOB %s DOESN`T HAVE ANY PERSONS TO DO IT !\n",jobs[jobid].name);
        }

        ++jobid;
      }
      ++day;
    }

  return 1;
}


unsigned int HeuristicJ(unsigned int personid,unsigned int jobid)
{
  unsigned int jobratio = Person_GetSumOfThisJobForThisMonth(personid,jobid) * 1000 ;
  if ( jobratio > jobs[jobid].tmp_per_day_ratio  )
    {
      jobratio = jobratio -  jobs[jobid].tmp_per_day_ratio;
    } else
    {
      jobratio = jobs[jobid].tmp_per_day_ratio - jobratio;
    }
  return jobratio;
}

inline unsigned int HeuristicDay(unsigned int personid,unsigned int day)
{
  unsigned int jobid = Person_GetJobAtDay(personid,day);
  return HeuristicJ(personid,jobid);
}

inline unsigned int AbsDifference ( unsigned int num1,unsigned int num2)
{
    if ( num1 > num2 ) { return num1-num2;}
    return num2-num1;
}

int ImproveSolutionBySwapping(unsigned int from_day,unsigned int to_day)
{
   if ( from_day > to_day ) { return 0; }
   if ( loaded_jobs == 0 ) { return 0; }
   if ( loaded_persons == 0 ) { return 0; }


   int personid_2=1;
   int personid_1=1;

   unsigned int jobid=0;
   double tmp_double;
   while ( jobid < loaded_jobs )
    {
      if ( jobs[jobid].total_possible_persons != 0 )
       {
        tmp_double =  (double)  (to_day-from_day+1) / jobs[jobid].total_possible_persons ;
        tmp_double = 1000 * tmp_double;
        jobs[jobid].tmp_per_day_ratio = (unsigned int ) tmp_double;

        fprintf(stderr,"Job %s has %u total persons and for %u days -> ",jobs[jobid].name,jobs[jobid].total_possible_persons,(to_day-from_day+1));
       fprintf(stderr,"%4.2f to %u \n",tmp_double,jobs[jobid].tmp_per_day_ratio);
       }

      ++jobid;
    }


   unsigned int stddev_1,stddev_2,stdsum;
   unsigned int new_stddev_1,new_stddev_2,new_stdsum;

   int day=from_day-1;
   while (day < to_day)
    {
        personid_1=1;
        while ( personid_1 < loaded_persons )
         {
           personid_2=1;
           while ( personid_2 < loaded_persons )
           {
             if ( personid_1 == personid_2 )
                {
                } else
                {
                    //fprintf(stderr,"Trying Swapping persons %u , %u at day %u\n",personid_1,personid_2,day);
                    stddev_1= HeuristicDay(personid_1,day);
                    stddev_2= HeuristicDay(personid_2,day);
                    stdsum = stddev_1 + stddev_2;

                    if ( SwapPersonJobsAtDays(personid_1,day,personid_2,day) )
                    {

                      new_stddev_1= HeuristicDay(personid_1,day);
                      new_stddev_2= HeuristicDay(personid_2,day);
                      new_stdsum = new_stddev_1 + new_stddev_2;


                     if ( ( stdsum>new_stdsum ) )
                      {
                         fprintf(stderr,"Increased success rate from %u,%u to %u,%u for persons %u,%u \n",stddev_1,stddev_2,new_stddev_1,new_stddev_2,personid_1,personid_2);
                          // WE ` ve increased our success rate
                      } else
                      {
                         // ROLL BACK
                         SwapPersonJobsAtDays(personid_1,day,personid_2,day);
                      }
                    }

                }
               ++personid_2;
           }


             ++personid_1;
         }
        ++day;
    }

  return 1;
}

