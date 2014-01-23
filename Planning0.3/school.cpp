/* 
 * File:   school.cpp
 * Author: Corentin
 *
 * Created on 22 janvier 2014, 13:16
 */

#include "school.h"
#include "parseFile.h"
#include "routine.h"
#include <iostream>

using namespace std;


School::School(int nb_week){
    
    _nb_week=nb_week;
    
    parse_courses();
    parse_profs();
    parse_promos();
}

void School::parse_profs() {
    
    list<string> line;
    
    line = read_file("profs.txt");
    for(list<string>::iterator it=line.begin() ; it!=line.end() ; it++)
    {
        new_prof(*it, _profs, _courses);
    }
    
}

void School::parse_courses() {
    
    list<string> line;
    
    line = read_file("courses.txt");
    for(list<string>::iterator it=line.begin() ; it!=line.end() ; it++) {
        new_course(*it, _courses, _nb_week);
    }
    
}

void School::parse_promos() {
    
    list<string> line;
    
    line = read_file("promos.txt");
    
    for(list<string>::iterator it=line.begin(); it!=line.end() ; it++) {
        //promo.push_back(new_promo(line[i], courses));
        new_promo(*it, _promos, _courses);
    }
    
}

void School::display(){
    
    for(map<int, Prof>::iterator it=_profs.begin() ; it!=_profs.end() ; it++) {
        (*it).second.list_profs();
    }
    
    for(map<int, Course>::iterator it=_courses.begin() ; it!=_courses.end() ; it++) {
        (*it).second.list_courses();
    }
    
    for(map<int, Promo>::iterator it=_promos.begin() ; it!=_promos.end() ; it++) {
        (*it).second.list_promos();
    }
}

//Retourne le nombre de classe dans une promo à partir de son id
int School::nb_class_promo(int id_promo){
    
    int nb=0;
    
    for (map<int, Promo>::iterator it =_promos.begin() ; it != _promos.end() ; it++){
        if((*it).second.get_id_promo() == id_promo)
            nb++;
    }
    
    return nb;
}

//Retourne le nombre de dispo des profs pour un cours donné
int School::nb_availabilities_course(int id_course){
    
    int nb=0;
    
    for(map<int, Prof>::iterator it = _profs.begin() ; it != _profs.end() ; it++) {
        if((*it).second.has_course(id_course))
            nb+= (*it).second.get_nb_availability(0);
    }
    
    return nb;
}

//Parcourt les matières et vérifie que chaque cours a assez de dispo de prof
int School::nb_prof_ok(){
    
    int id_course, id_promo;
    int nb_promo;
    
    for(map<int, Course>::iterator it = _courses.begin() ; it != _courses.end() ; it++){
        id_course = (*it).second.get_id();
        id_promo = (*it).second.get_id_promo();
        nb_promo = nb_class_promo(id_promo);
        
        if(nb_promo > nb_availabilities_course(id_course)) {
            cout << "Probleme avec la matiere numero " << id_course << endl;
            exit(EXIT_FAILURE);
        }
    }
    
    cout << "Chaque cours a bien assez de prof" << endl;
    return 1;
}

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
void School::rout(){
    rout2(_profs, _promos, _courses);
}