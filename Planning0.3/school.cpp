/* 
 * File:   school.cpp
 * Author: Corentin
 *
 * Created on 22 janvier 2014, 13:16
 */

#include "school.h"
#include "parseFile.h"
#include <iostream>

using namespace std;


School::School(){
    
    parse_courses();
    parse_profs();
    parse_promos();
}

void School::parse_profs() {
    
    vector<string> line;
    
    line = read_file("profs.txt");
    
    for(int i=0 ; i<line.size() ; i++)
    {
        new_prof(line[i], _profs, _courses);
    }
    
}

void School::parse_courses() {
    
    vector<string> line;
    
    line = read_file("courses.txt");
    for(int i=0 ; i<line.size() ; i++) {
        new_course(line[i], _courses);
    }
    
}

void School::parse_promos() {
    
    vector<string> line;
    
    line = read_file("promos.txt");
    
    for(int i=0 ; i<line.size() ; i++) {
        //promo.push_back(new_promo(line[i], courses));
        new_promo(line[i], _promos, _courses);
    }
    
}

void School::display(){
    
    int s;
    
    s=_profs.size();
    for(int i=0 ; i<s ; i++) {
        _profs[i].list_profs();
    }
    
    s=_courses.size();
    for(int i=0 ; i<s ; i++) {
        _courses[i].list_courses();
    }
    
    s=_promos.size();
    for(int i=0 ; i<s ; i++) {
        _promos[i].list_promos();
    }
}
