#include <iostream>
#include "promo.h"
#include "parseFile.h"

using namespace std;

//Initialisation
int Promo::_static_id=0;

Promo::Promo() :_name("unkonwn"), _nb_students(-1) {
    _id=_static_id++;
}

Promo::Promo(int id_promo, string name, int nb_students, list<int> courses):
_id_promo(id_promo), _name(name), _nb_students(nb_students), _id_courses(courses){
    _id=_static_id++;
}


//Getter
int Promo::get_course(int id) {
    return at(_id_courses,id);
}

int Promo::get_id() {
    return _id;
}

int Promo::get_id_promo() {
    return _id_promo;
}

string Promo::get_name() {
    return _name;
}

Week& Promo::get_week(int num_week) {
    return _weeks[num_week];
}

int Promo::is_available(int num_week, int index) {
    return _weeks[num_week].checkAvailability(index);
}



//Setter
void Promo::add_course(int id_c) {
    _id_courses.push_back(id_c);
}

void Promo::add_week(Week w) {
    _weeks[w.get_id()] = w;
}


//Affichage
void Promo::list_promos() {
    
    cout << "Classe numero " << get_id() << endl;
    cout << "Promotion numero " << get_id_promo() << endl;
    cout << "\t Nom : " << get_name() << endl;
    cout << "\t Cours : " << endl;
    for(list<int> ::iterator it=_id_courses.begin(); it!=_id_courses.end() ; it++) { 
        cout << "\t\t" << *it << endl;
    }
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