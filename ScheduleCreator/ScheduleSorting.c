#include <stdio.h>
#include <stdlib.h>
#include "ScheduleSorting.h"
#include "ScheduleCreatorCore.h"
#include "SCPerson.h"

struct SortingList * person_sorting_1=0;
struct SortingList * person_sorting_2=0;

int SortPeopleBetterForJobFirst(struct SortingList * person_sorting,unsigned int jobid)
{
  //fprintf(stderr,"Sorting For Job %u !\n",jobid);
  person_sorting[0].index=0;
  person_sorting[0].value=MAX_JOBS_MONTH_OVERFLOW; /**/
  unsigned int i=1;
  while ( i < loaded_persons )
    {
      person_sorting[i].index=i;
      if ( jobid > 0 )
        {
          if ( Person_CanDoJob(i,jobid) )
            {
              person_sorting[i].value = Person_GetSumOfThisJobForThisMonth(i,jobid);
            }
          else
            {
              person_sorting[i].value = MAX_JOBS_MONTH_OVERFLOW-1; /*SAVE THE PROGRAM LOTS OF TIME :P BUT COULD BE BUGGY ?*/
            }
        }
      else if ( jobid == 0  )
        {
          person_sorting[i].value = persons[i].total_jobs_this_month;
        }
      ++i;
    }
  //fprintf(stderr,"PreSorting Survived!\n");

  unsigned int swap_val = 0;
  unsigned int j = 1;
  unsigned int n = loaded_persons;
  for (i = 1; i < n; i++)
    {
      /* back through the area bringing smallest remaining element to position i */
      for (j = n-1; j > i; j--)
        {
          if (person_sorting[j-1].value > person_sorting[j].value)
            {
              swap_val = person_sorting[j-1].value;
              person_sorting[j-1].value = person_sorting[j].value;
              person_sorting[j].value = swap_val;

              swap_val = person_sorting[j-1].index;
              person_sorting[j-1].index = person_sorting[j].index;
              person_sorting[j].index = swap_val;
            }
        }
    }


  if  ( person_sorting[0].value!=MAX_JOBS_MONTH_OVERFLOW  )
    {
      fprintf(stderr,"Error Sorting , mixed zero person!\n");
      return 0;
    }

  /*
  i=0;
  while ( i < loaded_persons )
   {
      fprintf(stderr,"(%u) %u ",i,person_sorting[i].value);
       ++i;
   }
   fprintf(stderr,"\n");
   */


  //fprintf(stderr,"Sorting Survived!\n");

  return 1;
}
