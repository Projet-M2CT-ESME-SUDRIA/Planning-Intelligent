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
    
    //s.display();
    
    s.nb_prof_ok();
    s.nb_lectures_ok();
    
    s.divideCourses();
    
    s.display_schedule_promos();
    //s.moveCourse();
    s.write_schedule_file();
    cout << "TOUT OK" << endl;
    return;
                
}

int main(int argc, char* argv[]) {

    srand(time(NULL));
    test3(); 
    return 0;
}