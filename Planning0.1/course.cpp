#include <iostream>
#include "course.h"

using namespace std;

int course::_id=0;

course::course() : _name("unknown"), _nb_lectures(-1){
    _id++;
}

course::course(int id_promo, string name, int nb_lectures) 
:_id_promo(id_promo), _name(name), _nb_lectures(nb_lectures){
    _id++;
}

int course::get_id() {
    return _id;
}

string course::get_name() {
    return _name;
}