#include <iostream>
#include "promo.h"

using namespace std;


int promo::_id=0;

promo::promo() :_name("unkonwn"), _nb_students(-1) {
    _id++;
}

promo::promo(string name, int nb_students):
_name(name), _nb_students(nb_students){
    _id++;
}

void promo::add_course(course c) {
    _courses[c.get_id()] = c;
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
