#include "SCCoreMemory.h"
#include "ScheduleCreatorFileIO.h"
#include "ScheduleCreator.h"
#include "ScheduleCreatorCore.h"
#include "../InputParser/InputParser_C.h"

int LoadPersonsFile(char * filename)
{
  FILE * fp = fopen(filename,"r");
  if (fp == 0)
    {
      return 0;
    }


  ClearCorePersons();
  char line1[4096]= {0};

  struct InputParserC * ipc=0;
  ipc = InputParser_Create(512,5);

  unsigned int total_persons_to_load = 0;
  unsigned int person_being_loaded = 0;

  while (!feof(fp))
    {
      int retres = (fgets(line1,4096,fp)!=0 );

      if ( retres != 0 )

        {
          int res = InputParser_SeperateWords(ipc,line1,1);
          if ( res == 0 ) { }
          else if ( InputParser_WordCompare(ipc,0,"loaded_persons",14)==1 )
            {
              total_persons_to_load = InputParser_GetWordInt(ipc,1);
              if ( total_persons_to_load >= total_persons )
                {
                  /* todo */ //  total_persons_to_load +=100;
                }
            }
          else if ( InputParser_WordCompare(ipc,0,"person",6)==1 )
            {
              char name[128]= {0};
              char callname[128]= {0};
              InputParser_GetWord(ipc,1,name,128);
              InputParser_GetWord(ipc,2,callname,128);
              SC_AddPerson(name,callname,0,0);
            }
          else if ( InputParser_WordCompare(ipc,0,"person_data",11)==1 )
            {
              person_being_loaded = InputParser_GetWordInt(ipc,1);
              if ( person_being_loaded < loaded_persons )
                {
                  persons[person_being_loaded].total_possible_jobs = 0; /*OMMITED , WILL BE COUNTED BY JOB STATEMENTSInputParser_GetWordInt(ipc,2);*/
                  persons[person_being_loaded].jobs_per_month = InputParser_GetWordInt(ipc,3);
                  persons[person_being_loaded].total_jobs_this_month = /*InputParser_GetWordInt(ipc,4);*/
                    persons[person_being_loaded].total_jobs_ever_done = InputParser_GetWordInt(ipc,5);
                  persons[person_being_loaded].total_vacation_ever_taken = InputParser_GetWordInt(ipc,6);
                }
            }
          else if ( InputParser_WordCompare(ipc,0,"job",3)==1 )
            {
              person_being_loaded = InputParser_GetWordInt(ipc,1);
              if ( person_being_loaded < loaded_persons )
                {
                  char name[128]= {0};
                  InputParser_GetWord(ipc,2,name,128);
                  unsigned int jobid = GetJobIDFromJobName(name);
                  if ( jobid == 0 )
                    {
                      Error("Job could not be found while loading \n");
                    }
                  else
                    {
                      SC_AddPossibleJobToPerson(person_being_loaded,jobid,0);
                      persons[person_being_loaded].possible_jobs_taken_this_month[jobid] = InputParser_GetWordInt(ipc,3);
                      persons[person_being_loaded].possible_jobs_max_this_month[jobid] = InputParser_GetWordInt(ipc,4);
                    }
                }
            }
        }
    }


  if ( loaded_persons != total_persons_to_load )
    {
      Error("Loaded Persons != Expected persons to load \n");
    }

  loaded_persons = total_persons_to_load;
  fclose(fp);
  return 1;
}

