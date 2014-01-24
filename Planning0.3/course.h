/* 
 * File:   course.h
 * Author: Corentin
 *
 * Created on 4 décembre 2013, 15:57
 */

#ifndef COURSE_H
#define	COURSE_H

#include <list>
#include <map>
#include <algorithm>
#include <string>

class Course {
    
    int _id;
    int _id_promo;
    std::string _name;
    int _nb_hours;
    int _lecture_size;
    
public:
    
    
    //Initialisation
    static int _static_id;
    Course();
    Course(int id_promo, std::string name, int nb_hours);
    
    //Getter
    int get_id();
    int get_id_promo();
    std::string get_name();
    int get_nb_hours();
    
    //Affichage
    void list_courses();

};


#endif	/* COURSE_H */

