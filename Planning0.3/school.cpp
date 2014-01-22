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
    for(vector<string>::iterator it=line.begin() ; it!=line.end() ; it++)
    {
        new_prof(*it, _profs, _courses);
    }
    
}

void School::parse_courses() {
    
    vector<string> line;
    
    line = read_file("courses.txt");
    for(vector<string>::iterator it=line.begin() ; it!=line.end() ; it++) {
        new_course(*it, _courses);
    }
    
}

void School::parse_promos() {
    
    vector<string> line;
    
    line = read_file("promos.txt");
    
    for(vector<string>::iterator it=line.begin(); it!=line.end() ; it++) {
        //promo.push_back(new_promo(line[i], courses));
        new_promo(*it, _promos, _courses);
    }
    
}

void School::display(){
    
    for(map<int, Prof>::iterator it=_profs.begin() ; it!=_profs.end() ; it++) {
        (*it).second.list_profs();
    }
    
    for(map<int, Course>::iterator it=_courses.begin() ; it!=_courses.end() ; it++) {
        (*it).second.list_courses();
    }
    
    for(map<int, Promo>::iterator it=_promos.begin() ; it!=_promos.end() ; it++) {
        (*it).second.list_promos();
    }
}
