#include <iostream>
#include <cassert>
#include "prof.h"

using namespace std;

int prof::_static_id=0;

prof::prof() :_name("unknown"){
    _id=_static_id++;
}

prof::prof(string name, map<int, vector<int> > availability, vector<course> given_courses) : _name(name), _availability(availability), _given_courses(given_courses){
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
    _given_courses.push_back(c);
}

int prof::grant_lecture(course c, week &w, int index) {
    vector<int> availability = this->get_availability(w.get_num_week());
    if (w.checkAvailability(index)) {
        
        //assert(availability.at(index));
        this->set_availability(w.get_num_week(), index);

        lecture l(c.get_id(), this->_id, w.get_id());
        w.add_lecture(index,l);
        cout << "Cours ajoute au prof et a la classe" << endl;
        return 1;
    }
    else {
        cout << "La classe a deja un cours" << endl;
        return 0;
    }
}

string prof::get_name() {
    return _name;
}

vector<course> prof::get_given_courses() {
    return _given_courses;
}

course prof::get_course(int index) {
    return _given_courses[index];
}

void prof::list_profs() {
    int i;
    vector<course> courses = get_given_courses();
    cout << "Professeur numero " << _id << endl;
    cout << "\t Nom : " << _name << endl;
    cout << "\t Cours : " << endl;
    for(i = 0 ; i < courses.size() ; i++) { 
        cout << "\t\t" << courses.at(i).get_name() << endl;
    }
}

int prof::is_available(int num_week, int index) {
    return _availability[num_week].at(index);
}

int prof::nb_courses(){
    return _given_courses.size();
}