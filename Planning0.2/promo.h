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
    std::vector<course> _courses;
    std::map<int, week> _weeks;
   
public:
    
    static int _static_id;
    promo();
    promo(int id_promo, std::string name, int nb_students, std::vector<course> courses);
    void add_course(course c);
    void add_week(week w);
    course get_course(int id);
    int get_id();
    int get_id_promo();
    std::string get_name();
    void list_promos();
    week& get_week(int num_week);
    int is_available(int num_week, int index);
    
};



#endif	/* PROMO_H */

