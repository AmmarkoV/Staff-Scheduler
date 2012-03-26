#ifndef SCPERSON_H_INCLUDED
#define SCPERSON_H_INCLUDED

int Person_Add(char * name,char *callname,unsigned int total_work,unsigned int work_per_month);
int Person_Remove(unsigned int personid);
int Person_AddPossibleJob(unsigned int personid,unsigned int jobid,unsigned int max_job_times);
int Person_RemovePossibleJob(unsigned int personid,unsigned int jobid);
int Person_CantWorkBetweenDates(unsigned int personid,unsigned int startdate,unsigned int enddate);


int Person_GetSumOfThisJobForThisMonth(unsigned int personid,unsigned int jobid);
int Person_GetJobAtDay(unsigned int personid,unsigned int day);
int Person_HasVacationAtDay(unsigned int personid,unsigned int day);
int Person_HasJobAtDay(unsigned int personid,unsigned int day);
int Person_HasThisJobAtDay(unsigned int personid,unsigned int jobid,unsigned int day);
int Person_HasJobAtDayBeforeDay(unsigned int personid,unsigned int day);
int Person_CanDoJob(unsigned int personid,unsigned int jobid);
int Person_WillBeAbleToDoJobAtDay(unsigned int personid,unsigned int jobid,unsigned int day,unsigned int tight_schedule);
int Person_AssignJobAtDay(unsigned int day ,unsigned int personid,unsigned int jobid);
int Person_RemoveJobAtDay(unsigned int day ,unsigned int personid,unsigned int jobid);
int ReplaceJobOfPersonWithOtherPerson(unsigned int day,unsigned int personid);
int Person_AddVacation(unsigned int personid,unsigned int day_start , unsigned int total_days_of_vacation);
int Person_RemoveVacation(unsigned int personid,unsigned int day_start , unsigned int total_days_of_vacation);

char * Person_GetSValue(unsigned int personid,unsigned int field);
void Person_SetSValue(unsigned int personid,unsigned int field,char * str);
int Person_GetIValue(unsigned int personid,unsigned int field);

int GetTotalPersons();
int Person_GetTotalPossibleJobs(unsigned int personid);
int Person_GetPossibleJobsInt(unsigned int personid,unsigned int field);
int Person_GetPossibleJobsNumber(unsigned int personid,unsigned int field);

#endif // SCPERSON_H_INCLUDED
