#ifndef SCJOB_H_INCLUDED
#define SCJOB_H_INCLUDED

int Job_Add(char * name,unsigned int units,unsigned int persons_needed);
int Job_Remove(char * name,unsigned int units,unsigned int persons_needed);

int Job_NeedsMorePersonsAtDay(unsigned int day,unsigned int jobid);

int Job_AddToTimeTable(unsigned int jobid,signed int day_diff,unsigned int start_h,unsigned int start_m,unsigned int end_h,unsigned int end_m);
int Job_RemoveFromTimeTable(unsigned int jobid,signed int day_diff,unsigned int start_h,unsigned int start_m,unsigned int end_h,unsigned int end_m);

int Job_GetPersonsNeeded(unsigned int jobid);

int    Job_SetSValue(unsigned int jobid,unsigned int field,char * str);
char * Job_GetSValue(unsigned int jobid,unsigned int field);
int    Job_SetIValue(unsigned int jobid,unsigned int field,int val);
int    Job_GetIValue(unsigned int jobid,unsigned int field);


int GetTotalJobs();
unsigned int GetJobIDFromJobName(char * name);


#endif // SCJOB_H_INCLUDED
