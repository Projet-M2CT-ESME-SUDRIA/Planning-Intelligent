#include <iostream>
#include "week.h"

using namespace std;



int week::_static_id=0;

week::week() : _id_promo(0), _num_week(0) {
    _id=_static_id++;
    _lectures.resize(22);
}

week::week(int id_promo, int num_week) :
_id_promo(id_promo), _num_week(num_week){
    _id=_static_id++;
    _lectures.resize(22);
}

int week::get_id() {
    return _id;
}

int week::get_num_week() {
    return _num_week;
}


void week::add_lecture(int index, lecture l) {
    this->_lectures.insert(_lectures.begin()+index,l);
}

bool week::checkAvailability(int index) {
    lecture l;
    l = this->_lectures.at(index);
    if (l.get_id_course() == -1)
        return true;
    return false;
}

lecture week::get_lecture(int index) {
    return _lectures.at(index);
}

bool week::has_lecture(int id_course) {
    
    int i=0;
    
    for (i=0 ; i<_lectures.size() ; i++) {
        if (id_course == _lectures[i].get_id_course())
            return true;
    }
    
    return false;
}
