/* 
 * File:   school.h
 * Author: Corentin
 *
 * Created on 22 janvier 2014, 13:15
 */

#ifndef SCHOOL_H
#define	SCHOOL_H

#include "course.h"
#include "prof.h"
#include "promo.h"

class School {
    
public:
    School();
    
    void parse_profs();
    void parse_courses();
    void parse_promos();
    
    void display();
    
    void rout();
    
private:
    std::map<int, Course> _courses;
    std::map<int, Prof> _profs;
    std::map<int, Promo> _promos;
};

#endif	/* SCHOOL_H */

