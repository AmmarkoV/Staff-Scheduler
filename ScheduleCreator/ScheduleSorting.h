#ifndef SCHEDULESORTING_H_INCLUDED
#define SCHEDULESORTING_H_INCLUDED


#define MAX_JOBS_MONTH_OVERFLOW 1234

struct SortingList
{
    unsigned int index;
    unsigned int value;
};

extern  struct SortingList * person_sorting_1;
extern  struct SortingList * person_sorting_2;

int SortPeopleBetterForJobFirst(struct SortingList * person_sorting,unsigned int jobid);

#endif // SCHEDULESORTING_H_INCLUDED
