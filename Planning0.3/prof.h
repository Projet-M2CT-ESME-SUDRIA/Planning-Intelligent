/* 
 * File:   prof.h
 * Author: Corentin
 *
 * Created on 4 décembre 2013, 15:55
 */

#ifndef PROF_H
#define	PROF_H


#include <list>
#include <map>
#include <algorithm>
#include "week.h"
#include "course.h"
#include "promo.h"

class Prof{
    
    int _id;
    std::string _name;
    std::map<int, std::list<int> > _availability;
    std::list<int> _id_given_courses;
  
public:
    
    //Initialisation
    static int _static_id;
    Prof();
    Prof(std::string name, std::map<int, std::list<int> > availability, std::list<int> given_courses);
    
    //Getter
    std::list<int> get_availability(int num_week);
    std::string get_name();
    std::list<int> get_given_courses();
    int get_id_course(int index);
    int is_available(int num_week, int index);
    int nb_courses();
    int get_id();
    int get_nb_availability(int num_week);
    int has_course(int id_course);
    
    //Setter
    void add_availability(int nb_weeks, std::list <int> availability);
    void set_availability(int num_week, int index);
    void add_given_course(int id_c);
    
    //Random functions
    int grant_lecture(Course c, Week &w, int index);
    
    //Affichage
    void list_profs();
    
    
};


#endif	/* PROF_H */
