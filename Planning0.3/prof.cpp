#include <iostream>
#include <cassert>
#include "prof.h"
#include "promo.h"

using namespace std;


//Initialisation
int prof::_static_id=0;

prof::prof() :_name("unknown"){
    _id=_static_id++;
}

prof::prof(string name, map<int, vector<int> > availability, vector<int> given_courses) : _name(name), _availability(availability), _id_given_courses(given_courses){
    _id=_static_id++;
}

//Getter
std::vector<int> prof::get_availability(int num_week) {
    return _availability[num_week];
}

string prof::get_name() {
    return _name;
}

vector<int> prof::get_given_courses() {
    return _id_given_courses;
}

int prof::get_id_course(int index) {
    return _id_given_courses[index];
}

int prof::is_available(int num_week, int index) {
    return _availability[num_week].at(index);
}

int prof::nb_courses(){
    return _id_given_courses.size();
}

int prof::get_id(){
    return _id;
}

int prof::get_nb_availability(int num_week){
    std::vector<int> A=_availability.at(num_week);
    int buf=0;
    for(std::vector<int>::iterator it=A.begin(); it!=A.end(); it++){
        buf+=*it;
    }
    return buf;
}

//Setter
void prof::add_availability(int nb_weeks, std::vector<int> availability) {
    for (int i = 0; i < nb_weeks; i++) {
        _availability[i] = availability;
    }
}

void prof::set_availability(int num_week, int index) {
    _availability[num_week].at(index) = 0;
}

void prof::add_given_course(int id_c){
    _id_given_courses.push_back(id_c);
}


//Random function
int prof::grant_lecture(course c, week &w, int index) {
    vector<int> availability = this->get_availability(w.get_num_week());
    if (w.checkAvailability(index)) {
        
        //assert(availability.at(index));
        this->set_availability(w.get_num_week(), index);

        lecture l(c.get_id(), this->_id, w.get_id());
        w.add_lecture(index,l);
        return 1;
    }
    else {
        cout << "La classe a deja un cours" << endl;
        return 0;
    }
}

//Affichage
void prof::list_profs() {
    int i;
    vector<int> courses = get_given_courses();
    cout << "Professeur numero " << _id << endl;
    cout << "\t Nom : " << _name << endl;
    cout << "\t Cours : " << endl;
    for(i = 0 ; i < courses.size() ; i++) { 
        cout << "\t\tid: " << courses.at(i) << endl;
    }
}