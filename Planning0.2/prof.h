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
    std::string get_name();
    std::vector<course> get_given_courses();
    course get_course(int index);
    void list_profs();
    int is_available(int num_week, int index);
    int nb_courses();

};


#endif	/* PROF_H */

