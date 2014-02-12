#include <iostream>
#include "prof.h"
#include "promo.h"
#include "parseFile.h"

using namespace std;


//Initialisation
int Prof::_static_id=0;

Prof::Prof() :_name("unknown"){
    _id=_static_id++;
}

Prof::Prof(string name, map<int, list<int> > availability, list<int> given_courses) : _name(name), _availability(availability), _id_given_courses(given_courses){
    _id=_static_id++;
}

//Getter
std::list<int> Prof::get_availability(int num_week) {
    return _availability[num_week];
}

string Prof::get_name() {
    return _name;
}

list<int> Prof::get_given_courses() {
    return _id_given_courses;
}

int Prof::get_id_course(int index) {
    return at(_id_given_courses,index);
}

int Prof::is_available(int num_week, int index) {
    return at(_availability[num_week],index);
}

int Prof::nb_courses(){
    return _id_given_courses.size();
}

int Prof::get_id(){
    return _id;
}

//Retourne le nombre de disponibilités sur une semaine donnée
int Prof::get_nb_availability(int num_week){
    std::list<int> A=_availability.at(num_week);
    int buf=0;
    for(std::list<int>::iterator it=A.begin(); it!=A.end(); it++){
        buf+=*it;
    }
    return buf;
}


//Permet de savoir si un prof donne un cours à partir de l'id du cours
int Prof::has_course(int id_course){
    
    for(std::list<int>::iterator it = _id_given_courses.begin() ; it!=_id_given_courses.end() ; it++) {
        if(*it == id_course)
            return 1;
    }
    
    return 0;
}

//Setter
void Prof::add_availability(int nb_weeks, std::list<int> availability) {
    for (int i = 0; i < nb_weeks; i++) {
        _availability[i] = availability;
    }
}

void Prof::set_availability(int num_week, int index) {
    
    editList(_availability[num_week], 0, index);
    //_availability[num_week].at(index) = 0;
}

void Prof::add_given_course(int id_c){
    _id_given_courses.push_back(id_c);
}


//Random function
int Prof::grant_lecture(Course c, Week &w, int index) {
    
    if (w.checkAvailability(index)) {
        
        this->set_availability(w.get_num_week(), index);

        Lecture l(c.get_id(), this->_id, w.get_id());
        w.add_lecture(index,l);
        return 1;
    }
    else {
        cout << "La classe a deja un cours" << endl;
        return 0;
    }
}

//Affichage
void Prof::list_profs() {

    cout << "Professeur numero " << _id << endl;
    cout << "\t Nom : " << _name << endl;
    cout << "\t Cours : " << endl;
    
    list<int> given_courses = get_given_courses();
    
    for(list<int> ::iterator it=given_courses.begin() ; it!=given_courses.end() ; it++) { 
        cout << "\t\tid: " << *it << endl;
    }
}