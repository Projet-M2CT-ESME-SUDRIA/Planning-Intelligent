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
    for(list<string>::iterator it=line.begin() ; it!=line.end() ; it++){
        new_prof(*it);
    }
    
}

//Création d'un prof à partir d'une ligne du fichier de données
void School::new_prof(string line) {
    
    list<string> words = parse_line(line, '|');
    
    string availabilities = at(words,1);
    
    if(!check_availability(availabilities)) {
        cout << "probleme de disponibilites prof" << endl;
        exit(EXIT_FAILURE);
    }
    
    map<int,list<int> > availability;
    list<int> given_courses;
    
    //Création de l'ensemble des disponibilités du profs
    list<int> temp = fill_v_availability(availabilities);
    
    if (!temp.empty())
    {        
        for (int i=0 ; i<_nb_week ; i++) {
            availability[i] = temp;
        }

        string line_courses = at(words,2);
        list<string> name = parse_line(line_courses, ',');
        given_courses = retrieve_courses(name);
    
        Prof p(at(words,0),availability, given_courses);
        
        _profs.insert(pair<int, Prof>(p.get_id(), p));
        
    }
    
    else {
        cout << "probleme disponibilites" << endl;
        exit(EXIT_FAILURE);
    }
}

void School::parse_courses() {
    
    list<string> line;
    
    line = read_file("courses.txt");
    for(list<string>::iterator it=line.begin() ; it!=line.end() ; it++) {
        new_course(*it, _nb_week);
    }
}

//Création d'une matière à partir d'une ligne du fichier de données
void School::new_course(string line, int nb_week) {
    
    list<string> words;
    words = parse_line(line, '|');
    
    int nb_hours = string_to_int(at(words,2));
    
    if(nb_hours > 4*nb_week) {
        cout << "c'est la merde putain" << endl;
        exit(EXIT_FAILURE);
    }
    
    Course c(string_to_int(at(words,0)), at(words,1), nb_hours);
    _courses.insert(pair<int, Course>(c.get_id(), c));
}


void School::parse_promos() {
    
    list<string> line;
    
    line = read_file("promos.txt");
    
    for(list<string>::iterator it=line.begin(); it!=line.end() ; it++) {
        new_promo(*it);
    }   
}

//Création d'une matière à partir d'une ligne du fichier de données
void School::new_promo(string line) {
    
    list<string> words;
    list<int> course_followed;
    int id_promo = -1;
    int i;
    
    words = parse_line(line, '|');
    
    //Méthode pour pouvoir récupérer les cours suivis
    string s = at(words,3);
    list<string> name = parse_line(s, ',');
    course_followed = retrieve_courses(name);
    
    Promo p(string_to_int(at(words,0)), at(words,1), string_to_int(at(words,2)), course_followed);
    
    //Méthode pour créer les semaines de la promo
    id_promo = p.get_id();
    for(i = 0 ; i < _nb_week ; i++) {
        Week w(id_promo, i);
        p.add_week(w);
    }
    
    _promos.insert(pair<int, Promo>(p.get_id(), p));
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
        
        int c = nb_availabilities_course(id_course);
        
        if(nb_promo > c) {
            cout << "Probleme avec la matiere numero " << id_course << endl;
            exit(EXIT_FAILURE);
        }
    }
    
    cout << "Nombre de profs OK" << endl;
    
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


//Construit la map de matières d'un prof
list<int> School::retrieve_courses (list<string> name) {
    
    list<int> given_courses;
    
    for(list<string>::iterator it_name=name.begin(); it_name!=name.end() ; it_name++) {
        for(map<int, Course>::iterator it_course=_courses.begin(); it_course!=_courses.end() ; it_course++) {
            if((*it_name).compare((*it_course).second.get_name()) == 0) {
                given_courses.push_back((*it_course).second.get_id());
                break;
            }
        }
    }
    
    if(given_courses.size() != name.size())
        exit(EXIT_FAILURE);
    
    return given_courses;
}
