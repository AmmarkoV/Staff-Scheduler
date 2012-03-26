#ifndef SCHEDULECREATORCORE_H_INCLUDED
#define SCHEDULECREATORCORE_H_INCLUDED

#define MAX_TIMETABLE_ITEMS 12
#define MAX_PERSONS_PER_JOB 12

enum RepeatCycleEnum
{
   DAILY = 0 ,

   UNDER_THIS_VALUE_IS_EVERY_N_DAYS = 665 ,
   ONCE ,
   WEEKLY ,
   MONTHLY  ,
   YEARLY ,

};

enum DaysOfWeekEnum
{
   MONDAY = 0 ,
   TUESDAY ,
   WEDNESDAY ,
   THURSDAY ,
   FRIDAY ,
   SATURDAY ,
   SUNDAY
};

struct TimetableItem
{
   signed int day_difference_to_today;

   unsigned int from_hour;
   unsigned int from_minute;

   unsigned int to_hour;
   unsigned int to_minute;

};


struct JobTimetable
{
   unsigned int total_items;
   struct TimetableItem item[MAX_TIMETABLE_ITEMS];
};

struct Job
{
   char name[128];

   unsigned int credits;
   unsigned int difficulty;
   unsigned int persons_needed;
   unsigned int total_possible_persons;

   unsigned int repeat_cycle;
   unsigned int possible_at_days_of_week[7];

   struct JobTimetable timetable;

   unsigned int tmp_per_day_ratio;
};

struct Person
{
    /*EACH CHANGE HERE MUST BE MADE TO SCCoreMemory ( see swapping etc )*/
   char name[128];
   char callname[128];
   unsigned int * possible_jobs; /*dynamika*/
   unsigned int * possible_jobs_taken_this_month; /*apeytheias*/
   unsigned int * possible_jobs_max_this_month; /*apeytheias*/
   unsigned int total_possible_jobs;

   unsigned int jobs_per_month;
   unsigned int total_jobs_this_month;
   unsigned int total_jobs_ever_done;
   unsigned int total_vacation_ever_taken;
   //肉木曜日
   unsigned int std_deviation_jobs; /* / 1000 */
};

struct JobAssignment
{
  unsigned int total_persons_assigned_to;
  unsigned int assignment_to_person[MAX_PERSONS_PER_JOB];
};

struct Day
{
   struct JobAssignment * job_assignments; /*apeytheias*/
   unsigned int jobs_assigned_to_day;

   unsigned int * persons_denied; /*dynamika*/
   unsigned int total_persons_denied;

   unsigned int day_locked;

};


extern struct Job * jobs;
extern unsigned int loaded_jobs;
extern unsigned int total_jobs;

extern struct Person * persons;
extern unsigned int loaded_persons;
extern unsigned int total_persons;

extern struct Day * year;
extern unsigned int loaded_month,loaded_year;
extern unsigned int total_days;



int PersonHasJobAtDay(unsigned int personid,unsigned int day);
int PersonHasJobBeforeDay(unsigned int personid,unsigned int day);
int PersonCanDoJob(unsigned int personid,unsigned int jobid);
int PersonWillBeAbleToDoJobAtDay(unsigned int personid,unsigned int jobid,unsigned int day,unsigned int tight_schedule);

int AssignJobToPerson(unsigned int day ,unsigned int personid,unsigned int jobid);
int RemoveJobFromPerson(unsigned int day ,unsigned int personid,unsigned int jobid);
int ReplaceJobOfPersonWithOtherPerson(unsigned int day,unsigned int personid);
int JobNeedsMorePersonsAtDay(unsigned int day,unsigned int jobid);

int AddVacationToPerson(unsigned int personid,unsigned int day_start , unsigned int total_days_of_vacation);
int RemoveVacationFromPerson(unsigned int personid,unsigned int day_start , unsigned int total_days_of_vacation);

int ClearMonthDays(unsigned int from_date,unsigned int to_date); /* Perimenei date 1-31 ( OXI 0-30 )*/

int PersonHasVacationAtDay(unsigned int personid,unsigned int day);
int AssignVacationToPerson(unsigned int personid,unsigned int day_start , unsigned int day_end);
int GetSumOfThisJobForPersonAtMonth(unsigned int personid,unsigned int jobid);
int GetJobOfPersonAtDay(unsigned int personid,unsigned int day);


int SwapPersonJobsAtDays(unsigned int personid_1,unsigned int day_1,unsigned int personid_2,unsigned int day_2);
int PersonsJobCanBeSwaped(unsigned int personid_1,unsigned int day_1,unsigned int personid_2,unsigned int day_2);

#endif // SCHEDULECREATORCORE_H_INCLUDED
