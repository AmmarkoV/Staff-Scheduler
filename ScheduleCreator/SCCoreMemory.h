#ifndef SCCOREMEMORY_H_INCLUDED
#define SCCOREMEMORY_H_INCLUDED

extern unsigned int MAX_CONCURRENT_PERSONS_ON_JOB;
extern unsigned int ACTIVE_MAX_CONCURRENT_PERSONS_ON_JOB;

int PersonIsOk(unsigned int personid);
int CoreIsOk();
int InitCore(unsigned int max_persons,unsigned int max_jobs);
int CloseCore();

int ClearCorePersons();
int ClearCoreJobs();
int ClearCore();

unsigned int GetTotalJobidAssignmentsAtDay(unsigned int day,unsigned int jobid);

int Memory_CheckDayJobPersonAssignment(unsigned int day,unsigned int jobid,unsigned int personid);
int Memory_AddDayJobPersonAssignment(unsigned int day,unsigned int jobid,unsigned int personid);
int Memory_RemoveDayJobPersonAssignment(unsigned int day,unsigned int jobid,unsigned int personid);
int Memory_SwapPersonJobsAtDays(unsigned int personid_1,unsigned int day_1,unsigned int jobid_1,unsigned int personid_2,unsigned int day_2,unsigned int jobid_2);

int RemovePersonFromArray(unsigned int personid);

int Error(char * description);

#endif // SCCOREMEMORY_H_INCLUDED
