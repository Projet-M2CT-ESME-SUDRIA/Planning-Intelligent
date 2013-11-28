/* 
 * File:   main.cpp
 * Author: elysiunk
 *
 * Created on 28 novembre 2013, 17:04
 */

#include <cstdlib>
#include <iostream>
#include "classes.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    course test;
    
    course alg(1, "algebre", 10);
    course geo(2, "geoAna", 12);
    promo p1(1,"B1A", 40);
    
    p1.add_course(alg);
    p1.add_course(geo);
    
    test = p1.get_course(2);
    cout << test.get_name() << endl;
    
    return 0;
}

