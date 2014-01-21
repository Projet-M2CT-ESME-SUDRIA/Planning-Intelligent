/* 
 * File:   prof.h
 * Author: Corentin
 *
 * Created on 4 décembre 2013, 15:55
 */

#ifndef PROF_H
#define	PROF_H


#include <vector>
#include <map>
#include <algorithm>
#include "week.h"
#include "course.h"
#include "promo.h"

class prof{
    
    int _id;
    std::string _name;
    std::map<int, std::vector<int> > _availability;
    std::vector<course> _given_courses;
  
public:
    
    static int _static_id;
    prof();
    prof(std::string name, std::map<int, std::vector<int> > availability, std::vector<course> given_courses);
    void add_availability(int nb_weeks, std::vector <int> availability);
    std::vector<int> get_availability(int num_week);
    void set_availability(int num_week, int index);
    void add_given_course(course c);
    //index = creneaux
    int grant_lecture(course c, week &w, int index);
    int grant(promo &p, int course_id, int first_week, int hour);
    std::string get_name();
    std::vector<course> get_given_courses();
    course get_course(int index);
    void list_profs();
    int is_available(int num_week, int index);
    int nb_courses();
    int get_id();
    
    int get_nb_availability(int num_week){
        std::vector<int> A=_availability.at(num_week);
        int buf=0;
        for(std::vector<int>::iterator it=A.begin(); it!=A.end(); it++){
            buf+=*it;
        }
        return buf;
        
    }
    
    
    

};


#endif	/* PROF_H */

