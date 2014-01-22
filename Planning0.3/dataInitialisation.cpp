#include <iostream>
#include "dataInitialisation.h"
#include "parseFile.h"

using namespace std;

void add_prof() {
    
    string name, availability, given_courses, nb_weeks;
    
    cout << "Nom du prof" << endl;
    cin >> name;
    cout << "Disponibilites" << endl;
    cin >> availability;
    cout << "Cours donnes par le prof" << endl;
    cin >> given_courses;
    cout << "Nombre de semaine de cours" << endl;
    cin >> nb_weeks;
    
    add_prof_to_db(name, availability, given_courses, nb_weeks);
}

void add_course() {
    
    string name, nb_hours, id_promo;
    
    cout << "ID de la promo correspondante" << endl;
    cin >> id_promo;
    cout << "Nom de la matiere" << endl;
    cin >> name;
    cout << "Nombre d'heures" << endl;
    cin >> nb_hours;
    
    add_course_to_db(id_promo, name, nb_hours);
}

void add_promo() {
    string id_promo, name, nb_student, courses, nb_weeks;
    
    cout << "ID de la promotion" << endl;
    cin >> id_promo;
    cout << "Nom de la classe" << endl;
    cin >> name;
    cout << "Nombre d'élève dans la classe" << endl;
    cin >> nb_student;
    cout << "Liste des cours suivis par la classe" << endl;
    cin >> courses;
    cout << "Nombre de semaine de cours" << endl;
    cin >> nb_weeks;
    
    add_promo_to_db(id_promo, name, nb_student, courses, nb_weeks);
}

void get_profs(map<int, prof> &profs, map<int, course> courses) {
    
    parse_profs(profs, courses);
    
    for(int i=0 ; i<profs.size() ; i++) {
        profs[i].list_profs();
    }
}

void get_courses(map<int, course> &courses) {
    
    parse_courses(courses);
    int size_course = courses.size();
    for(int i=0 ; i<size_course ; i++) {
        courses[i].list_courses();
    }
}

void get_promos(map<int, promo> &promos, map<int, course> &courses) {
    parse_promo(promos, courses);
    
    for(int i=0 ; i<promos.size() ; i++) {
        promos[i].list_promos();
    }  
}
