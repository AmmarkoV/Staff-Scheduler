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

MAINFILES="StaffManagment.cpp StaffSchedulerApp.cpp StaffSchedulerMain.cpp VacationManagment.cpp WorkManagment.cpp"
SUBLIBS="ScheduleCreator/libScheduleCreator.a InputParser/libInputParser_C.a"

g++ $MAINFILES $SUBLIBS `wx-config --libs` `wx-config --cxxflags` -L. -pthread -o bin/Release/StaffScheduler


echo "Done.."
exit 0
