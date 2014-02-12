#include "school.h"
#include "parseFile.h"
#include "routine.h"
#include <iostream>

using namespace std;

//Fonction qui parcourt la liste de classes d'une promo et appelle la fonction de répartition des cours dans la semaine
void School::give_courses_promo(int id_year, list<progSemester> prog) {
    int nb_promo = _promos.size(); 
    int i;
    
    for (i=0 ; i<nb_promo ; i++) {
        if (_promos[i].get_id_promo() == id_year) {
            parse_courses_promo(_promos[i], prog);
        }
    }
}

void School::parse_courses_promo(Promo &p, list<progSemester> prog) {

     
}
