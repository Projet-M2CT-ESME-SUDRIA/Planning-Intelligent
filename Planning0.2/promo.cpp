#include <iostream>
#include "promo.h"

using namespace std;


int promo::_static_id=0;

promo::promo() :_name("unkonwn"), _nb_students(-1) {
    _id=_static_id++;
}

promo::promo(string name, int nb_students, vector<course> courses):
_name(name), _nb_students(nb_students), _courses(courses){
    _id=_static_id++;
}

void promo::add_course(course c) {
    _courses.push_back(c);
}

void promo::add_week(week w) {
    _weeks[w.get_id()] = w;
}

course promo::get_course(int id) {
    return _courses[id];
}

int promo::get_id() {
    return _id;
}

string promo::get_name() {
    return _name;
}

week& promo::get_week(int num_week) {
    return _weeks[num_week];
}

void promo::list_promos() {
    int i;
    
    cout << "Classe numero " << get_id() << endl;
    cout << "\t Nom : " << get_name() << endl;
    cout << "\t Cours : " << endl;
    for(i = 0 ; i < _courses.size() ; i++) { 
        cout << "\t\t" << _courses.at(i).get_name() << endl;
    }
}