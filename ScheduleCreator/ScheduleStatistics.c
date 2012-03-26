#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "SCCoreMemory.h"
#include "ScheduleCreatorCore.h"
#include "ScheduleStatistics.h"

int DISPLAY_STATISTIC_OUTPUT_CONSOLE = 0;


unsigned int JobStdDeviationForPerson(unsigned int personid)
{
  if (!PersonIsOk(personid))
    {
      return 0;
    }
  double mean = 0.0;
  unsigned int different_jobs = 0;
  if ( DISPLAY_STATISTIC_OUTPUT_CONSOLE ) fprintf(stderr,"Calculating StdDeviation For Person %s \n",persons[personid].name);

  unsigned int i=0,job=0;
  while ( i<persons[personid].total_possible_jobs )
    {
      job=persons[personid].possible_jobs[i];
      mean += persons[personid].possible_jobs_taken_this_month[job];
      if ( DISPLAY_STATISTIC_OUTPUT_CONSOLE ) fprintf(stderr," %u ",persons[personid].possible_jobs_taken_this_month[job]);
      ++different_jobs;
      ++i;
    }


  if ( different_jobs == 1)
    {
      return 0;
    }
  if ( different_jobs == 0)
    {
      return 0;
    }

  mean = (double) (mean / different_jobs);
  if ( DISPLAY_STATISTIC_OUTPUT_CONSOLE ) fprintf(stderr,"Mean is %4.2f ,different jobs %u \n",mean,different_jobs);


  double stddeviation = 0.0;
  double tmp=0.0;
  i=0;
  while ( i<persons[personid].total_possible_jobs )
    {
      job=persons[personid].possible_jobs[i];
      if ( mean > persons[personid].possible_jobs_taken_this_month[job] )
        {
          tmp =  mean-persons[personid].possible_jobs_taken_this_month[job];
        }
      else
        {
          tmp =  persons[personid].possible_jobs_taken_this_month[job] - mean;
        }

      stddeviation += (tmp*tmp);
      ++i;
    }

  if ( different_jobs <= 1)
    {
      fprintf(stderr,"Wtf happened ? \n");
      return 0.0;
    }
  stddeviation = sqrt( stddeviation / (different_jobs-1) );
  if ( DISPLAY_STATISTIC_OUTPUT_CONSOLE ) fprintf(stderr,"StdDeviation is %4.2f \n",stddeviation);

  stddeviation = stddeviation * 1000; /*We want to store it in an int*/
  unsigned int stddeviation_int = (unsigned int) stddeviation ;
  persons[personid].std_deviation_jobs = stddeviation_int;

  return stddeviation_int;
}


