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
    fill_list_promo();
    
    
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
        
        _profs.insert(pair<int, Prof> (p.get_id(), p));
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
    c.initializeList(_nb_week);
    int i = c.get_id();
    _courses.insert(pair<int, Course> (c.get_id(), c));
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

void School::fill_list_promo(){
    
    for(map<int, Course>::iterator it = _courses.begin() ; it != _courses.end() ; it++) {
        if(!existing_value(_list_promos, (*it).second.get_id_promo()))
            _list_promos.push_back((*it).second.get_id_promo());
    }
    
    _list_promos.sort();
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

//Vérifie que le nombre d'heures TOTAL d'une promo ne dépasse pas le nombre d'heure qu'elle peut recevoir
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


void School::divideCourses(){
    
    list<int> id_courses;
    
    for(list<int>::iterator it_list = _list_promos.begin() ; it_list!=_list_promos.end() ; it_list++){
        for(map<int, Promo>::iterator it_promo = _promos.begin() ; it_promo != _promos.end() ; it_promo++){
            if(*it_list == (*it_promo).second.get_id_promo()) {
                id_courses = (*it_promo).second.get_id_courses();
                break;
            }
        }
        
        id_courses = merge_sort(id_courses);
        
        //Répartir les cours sur le semestre
        list<progSemester> prog = splitCourses(id_courses);
        
        //Vérification créneau
        give_courses_promo(*it_list, prog);
    }
}

void School::give_courses_promo(int id_year, list<progSemester> prog) {
    int nb_promo = _promos.size(); 
    int i;
    
    for (i=0 ; i<nb_promo ; i++) {
        if (_promos[i].get_id_promo() == id_year) {
            parse_courses_promo(_promos[i], prog);
        }
    }
}

void School::parse_courses_promo(Promo &p, list<progSemester> prog) {

     
}


//Fonction pour répartir les cours sur les semaines d'un semestre
list<progSemester> School::splitCourses(list<int> id_courses) {
    
    list<progSemester> prog;
    bool put=false;
    int cmpt = 0;
    
    prog.resize(id_courses.size());
    initProg(prog);
    
    //On parcourt la liste contenant les id des cours du programme
    for(list<int>::iterator it = id_courses.begin() ; it != id_courses.end() ; it++) {
        put = false;
       
        //On parcourt la liste des cours déjà placé pour éventuellement placer le cours à la suite d'un autre
        for (list<progSemester>::iterator it_prog = prog.begin() ; it_prog != prog.end() ; it_prog++) {

            //Si sur le prog on le cours est déja placé
            if((*it_prog)._id_course != -1) {
               
                checkNextCourse((*it_prog), prog, cmpt, (*it));

                //Si on a ajouté le nouveau cours
                if(at(prog, cmpt)._id_course != -1) {
                    //cout <<"test : " << _courses[*it].get_id() << endl;
                    put = true;
                    cmpt ++;
                    break;
                }
            }
            
        } 
        if(!put) {
            //cout << _courses[*it].get_id() << endl;
            editList(prog, cmpt, _courses[*it].get_id(), _courses[*it].get_nb_weeks(_nb_week), 0);
            cmpt ++;
        }
    }
    
    for(list<progSemester>::iterator it = prog.begin() ; it != prog.end() ; it++) {
        cout << (*it)._id_course << "|" << (*it)._nb_weeks << "|" << (*it)._start_week << endl;
    }
    
    return prog;
}

//Fonction récursive qui permet de vérifier si on peut placer un  cours à la suite d'un ou plusieurs autres cours.
void School::checkNextCourse(progSemester &currentCourse, list<progSemester> &prog, int index, int id_newCourse) {
    
    //Si le cours actuel a un successeur, on rappelle la fonction pour traiter le successeur
    if(currentCourse._next != NULL) {
        checkNextCourse(*(currentCourse._next), prog, index, id_newCourse);
    }
    
    //Si le cours actuel n'a pas de successeur, on regarde si on peut placer le nouveau cours derrière lui
    else if(currentCourse._start_week + currentCourse._nb_weeks + _courses[id_newCourse].get_nb_weeks(_nb_week) <= _nb_week) {
        editList(prog, index, _courses[id_newCourse].get_id(), _courses[id_newCourse].get_nb_weeks(_nb_week), currentCourse._start_week + currentCourse._nb_weeks);
        
        list<progSemester>::iterator it = prog.begin();
        advance(it, index);
        if(&currentCourse != &(*it))
           currentCourse._next = &(*it);
    }
    
}

void School::setProg(progSemester &buf, Course c, int start_week){
    
    buf._id_course = c.get_id();
    buf._nb_weeks = c.get_nb_weeks(_nb_week);
    buf._start_week = start_week;
    buf._next = NULL;
}


list<int> School::merge_sort(list<int> &l) {
    
    list<int> left;
    list<int> right;
    list<int> result;
    int size_list = l.size();
    int i;
    
    if (size_list <= 1) {
        return l;
    }
    
    int middle = (size_list / 2);
    
    for (i = 0; i < middle; i++) {        
        left.push_back(at(l,i));
    }
    
    for (i = middle; i < size_list; i++) {
        right.push_back(at(l,i));
    }
    
    left = merge_sort(left);
    right = merge_sort(right);
    result = merge(left, right);
    
    return result;
    
}

std::list<int> School::merge(std::list<int>& left, std::list<int>& right) {
    
    list<int> result;
    int left_size = left.size();
    int right_size = right.size();
    int left_index = 0, right_index = 0;
    
    while (left_index < left_size && right_index < right_size) {
        if (_courses[at(left,left_index)].get_nb_weeks(_nb_week) > _courses[at(right, right_index)].get_nb_weeks(_nb_week)) {
            result.push_back(at(left,left_index));
            left_index++;
        }
        else if (_courses[at(left,left_index)].get_nb_weeks(_nb_week) == _courses[at(right, right_index)].get_nb_weeks(_nb_week)) {
            if(_courses[at(left,left_index)].get_lecture_size() > _courses[at(right,right_index)].get_lecture_size()) {
                result.push_back(at(left,left_index));
                left_index++;
            }
            else {
                result.push_back(at(right, right_index));
                right_index++;
            }
        }
        else {
            result.push_back(at(right, right_index));
            right_index++;
        }
    }
    
    if (left_index == left_size) {
        while (right_index < right_size) {
            result.push_back(at(right, right_index));
            right_index++;
	}
    } 
    
    else {
	while (left_index < left_size) {
	    result.push_back(at(left,left_index));
	    left_index++;
	}
    }
    
    return result;
}

void initProg(list<progSemester> &l) {
    int size = l.size();
    int index;
    
    for (index = 0; index < size; index++) {
        editList(l, index, -1, 0, 0);
    }
}
