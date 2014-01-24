/* 
 * File:   main.cpp
 * Author: elysiunk
 *
 * Created on 28 novembre 2013, 17:04
 */

#include <cstdlib>
#include <iostream>
#include "parseFile.h"
#include "routine.h"
#include "school.h"


using namespace std;

void test3() {
    School s(14);
    
    s.display();
//    
//    s.nb_prof_ok();
//    s.nb_lectures_ok();
//    
//    s.rout();
    
    return;
                
}

int main(int argc, char* argv[]) {
   test3(); 
   
   return 0;
}