#include <iostream>
#include <cassert>
#include "prof.h"

using namespace std;

int prof::_static_id=0;

prof::prof() :_name("unknown"){
    _id=_static_id++;
}

prof::prof(string name, map<int, vector<int> > availability, map<int, course> given_courses) : _name(name), _availability(availability), _given_courses(given_courses){
    _id=_static_id++;
}

void prof::add_availability(int nb_weeks, std::vector<int> availability) {
    for (int i = 0; i < nb_weeks; i++) {
        _availability[i] = availability;
    }
}

std::vector<int> prof::get_availability(int num_week) {
    return _availability[num_week];
}

void prof::set_availability(int num_week, int index) {
    _availability[num_week].at(index) = 0;
}

void prof::add_given_course(course c){
    _given_courses[c.get_id()] = c;
}

void prof::grant_lecture(course c, week& w, int index) {
    vector<int> availability = this->get_availability(w.get_num_week());
    if (w.checkAvailability(index)) {
        
        assert(availability.at(index));
        this->set_availability(w.get_num_week(), index);

        lecture l(c.get_id(), this->_id, w.get_id());
        w.add_lecture(index,l);
        cout << "Cours ajoute au prof et a la classe" << endl;
    }
    else
        cout << "La classe a deja un cours" << endl;
}

string prof::get_name() {
    return _name;
}

map<int, course> prof::get_given_courses() {
    return _given_courses;
}

void prof::list_profs() {
    int i;
    map<int,course> courses = get_given_courses();
    cout << "Professeur numero " << _id << endl;
    cout << "\t Nom : " << _name << endl;
    cout << "\t Cours : " << endl;
    for(i = 0 ; i < courses.size() ; i++) { 
        cout << "\t\t" << courses[i].get_name() << endl;
    }
}