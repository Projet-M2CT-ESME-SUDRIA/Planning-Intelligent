#include <iostream>

#include "classes.h"

using namespace std;

/************************/
/*      Lecture         */
/************************/
int lecture::_id =0;

lecture::lecture() : _id_course(-1),_id_prof(-1) {
    _id++;
}

lecture::lecture(int id_course, int id_prof, int id_week):
_id_course(id_course),_id_prof(id_prof), _id_week(id_week) {
    _id++;
}


/*********************/
/*      Week         */
/*********************/
week::week() : _id(0), _id_promo(0) {
    _lectures.resize(22);
}

week::week(int id, int id_promo) : _id(id),_id_promo(id_promo){
    _lectures.resize(22);
}

int week::get_id() {
    return _id;
}

void week::add_lecture(int index, lecture l) {
    this->_lectures.insert(_lectures.begin()+index,l);
}



/***********************/
/*      Course         */
/***********************/
course::course() : _id(-1), _name("unknown"), _nb_lectures(-1){}

course::course(int id, string name, int nb_lectures) 
:_id(id), _name(name), _nb_lectures(nb_lectures){}

int course::get_id() {
    return _id;
}

string course::get_name() {
    return _name;
}


/**********************/
/*      Prof         */
/*********************/
prof::prof() :_id(-1), _name("unknown"){
    assert(_availabiliy.size()==22);
}

prof::prof(int id, string name, vector<int> availability) :
_id(id),_name(name), _availabiliy(availability){
    assert(_availabiliy.size()==22);
}

void prof::add_given_course(course c){
    _given_courses[c.get_id()] = c;
}

void prof::grant_lecture(course c, week& w, int index) {
    assert(_availabiliy.at(index));
    this->_availabiliy.at(index)=0;

    lecture l(c.get_id(), this->_id, w.get_id());
    w.add_lecture(index,l);
}



/**********************/
/*      Promo         */
/**********************/
promo::promo() :_id(-1), _name("unkonwn"), _nb_students(-1) {}

promo::promo(int id, string name, int nb_students):
_id(id), _name(name), _nb_students(nb_students){}

void promo::add_course(course c) {
    _courses[c.get_id()] = c;
}

course promo::get_course(int id) {
    return _courses[id];
}