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

list<int> Promo::get_id_courses() {
    return _id_courses;
}

//Setter
void Promo::add_course(int id_c) {
    _id_courses.push_back(id_c);
}

void Promo::add_week(Week w) {
    _weeks[w.get_id()] = w;
}

int Promo::get_id_prof(int id_course, int num_week) {
    return _weeks[num_week].get_lecture(id_course).get_id_prof();
}

int Promo::get_course_index(int id_course, int num_week) {

    return _weeks[num_week].retrieve_course_index(id_course);
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



//Méthode pour savoir si la promo à le cours que l'on lui envoie.
int Promo::has_course(int id_course) {
    
    int i=0;
    
    for (i=0 ; i<_id_courses.size() ; i++) {
        if(id_course == at(_id_courses,i))
            return 1;
    }
    
    return 0;
}

//Méthode pour savoir si le cours a déja été placé sur la semaine envoyé.
int Promo::has_course_received(int id_course, int week_index) {
    
    if(_weeks[week_index].has_lecture(id_course))
        return 1;
    
    return 0;
}