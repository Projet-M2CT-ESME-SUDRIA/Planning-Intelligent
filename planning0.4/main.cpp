/* 
 * File:   main.cpp
 * Author: elysiunk
 *
 * Created on 28 novembre 2013, 17:04
 */

#include <cstdlib>
#include <iostream>
#include "parseFile.h"
#include "school.h"
#include <time.h>


using namespace std;

void createSchedule(School s) {
    s.nb_prof_ok();
    s.nb_lectures_ok();
    
    s.divideCourses();
}

void changePositionCourses(School s) {
    s.getBestSchedule();
    s.moveCourse();
    s.write_schedule_file();
}

int main(int argc, char* argv[]) {

    srand(time(NULL));
    School s(14);
    createSchedule(s);
    changePositionCourses(s);
    return 0;
}