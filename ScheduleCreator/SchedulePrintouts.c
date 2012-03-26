#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SCCoreMemory.h"
#include "ScheduleCreatorCalender.h"
#include "ScheduleCreatorCore.h"
#include "SCPerson.h"
#include "ScheduleStatistics.h"
#include "SchedulePrintouts.h"


int HTMLHeaderStart(FILE *fp,char * title)
{
   fprintf(fp,"<html>\n");
   fprintf(fp,"<head>\n");
   fprintf(fp,"  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">");
   fprintf(fp,"  <title>%s</title>",title);
      fprintf(fp,"   <style type=\"text/css\">");
      fprintf(fp,"     TD {text-align: center} ");
      fprintf(fp,"   </style>");
   fprintf(fp,"</head>\n");

   fprintf(fp,"<body>\n");

   return 1;
}

int HTMLHeaderEnd(FILE *fp)
{

   fprintf(fp,"</body>\n");
   fprintf(fp,"</html>\n");

   return 1;
}


int PrintOutHtml(char * filename)
{
   if (!CoreIsOk()) { fprintf(stderr,"CORE IS NOT OK ABORTING PRINTOUT\n"); return 0; }


   fprintf(stderr,"Generating PrintOutHtml %s \n",filename);
   FILE * fp = fopen(filename,"w");
   if (fp == 0) { return 0; }


   HTMLHeaderStart(fp,(char *) "Συγκεντρωτικό Πρόγραμμα κάθε μέρας");
   fprintf(fp,"<table  border=1>\n");
   fprintf(fp,"   <tr>\n");
     int i = 0 ;
       while ( i < 31 )
        {
            if (i%8==0)
             {
              fprintf(fp,"   </tr>\n");
              fprintf(fp,"   <tr>\n");
             }
                fprintf(fp,"      <td>\n");
                fprintf(fp,"          <table>\n");

                  fprintf(fp,"           <tr height=30><td colspan=2>\n");
                   fprintf(fp,"             <h3>%u</h3>\n",i+1);
                  fprintf(fp,"           </td></tr>\n");

                int z=1;
                while ( z < year[i].jobs_assigned_to_day )
                 {
                     if (z%2==0) { fprintf(fp,"           <tr height=30 bgcolor=\"#FFFFFF\">\n"); } else
                                 { fprintf(fp,"           <tr height=30 bgcolor=\"#EEEEEE\">\n"); }

                     fprintf(fp,"             <td>%s</td><td>",jobs[z].name);
                        int pers_need = GetTotalJobidAssignmentsAtDay(i,z);
                        int pers = 0;
                        while ( pers < pers_need  )
                          {
                           fprintf(fp,"%s<br>",persons[year[i].job_assignments[z].assignment_to_person[pers]].name);
                           ++pers;

                          }
                     fprintf(fp,"           </td>\n</tr>\n");
                     ++z;
                 }
                fprintf(fp,"          </table>\n");
                fprintf(fp,"      </td>\n");
            ++i;
        }
   fprintf(fp,"   </tr>\n");
   fprintf(fp,"</table>\n");

   HTMLHeaderEnd(fp);



   fclose(fp);
 return 1;
}



int PrintOutNVerticalDaystHtml(char * filename,unsigned int total_rows)
{
   if (!CoreIsOk()) { fprintf(stderr,"CORE IS NOT OK ABORTING PRINTOUT\n"); return 0; }


   fprintf(stderr,"Generating NVerticalDaystHtml %s \n",filename);
   FILE * fp = fopen(filename,"w");
   if (fp == 0) { return 0; }


   HTMLHeaderStart(fp,(char *) "Συγκεντρωτικό Πρόγραμμα κάθε μέρας");
   fprintf(fp,"<table  border=0>\n");
   fprintf(fp,"   <tr><td>Ημερομηνία</td>\n");
     int jobid=1;
     while ( jobid < total_jobs )
       {
           fprintf(fp,"<td><b>%s</b></td>",Job_GetSValue(jobid,0));
           ++jobid;
       }

   fprintf(fp,"   </tr>\n");

     int rows=0;
     while ( rows < total_rows )
       {
          fprintf(fp,"   <tr><td>%u</td>\n",rows);
           jobid=1;
           while ( jobid < total_jobs )
           {
             int person_slot = 0;
              fprintf(fp,"   <td>\n");
              while ( person_slot < Job_GetPersonsNeeded(jobid) )
               {
                     int personid = GetPersonThatHasJobAtDay(jobid,rows,person_slot);
                     fprintf(fp,"%s ",Person_GetSValue(personid,0));
                   ++person_slot;
               }
               fprintf(fp,"   </td>\n");
             ++jobid;
           }
          fprintf(fp,"   </tr>\n");


           ++rows;
       }
   fprintf(fp,"</table>\n");

   HTMLHeaderEnd(fp);



   fclose(fp);
 return 1;
}



int PrintOutDistributionHTML(char * filename)
{

   fprintf(stderr,"Generating DistributionHTML %s \n",filename);
   FILE * fp = fopen(filename,"w");
   if (fp == 0) { return 0; }


   HTMLHeaderStart(fp,(char *) "Μηνιαίο Πρόγραμμα διασποράς εργασιών ανα άτομο");
   int i=0;
   fprintf(fp,"<table border=1>\n");
      fprintf(fp,"<tr>\n");
             fprintf(fp,"<td><h2>Ονόματα</h2></td><td><h2>Υπηρεσίες</h2></td><td><h2>Έξοδοι</h2></td><td><h4>Απόκλιση<br>Υπηρεσιών</h4></td>\n");
             i=1;
             while (i<loaded_jobs)
              {
                 fprintf(fp,"      <td>\n");
                 fprintf(fp,"        <h4>%s</h4> \n",jobs[i].name);
                 if (  jobs[i].total_possible_persons>0 )
                     {
                        fprintf(fp,"          (%4.2f/ατ.) ",(double) total_days / jobs[i].total_possible_persons);
                     }
                 fprintf(fp,"      </td>\n");
                  ++i;
              }




      i = 1 ;
       while ( i < loaded_persons )
        {
          fprintf(fp,"   <tr>\n");
          fprintf(fp,"      <td>\n");
          fprintf(fp,"        <h4>%s</h4>\n",persons[i].name);
          fprintf(fp,"      </td>\n");

          fprintf(fp,"      <td>\n");
          fprintf(fp,"        %u \n",persons[i].total_jobs_this_month);
          fprintf(fp,"      </td>\n");

          fprintf(fp,"      <td>\n");
          fprintf(fp,"        %u \n",total_days-persons[i].total_jobs_this_month);
          fprintf(fp,"      </td>\n");

          fprintf(fp,"      <td>\n");
          float keep_as_a_float = (float) JobStdDeviationForPerson(i)/1000;
          fprintf(fp,"        %4.2f<br>(%u) \n",keep_as_a_float,persons[i].total_possible_jobs);
          fprintf(fp,"      </td>\n");

          int z=1;
          while ( z<loaded_jobs )
           {
              fprintf(fp,"      <td>\n");
              unsigned int tot_job_pers = Person_GetSumOfThisJobForThisMonth(i,z);
              fprintf(fp,"        %u \n",tot_job_pers);
              if ((Person_CanDoJob(i,z))&&(  jobs[z].total_possible_persons>0 ))
                     {
                        double deviation = (double) tot_job_pers - ((double) total_days / jobs[z].total_possible_persons) ;
                        if ( deviation > 0 )
                         {
                          fprintf(fp,"          <font color=#00FF00><br>(%4.2f)</font> ",deviation) ;
                         }
                           else
                         {
                          fprintf(fp,"          <font color=#FF0000><br>(%4.2f)</font> ",deviation) ;
                         }
                     }
              fprintf(fp,"      </td>\n");
              ++z;
           }

          fprintf(fp,"   </tr>\n");
          ++i;
        }
   fprintf(fp,"</table>\n");
   HTMLHeaderEnd(fp);


   fclose(fp);
  return 1;

}




int PrintOutVacationsHTML(char * filename)
{
   fprintf(stderr,"Generating VacationsHTML %s \n",filename);
   FILE * fp = fopen(filename,"w");
   if (fp == 0) { return 0; }

   HTMLHeaderStart(fp,(char *) "Μηνιαίο Πρόγραμμα ανα άτομο");

   fprintf(fp,"<table>\n");
          fprintf(fp,"   <tr>\n");
          fprintf(fp,"      <td colspan=2>\n");
          fprintf(fp,"         %u / %u \n",loaded_month,loaded_year);
          fprintf(fp,"      </td>\n");
      int day=0;
      while ( day < 31 )
        {
          fprintf(fp,"      <td>\n");
          fprintf(fp,"        %s\n",GetWeekDayStr(GetWeekDay(day+1,loaded_month,loaded_year)));
          fprintf(fp,"      </td>\n");
          ++day;
        }
         fprintf(fp,"   </tr>\n");


      int i = 1 ;
       while ( i < loaded_persons )
        {
          fprintf(fp,"   <tr><font size=1>\n");
          fprintf(fp,"      <td>\n");
          fprintf(fp,"        <b>%s</b>\n",persons[i].name);
          fprintf(fp,"      </td>\n");
          fprintf(fp,"      <td>\n");
          fprintf(fp,"        %u υπηρεσίες \n",persons[i].total_jobs_this_month);
          fprintf(fp,"      </td>\n");
          day=0;
          while ( day < 31 )
           {
               if (Person_HasVacationAtDay(i,day) == 1 )  {fprintf(fp,"      <td bgcolor=\"#FF0000\">%u<br>ΑΔΕΙΑ</td>\n",day+1); } else
               if ( Person_GetJobAtDay(i,day) == 0 )    {fprintf(fp,"      <td bgcolor=\"#ccffcc\">%u<br>&nbsp;</td>\n",day+1); } else
                                                         {fprintf(fp,"      <td bgcolor=\"#fffeaa\" >%u<br>%s</td>\n",day+1,jobs[Person_GetJobAtDay(i,day)].name);}

               fprintf(fp,"      \n");
               ++day;
           }

          fprintf(fp,"   </font></tr>\n");
          ++i;
        }
   fprintf(fp,"</table>\n");


   HTMLHeaderEnd(fp);



   fclose(fp);
  return 1;
}
