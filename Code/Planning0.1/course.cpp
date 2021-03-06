#include <iostream>
#include "course.h"

using namespace std;

int course::_static_id=0;

course::course() : _name("unknown"), _nb_lectures(-1){
    _id = _static_id++;
}

course::course(int id_promo, string name, int nb_lectures) 
:_id_promo(id_promo), _name(name), _nb_lectures(nb_lectures){
    _id = _static_id++;
}

int course::get_id() {
    return _id;
}

string course::get_name() {
    return _name;
}

void course::list_courses() {
    cout << "Matiere numero " << _id << endl;
    cout << "\t intitule : " << _name << endl;
    cout << "\t nombre d'heures : " << _nb_lectures << endl;
}