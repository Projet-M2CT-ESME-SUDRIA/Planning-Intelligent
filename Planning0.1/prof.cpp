#include <iostream>
#include <cassert>
#include "prof.h"

using namespace std;

int prof::_id=0;

prof::prof() :_name("unknown"){
    _id++;
}

prof::prof(string name, map<int, vector<int> > availability, map<int, course> given_courses) : _name(name), _availability(availability), _given_courses(given_courses){
    _id++;
}

void prof::add_availability(int nb_weeks, std::vector<int> availability) {
    for (int i = 0; i < nb_weeks; i++) {
        _availability[i+1] = availability;
    }
}

std::vector<int> prof::get_availability(int num_week) {
    return _availability[num_week];
}

void prof::set_availability(int num_week, int index) {
    vector <int> availability = _availability[num_week];
    availability.at(index) = 0;
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
