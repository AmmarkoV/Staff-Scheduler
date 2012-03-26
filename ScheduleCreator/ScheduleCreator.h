#ifndef SCHEDULECREATOR_H_INCLUDED
#define SCHEDULECREATOR_H_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif

char * SC_Version();

int SC_Init(unsigned int max_persons,unsigned int max_jobs);
int SC_Close();

int SC_AddPerson(char * name,char *callname,unsigned int total_work,unsigned int work_per_month);
int SC_RemovePerson(unsigned int personid);
int SC_PersonCantWorkBetweenDates(unsigned int personid,unsigned int startdate,unsigned int enddate);

int SC_AddPossibleJobToPerson(unsigned int personid,unsigned int jobid,unsigned int max_job_times);
int SC_RemovePossibleJobFromPerson(unsigned int personid,unsigned int jobid);
int SC_AddJob(char * name,unsigned int units,unsigned int persons_needed);


char * SC_GetJobs_Str(unsigned int jobid,unsigned int field);
int SC_GetJobs_Int(unsigned int jobid,unsigned int field);
int SC_GetTotalJobs();
char * SC_GetPersons_Str(unsigned int personid,unsigned int field);
void SC_SetPersons_Str(unsigned int personid,unsigned int field,char * str);
int SC_GetPersons_Int(unsigned int personid,unsigned int field);
int SC_GetTotalPersons();
int SC_GetTotalPersonPossibleJobs(unsigned int personid);
int SC_GetPersonsPossibleJobsInt(unsigned int personid,unsigned int field);
int SC_GetPersonsPossibleJobsNumber(unsigned int personid,unsigned int field);

int SC_Compute();
int SC_Printout();

int SC_Test();

#ifdef __cplusplus
}
#endif

#endif // SCHEDULECREATOR_H_INCLUDED
