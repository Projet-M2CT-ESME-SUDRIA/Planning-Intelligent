/* 
 * File:   course.h
 * Author: Corentin
 *
 * Created on 4 décembre 2013, 15:57
 */

#ifndef COURSE_H
#define	COURSE_H

#include <vector>
#include <map>
#include <algorithm>
#include <string>

class course {
    
    int _id;
    int _id_promo;
    std::string _name;
    int _nb_hours;
    //std::vector<prof> _profs;
    
public:
    
    static int _static_id;
    course();
    course(int id_promo, std::string name, int nb_hours);
    int get_id();
    int get_id_promo();
    std::string get_name();
    void list_courses();
    int get_nb_hours();
    //void add_prof(prof &p);

};


#endif	/* COURSE_H */

