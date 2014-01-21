#include <iostream>
#include "course.h"

using namespace std;

int course::_static_id=0;

course::course() : _name("unknown"), _nb_hours(-1){
    _id = _static_id++;
}

course::course(int id_promo, string name, int nb_hours) 
:_id_promo(id_promo), _name(name), _nb_hours(nb_hours){
    _id = _static_id++;
}

int course::get_id() {
    return _id;
}

int course::get_id_promo() {
    return _id_promo;
}

string course::get_name() {
    return _name;
}

void course::list_courses() {
    cout << "Matiere numero " << _id << endl;
    cout << "\t intitule : " << _name << endl;
    cout << "\t nombre d'heures : " << _nb_hours << endl;
}

int course::get_nb_hours() {
    return _nb_hours;
}

/*void course::add_prof(prof &p){
    _profs.push_back(p);
}*/