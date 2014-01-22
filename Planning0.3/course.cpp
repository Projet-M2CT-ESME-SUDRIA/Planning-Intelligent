#include <iostream>
#include "course.h"

using namespace std;


//Initialisation
int Course::_static_id=0;

Course::Course() : _name("unknown"), _nb_hours(-1){
    _id = _static_id++;
}

Course::Course(int id_promo, string name, int nb_hours) 
:_id_promo(id_promo), _name(name), _nb_hours(nb_hours){
    _id = _static_id++;
}


//Getter
int Course::get_id() {
    return _id;
}

int Course::get_id_promo() {
    return _id_promo;
}

string Course::get_name() {
    return _name;
}

int Course::get_nb_hours() {
    return _nb_hours;
}

int Course::get_id_prof(int index) {
    return _id_profs.at(index);
}

int Course::get_profs(){
        return _id_profs.size();
}


//Setter
void Course::add_prof(int id_prof){
    _id_profs.push_back(id_prof);
}

//Affichage
void Course::list_courses() {
    cout << "Matiere numero " << _id << endl;
    cout << "\t intitule : " << _name << endl;
    cout << "\t nombre d'heures : " << _nb_hours << endl;
}