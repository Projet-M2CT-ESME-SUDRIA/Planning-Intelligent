/* 
 * File:   promo.h
 * Author: Corentin
 *
 * Created on 4 décembre 2013, 15:59
 */

#ifndef PROMO_H
#define	PROMO_H

#include <list>
#include <map>
#include <algorithm>
#include "course.h"
#include "week.h"


class Promo{
    
    int _id;
    int _id_promo;
    int _nb_students;
    std::string _name;
    std::list<int> _id_courses;
    std::map<int, Week> _weeks;
   
public:
    
    //Initialisation
    static int _static_id;
    Promo();
    Promo(int id_promo, std::string name, int nb_students, std::list<int> courses);
    
    //Getter
    int get_course(int id);
    int get_id();
    int get_id_promo();
    std::string get_name();
    int is_available(int num_week, int index);
    std::list<int>get_id_courses();
    
    //Setter
    void add_course(int id_c);
    void add_week(Week w);
    
    //Affichage
    void list_promos();
    
    //Random function
    Week& get_week(int num_week);
    
    int has_course(int id_course);
    int has_course_received(int id_course, int week_index);
    
};



#endif	/* PROMO_H */

