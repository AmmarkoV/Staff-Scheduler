#!/bin/bash
echo "Hand made make script for Staff Scheduler binary .." 
echo "Written by Ammar Qammaz a.k.a AmmarkoV :) "

cd InputParser
./make
cd ..

cd ScheduleCreator
./make
cd ..


echo "Compiling files.."

g++ StaffManagment.cpp StaffManagment.h StaffSchedulerApp.cpp StaffSchedulerApp.h StaffSchedulerMain.cpp StaffSchedulerMain.h VacationManagment.cpp VacationManagment.h WorkManagment.cpp WorkManagment.h ScheduleCreator/libScheduleCreator.a InputParser/libInputParser.a  `wx-config --libs` `wx-config --cxxflags` -L. -pthread -o bin/Debug/StaffScheduler


echo "Done.."
exit 0
