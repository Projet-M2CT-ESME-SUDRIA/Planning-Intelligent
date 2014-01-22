/* 
 * File:   main.cpp
 * Author: elysiunk
 *
 * Created on 28 novembre 2013, 17:04
 */

#include <cstdlib>
#include <iostream>
#include "parseFile.h"
#include "dataInitialisation.h"
#include "routine.h"


using namespace std;

void test3() {
    
    map<int, course> courses;
    map<int, prof> profs;
    map<int, promo> promos;
    
    get_courses(courses);
    get_profs(profs, courses);
    get_promos(promos, courses);
    rout2(profs,promos, courses);
    
    return;
                
}

int main(int argc, char* argv[]) {
   test3(); 
   
   return 0;
}