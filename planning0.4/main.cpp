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

void test3() {
    
    School s(14);
    
    s.nb_prof_ok();
    s.nb_lectures_ok();
    
    s.divideCourses();
    
    //s.moveCourse();
    return;
                
}

int main(int argc, char* argv[]) {

    srand(time(NULL));
    test3(); 
    return 0;
}