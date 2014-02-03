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
    School(int nb_week);
    
    //Initialisation de la classe School
    void parse_profs();
    void new_prof(std::string line);
    
    void parse_courses();
    void new_course(std::string line, int nb_week);
    
    void parse_promos();
    void new_promo(std::string line);

    void fill_list_promo();
    
    //Affichage
    void display();
    
    //Méthodes relatives au prétraitement
    int nb_class_promo(int id_promo);
    int nb_availabilities_course(int id_course);
    
    //Prétraitements
    int nb_prof_ok();
    int nb_lectures_ok();
    
    void divideCourses();
    std::list<int> merge_sort(std::list<int> &l);
    std::list<int> merge(std::list<int> &left, std::list<int> &right);
    
    std::list<int> retrieve_courses (std::list<std::string> name);
    
private:
    std::map<int, Course> _courses;
    std::map<int, Prof> _profs;
    std::map<int, Promo> _promos;
    std::list<int> _list_promos;
    int _nb_week;
};

#endif	/* SCHOOL_H */

