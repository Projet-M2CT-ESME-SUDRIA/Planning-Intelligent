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
    l = get_lecture(index);
    if (l.get_id_course() == -1)
        return true;
    return false;
}

Lecture Week::get_lecture(int index) {
    
    list<Lecture>::iterator it = _lectures.begin();
    advance(it, index);
    return *it;
}

bool Week::has_lecture(int id_course) {
    
    for (list<Lecture>::iterator it=_lectures.begin(); it!=_lectures.end() ; it++) {
        if (id_course == (*it).get_id_course())
            return true;
    }
    
    return false;
}

//Récupère le créneau auquel 
int Week::retrieve_course_index(int id_course) {

    int cmpt=0;
    
    for (list<Lecture>::iterator it=_lectures.begin(); it!=_lectures.end() ; it++) {
        if (id_course == (*it).get_id_course())
            break;
        cmpt++;
    }
    
    return cmpt;
}



//Setter
void Week::add_lecture(int index, Lecture l) {
    list<Lecture>::iterator it = _lectures.begin();
    
    advance(it,index);
    
    *it = l;
    //this->_lectures.insert(_lectures.begin()+index,l);
}


