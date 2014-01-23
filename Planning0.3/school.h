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
    void parse_courses();
    void parse_promos();
    
    //Affichage
    void display();
    
    //Méthodes relatives au prétraitement
    int nb_class_promo(int id_promo);
    int nb_availabilities_course(int id_course);
    
    //Prétraitements
    int nb_prof_ok();
    int nb_lectures_ok();
    
    //Routine
    void rout();
    
private:
    std::map<int, Course> _courses;
    std::map<int, Prof> _profs;
    std::map<int, Promo> _promos;
    int _nb_week;
};

#endif	/* SCHOOL_H */

