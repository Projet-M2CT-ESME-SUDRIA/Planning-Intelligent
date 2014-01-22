/* 
 * File:   promo.h
 * Author: Corentin
 *
 * Created on 4 décembre 2013, 15:59
 */

#ifndef PROMO_H
#define	PROMO_H

#include <vector>
#include <map>
#include <algorithm>
#include "course.h"
#include "week.h"


class promo{
    
    int _id;
    int _id_promo;
    int _nb_students;
    std::string _name;
    std::vector<int> _id_courses;
    std::map<int, week> _weeks;
   
public:
    
    //Initialisation
    static int _static_id;
    promo();
    promo(int id_promo, std::string name, int nb_students, std::vector<int> courses);
    
    //Getter
    int get_course(int id);
    int get_id();
    int get_id_promo();
    std::string get_name();
    int is_available(int num_week, int index);
    
    //Setter
    void add_course(int id_c);
    void add_week(week w);
    
    //Affichage
    void list_promos();
    
    //Random function
    week& get_week(int num_week);
    
    //int has_course(course c);
    //int has_course_received(course c, int week_index);
    
};



#endif	/* PROMO_H */

