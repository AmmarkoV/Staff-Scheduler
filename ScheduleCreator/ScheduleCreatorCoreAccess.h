#ifndef SCHEDULECREATORCOREACCESS_H_INCLUDED
#define SCHEDULECREATORCOREACCESS_H_INCLUDED




int CoreAddPerson(char * name,char *callname,unsigned int total_work,unsigned int work_per_month);
int CoreRemovePerson(unsigned int personid);
int CorePersonCantWorkBetweenDates(unsigned int personid,unsigned int startdate,unsigned int enddate);

int CoreAddPossibleJobToPerson(unsigned int personid,unsigned int jobid,unsigned int max_job_times);
int CoreRemovePossibleJobFromPerson(unsigned int personid,unsigned int jobid);
int CoreAddJob(char * name,unsigned int units,unsigned int persons_needed);



char * CoreGetJobsStr(unsigned int jobid,unsigned int field);
int CoreGetJobsInt(unsigned int jobid,unsigned int field);
int CoreGetTotalJobs();
char * CoreGetPersonsStr(unsigned int personid,unsigned int field);
void CoreSetPersonsStr(unsigned int personid,unsigned int field,char * str);
int CoreGetPersonsInt(unsigned int personid,unsigned int field);
int CoreGetTotalPersons();
int CoreGetTotalPersonPossibleJobs(unsigned int personid);
int CoreGetPersonsPossibleJobsInt(unsigned int personid,unsigned int field);
int CoreGetPersonsPossibleJobsNumber(unsigned int personid,unsigned int field);

#endif // SCHEDULECREATORCOREACCESS_H_INCLUDED
