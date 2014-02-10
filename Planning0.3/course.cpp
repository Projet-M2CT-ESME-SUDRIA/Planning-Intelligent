#include <iostream>
#include "course.h"
#include "parseFile.h"

using namespace std;


//Initialisation
int Course::_static_id=0;

Course::Course() : _name("unknown"), _nb_hours(-1){
    _id = _static_id++;
    _id_previous_course=-1;
}

Course::Course(int id_promo, string name, int nb_hours) 
:_id_promo(id_promo), _name(name), _nb_hours(nb_hours){
    _id = _static_id++;
    _lecture_size=0;
    _id_previous_course=-1;
}

void Course::initializeList(int nb_week) {
    
    for(int i=0 ; i<nb_week ; i++) {
        _prog_semester.push_back(0);
    }
}



//Getter
int Course::get_id() {
    return _id;
}

int Course::get_id_promo() {
    return _id_promo;
}

string Course::get_name() {
    return _name;
}

int Course::get_nb_hours() {
    return _nb_hours;
}

//Calcul la durée en semaine en cours d'une matière
int Course::get_nb_weeks(int nb_weeks){
    
    if(_nb_hours/2 < nb_weeks) {
        _lecture_size = 2;
        return _nb_hours/2;
    }
    else if(_nb_hours%4 == 0) {
        _lecture_size = 4;
        return _nb_hours/4;
    }
        
    _lecture_size = 4;
    
    return 1 + _nb_hours/4;
}

int Course::get_lecture_size() {
    return _lecture_size;
}

//Affichage
void Course::list_courses() {
    cout << "Matiere numero " << _id << endl;
    cout << "\t intitule : " << _name << endl;
    cout << "\t nombre d'heures : " << _nb_hours << endl;
}