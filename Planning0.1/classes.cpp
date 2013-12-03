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

int lecture::get_id_course() {
    return _id_course;
}


/*********************/
/*      Week         */
/*********************/

int week::_id=0;

week::week() : _id_promo(0), _num_week(0) {
    _id++;
    _lectures.resize(22);
}

week::week(int id_promo, int num_week) :
_id_promo(id_promo), _num_week(num_week){
    _id++;
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


/***********************/
/*      Course         */
/***********************/

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


/**********************/
/*      Prof         */
/*********************/

int prof::_id=0;

prof::prof() :_name("unknown"){
    _id++;
}

prof::prof(string name) : _name(name){
    _id++;
}

void prof::add_availability(int nb_weeks, std::vector<int> availability) {
    for (int i = 0; i < nb_weeks; i++) {
        _availabiliy[i+1] = availability;
    }
}

std::vector<int> prof::get_availability(int num_week) {
    return _availabiliy[num_week];
}

void prof::set_availability(int num_week, int index) {
    vector <int> availability = _availabiliy[num_week];
    availability.at(index) = 0;
}


void prof::add_given_course(course c){
    _given_courses[c.get_id()] = c;
}

void prof::grant_lecture(course c, week& w, int index) {
    vector<int> availability = this->get_availability(w.get_num_week());
    if (w.checkAvailability(index)) {
        
        assert(availability.at(index));
        this->set_availability(w.get_num_week(), index);

        lecture l(c.get_id(), this->_id, w.get_id());
        w.add_lecture(index,l);
        cout << "Cours ajoute au prof et a la classe" << endl;
    }
    else
        cout << "La classe a deja un cours" << endl;
}

string prof::get_name() {
    return _name;
}


/**********************/
/*      Promo         */
/**********************/

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