int SavePersonsFile(char * filename)
{
  fprintf(stderr,"SavePersonsFile(%s)\n",filename);
  FILE * fp = fopen(filename,"w");
  if (fp == 0)
    {
      return 0;
    }
  fprintf(fp,"loaded_persons(%u)\n",loaded_persons);
  int personid =0;
  while ( personid < loaded_persons )
    {
      fprintf(fp,"\n# PERSON %s DATA --------------------\n",persons[personid].name);
      fprintf(fp,"person(%s,%s,%s,%s)\n",persons[personid].name,persons[personid].callname," "," ");
      fprintf(fp,"person_data(%u,%u,%u,%u,%u,%u)\n",
              personid,
              persons[personid].total_possible_jobs,
              persons[personid].jobs_per_month,
              persons[personid].total_jobs_this_month,
              persons[personid].total_jobs_ever_done,
              persons[personid].total_vacation_ever_taken);

      int jobsofperson=0;
      while ( jobsofperson < persons[personid].total_possible_jobs )
        {
          int jobid = persons[personid].possible_jobs[jobsofperson];
          fprintf(fp,"job(%u,%s,%u,%u)\n",personid,jobs[jobid].name,persons[personid].possible_jobs_taken_this_month[jobid],persons[personid].possible_jobs_max_this_month[jobid]);
          ++jobsofperson;
        }
      ++personid;
    }
  fprintf(fp,"\n");
  fclose(fp);
  return 1;
}

int LoadJobFile(char * filename)
{
  FILE * fp = fopen(filename,"r");
  if (fp == 0)
    {
      return 0;
    }


  ClearCoreJobs();
  char line1[4096]= {0};

  struct InputParserC * ipc=0;
  ipc = InputParser_Create(512,5);

  while (!feof(fp))
    {
      int retres = (fgets(line1,4096,fp)!=0 );

      if ( retres != 0 )

        {
          int res = InputParser_SeperateWords(ipc,line1,1);
          if ( res == 0 ) { }
          else if ( InputParser_WordCompare(ipc,0,"job",3)==1 )
            {
              char name[128]= {0};
              InputParser_GetWord(ipc,1,name,128);
              SC_AddJob(name,InputParser_GetWordInt(ipc,2),InputParser_GetWordInt(ipc,6)); /*TODO LAST 1 IS TOTAL PEOPLE TO ADD*/
              jobs[loaded_jobs-1].difficulty = InputParser_GetWordInt(ipc,3);
              // jobs[loaded_jobs-1].total_possible_persons = InputParser_GetWordInt(ipc,4);
              jobs[loaded_jobs-1].tmp_per_day_ratio = InputParser_GetWordInt(ipc,5);
              //jobs[loaded_jobs-1].persons_needed = InputParser_GetWordInt(ipc,6);
            }
        }
    }
  fclose(fp);
  return 1;
}

int SaveJobFile(char * filename)
{
  fprintf(stderr,"SaveJobFile(%s)\n",filename);
  FILE * fp = fopen(filename,"w");
  if (fp == 0)
    {
      return 0;
    }
  fprintf(fp,"loaded_jobs(%u)\n",loaded_jobs);
  int jobid =0;
  while ( jobid < loaded_jobs )
    {
      fprintf(fp,"\n# JOB %s DATA --------------------\n",jobs[jobid].name);
      fprintf(fp,"job(%s,%u,%u,%u,%u,%u)\n",jobs[jobid].name,
              jobs[jobid].credits,
              jobs[jobid].difficulty,
              jobs[jobid].total_possible_persons,
              jobs[jobid].tmp_per_day_ratio,
              jobs[jobid].persons_needed
             );

      fprintf(fp,"job_timing(%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u)\n"
              ,jobid
              ,jobs[jobid].repeat_cycle
              ,0
              ,0
              ,0
              ,jobs[jobid].possible_at_days_of_week[0]
              ,jobs[jobid].possible_at_days_of_week[1]
              ,jobs[jobid].possible_at_days_of_week[2]
              ,jobs[jobid].possible_at_days_of_week[3]
              ,jobs[jobid].possible_at_days_of_week[4]
              ,jobs[jobid].possible_at_days_of_week[5]
              ,jobs[jobid].possible_at_days_of_week[6]
             );
      ++jobid;
    }
  fprintf(fp,"\n");
  fclose(fp);
  return 1;
}

int AutoSave()
{
  SaveJobFile("autosave_job");
  SavePersonsFile("autosave_persons");
  return 1;
}


int AutoLoad()
{
  LoadJobFile("autosave_job");
  LoadPersonsFile("autosave_persons");
  return 1;
}
