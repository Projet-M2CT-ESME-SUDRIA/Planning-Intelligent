#include "school.h"
#include "parseFile.h"
#include "routine.h"
#include <iostream>

using namespace std;

//Fonction qui parcourt la liste de classes d'une promo et appelle la fonction de répartition des cours dans la semaine
void School::give_courses_promo(int id_year, list<progSemester> prog) {
    
    list<int> id_promo = getClassPromo(id_year);
    list<progSemester> prog_week;
    int i;
    
    
    //Pour toutes les semaines du semestre
    for (i=0; i<_nb_week ; i++) {
        prog_week = getProgWeek(prog, i);
    }
}

//Récupération des classes qui appartiennent à la même promo
list<int> School::getClassPromo(int id_year) {
    list<int> id_promo;
    int nb_promo = _promos.size(); 
    int i, id;
    for (i=0 ; i<nb_promo ; i++) {
        id = _promos[i].get_id_promo();
        if (id == id_year) {
            id_promo.push_back(id);
        }
    }
    return id_promo;
}

//Récupération du programme pour une semaine donnée
list<progSemester> School::getProgWeek(list<progSemester> prog, int num_week) {
    
    list<progSemester> prog_week;
    for(list<progSemester>::iterator it=prog.begin() ; it!=prog.end() ; it++) {
        if((*it)._start_week <= num_week && (*it)._start_week+(*it)._nb_weeks > num_week) {
            prog_week.push_back(*it);
        }
    }
    return prog_week;
}