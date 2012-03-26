#ifndef SCHEDULESOLVER_H_INCLUDED
#define SCHEDULESOLVER_H_INCLUDED

int FindPersonWithLessJobsForJob(unsigned int day,unsigned int jobid,unsigned int tight_schedule);
unsigned int HeuristicJ(unsigned int personid,unsigned int jobid);
int Solve(unsigned int from_day,unsigned int to_day);
int ImproveSolutionBySwapping(unsigned int from_day,unsigned int to_day);
#endif // SCHEDULESOLVER_H_INCLUDED
