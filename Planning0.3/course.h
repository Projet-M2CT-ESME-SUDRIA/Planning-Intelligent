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

class Course {
    
    int _id;
    int _id_promo;
    std::string _name;
    int _nb_hours;
    std::vector<int> _id_profs;
    
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
    int get_id_prof(int index);    
    int get_profs();
    
    //Setter
    void add_prof(int id_prof);
    
    //Affichage
    void list_courses();

};


#endif	/* COURSE_H */

