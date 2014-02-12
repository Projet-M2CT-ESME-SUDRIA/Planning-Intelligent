#include "school.h"
#include "parseFile.h"
#include "routine.h"
#include <iostream>

using namespace std;

//Parcourt les matières et vérifie que chaque cours a assez de dispo de prof
int School::nb_prof_ok(){
    
    int id_course, id_promo;
    int nb_promo;
    
    for(map<int, Course>::iterator it = _courses.begin() ; it != _courses.end() ; it++){
        id_course = (*it).second.get_id();
        id_promo = (*it).second.get_id_promo();
        nb_promo = nb_class_promo(id_promo);
        
        int c = nb_availabilities_course(id_course);
        
        if(nb_promo > c) {
            cout << "Probleme avec la matiere numero " << id_course << endl;
            exit(EXIT_FAILURE);
        }
    }
    
    cout << "Nombre de profs OK" << endl;
    
    return 1;
}

//Vérifie que le nombre d'heures TOTAL d'une promo ne dépasse pas le nombre d'heures qu'elle peut recevoir
int School::nb_lectures_ok() {
    
    int nb_hours=0;
    
    for(map<int, Promo>::iterator it = _promos.begin() ; it != _promos.end() ; it++){
        list<int> id_courses = (*it).second.get_id_courses();
        
        for(list<int>::iterator it2 = id_courses.begin() ; it2 != id_courses.end() ; it2++) {
            nb_hours += _courses.at(*it2).get_nb_hours();
        }
        if(nb_hours / 2 > _nb_week * 22) {
            cout << "Trop d'heures pour la promo " << (*it).second.get_id() << endl;
            exit(EXIT_FAILURE);    
        }
    }
    
    cout << "Nombre d'heures de cours OK" << endl;
    
    return 1;
}

//Fonction qui permet de vérifier qu'aucune semaine ne dépasse le nombre maximum de créneaux d'une semaine
bool School::checkProgSemester(list<progSemester> l) {
    
    //On initialise le tableau du nombre de créneaux utilisé par semaine à 0.
    int *nb_course = new int[_nb_week]();
    int start_week;
    int end_week;
    int i;
    
    for(list<progSemester>::iterator it=l.begin() ; it!=l.end() ; it++) {
        start_week = (*it)._start_week;
        end_week = ((*it)._start_week + (*it)._nb_weeks);
        for(i=start_week ; i<end_week ; i++) {
            nb_course[i] += _courses[(*it)._id_course].get_lecture_size();
            if(nb_course[i] > 44) {
                delete [] nb_course;
                return false;
            }
        }
    }
    
    delete [] nb_course;
    return true;
}