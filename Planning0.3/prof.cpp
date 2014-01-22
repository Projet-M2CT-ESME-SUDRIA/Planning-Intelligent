#include <iostream>
#include <cassert>
#include "prof.h"
#include "promo.h"

using namespace std;


//Initialisation
int Prof::_static_id=0;

Prof::Prof() :_name("unknown"){
    _id=_static_id++;
}

Prof::Prof(string name, map<int, vector<int> > availability, vector<int> given_courses) : _name(name), _availability(availability), _id_given_courses(given_courses){
    _id=_static_id++;
}

//Getter
std::vector<int> Prof::get_availability(int num_week) {
    return _availability[num_week];
}

string Prof::get_name() {
    return _name;
}

vector<int> Prof::get_given_courses() {
    return _id_given_courses;
}

int Prof::get_id_course(int index) {
    return _id_given_courses[index];
}

int Prof::is_available(int num_week, int index) {
    return _availability[num_week].at(index);
}

int Prof::nb_courses(){
    return _id_given_courses.size();
}

int Prof::get_id(){
    return _id;
}

int Prof::get_nb_availability(int num_week){
    std::vector<int> A=_availability.at(num_week);
    int buf=0;
    for(std::vector<int>::iterator it=A.begin(); it!=A.end(); it++){
        buf+=*it;
    }
    return buf;
}

//Setter
void Prof::add_availability(int nb_weeks, std::vector<int> availability) {
    for (int i = 0; i < nb_weeks; i++) {
        _availability[i] = availability;
    }
}

void Prof::set_availability(int num_week, int index) {
    _availability[num_week].at(index) = 0;
}

void Prof::add_given_course(int id_c){
    _id_given_courses.push_back(id_c);
}


//Random function
int Prof::grant_lecture(Course c, Week &w, int index) {
    vector<int> availability = this->get_availability(w.get_num_week());
    if (w.checkAvailability(index)) {
        
        //assert(availability.at(index));
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
    int i;
    vector<int> courses = get_given_courses();

    cout << "Professeur numero " << _id << endl;
    cout << "\t Nom : " << _name << endl;
    cout << "\t Cours : " << endl;
    for(vector<int>::iterator it=get_given_courses().begin() ; it!=get_given_courses().end() ; it++) { 
        cout << "\t\tid: " << *it << endl;
    }
}