#include <iostream>
#include "promo.h"

using namespace std;


int promo::_static_id=0;

promo::promo() :_name("unkonwn"), _nb_students(-1) {
    _id=_static_id++;
}

promo::promo(int id_promo, string name, int nb_students, vector<int> courses):
_id_promo(id_promo), _name(name), _nb_students(nb_students), _id_courses(courses){
    _id=_static_id++;
}

void promo::add_course(int id_c) {
    _id_courses.push_back(id_c);
}

void promo::add_week(week w) {
    _weeks[w.get_id()] = w;
}

int promo::get_course(int id) {
    return _id_courses[id];
}

int promo::get_id() {
    return _id;
}

int promo::get_id_promo() {
    return _id_promo;
}

string promo::get_name() {
    return _name;
}

week& promo::get_week(int num_week) {
    return _weeks[num_week];
}

void promo::list_promos() {
    int i;
    
    cout << "Classe numero " << get_id() << endl;
    cout << "Promotion numero " << get_id_promo() << endl;
    cout << "\t Nom : " << get_name() << endl;
    cout << "\t Cours : " << endl;
    for(i = 0 ; i < _id_courses.size() ; i++) { 
        cout << "\t\t" << _id_courses.at(i) << endl;
    }
}

int promo::is_available(int num_week, int index) {
    return _weeks[num_week].checkAvailability(index);
}


//int promo::has_course(course c) {
//    
//    int i=0;
//    
//    for (i=0 ; i<_id_courses.size() ; i++) {
//        if(c.get_id() == _id_courses[i].get_id())
//            return 1;
//    }
//    
//    return 0;
//}

//int promo::has_course_received(course c, int week_index) {
//    
//    if(_id_weeks[week_index].has_lecture(c.get_id()))
//        return 1;
//    
//    return 0;
//}