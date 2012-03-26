#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SCCoreMemory.h"
#include "ScheduleCreatorCore.h"
#include "SCDays.h"

unsigned int GetPersonThatHasJobAtDay(unsigned int jobid,unsigned int day,unsigned int slot)
{
     if ( year[day].job_assignments[jobid].assignment_to_person[slot] >= total_persons )
      {
          fprintf(stderr,"Error accessing GetPersonThatHasJobAtDay(%u,%u,%u)\n",jobid,day,slot);
          return 0;
      }
     return year[day].job_assignments[jobid].assignment_to_person[slot];
}
