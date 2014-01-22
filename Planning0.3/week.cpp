#include <iostream>
#include "week.h"

using namespace std;


//Initialisation
int Week::_static_id=0;

Week::Week() : _id_promo(0), _num_week(0) {
    _id=_static_id++;
    _lectures.resize(22);
}

Week::Week(int id_promo, int num_week) :
_id_promo(id_promo), _num_week(num_week){
    _id=_static_id++;
    _lectures.resize(22);
}

//Getter
int Week::get_id() {
    return _id;
}

int Week::get_num_week() {
    return _num_week;
}

bool Week::checkAvailability(int index) {
    Lecture l;
    l = this->_lectures.at(index);
    if (l.get_id_course() == -1)
        return true;
    return false;
}

Lecture Week::get_lecture(int index) {
    return _lectures.at(index);
}

bool Week::has_lecture(int id_course) {
    
    int i=0;
    
    for (vector<lecture>::iterator it=_lectures.begin(); it!=_lectures.end() ; it++) {
        if (id_course == (*it).get_id_course())
            return true;
    }
    
    return false;
}


//Setter
void Week::add_lecture(int index, Lecture l) {
    this->_lectures.insert(_lectures.begin()+index,l);
}


