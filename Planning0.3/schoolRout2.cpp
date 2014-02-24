#include "school.h"
#include "parseFile.h"
#include "routine.h"
#include <iostream>

using namespace std;

//Fonction qui parcourt la liste de classes d'une promo et appelle la fonction de répartition des cours dans la semaine
void School::give_courses_promo(int id_year, list<progSemester> prog) {
    
    list<int> id_promo = getClassPromo(id_year);
    list<progSemester> prog_week;
    list<int> prof_week;
    int i;
    
    //Pour toutes les semaines du semestre
    for (i=0; i<_nb_week ; i++) {
        //on récupère le programme de la semaine et les profs qui vont pouvoir donner ces cours.
        prog_week = getProgWeek(prog, i);
        prof_week = getProfWeek(prog_week);
        addCoursePromo(id_promo, prog_week, prof_week, i);
    }
    for(i=0 ; i<14 ; i++) {
        for(int j=0 ; j<22 ; j++) {
            cout << _promos[0].get_week(i).get_lecture(j).get_id_course() << "  ";
        }
        cout << endl;
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
            id_promo.push_back(_promos[i].get_id());
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

//Récupération des id des profs de la semaine en fonction des cours qui doivent être donées
list<int> School::getProfWeek(list<progSemester> prog_week) {
    
    int nb_prof_tot = _profs.size();
    int nb_course_prof = 0;
    int i, j;
    list<int> list_id_prof_week;
    
    //On parcourt toutes les matières de la semaine
    for(list<progSemester>::iterator it=prog_week.begin() ; it!=prog_week.end() ; it++) {
        //On parcourt tous les profs de l'école
        for(i=0 ; i<nb_prof_tot ; i++) {
            nb_course_prof = _profs[i].nb_courses();
            //On parcourt toutes les matières d'un prof
            for (j = 0; j < nb_course_prof; j++) {
                //Si le cours du prof correspond au cours de la semaine on ajoute le prof à la liste des profs de la semaine
                //si il n'y est pas déja dedans
                if(_profs[i].get_id_course(j) == (*it)._id_course && !prof_in_list(list_id_prof_week,_profs[i].get_id())) 
                    list_id_prof_week.push_back(_profs[i].get_id());
            }
        }
    }
    return list_id_prof_week;
}

//Méthode pour savoir si le prof est déja dans la liste des profs de la semaine
bool School::prof_in_list(list<int>list_id_prof_week, int id_prof) {
    for(list<int>::iterator it=list_id_prof_week.begin() ; it!=list_id_prof_week.end() ; it++) {
        if(*it == id_prof)
            return true;
    }
    return false;
}

void School::addCoursePromo(list<int> list_id_promo, list<progSemester> prog_week, list<int> list_id_prof, int num_week) {
    int i;
    int nb_course_tot = list_id_promo.size() * prog_week.size();
    //Id des profs et de la promo que l'on va ajouter car ayant le moins de créneaux en commun
    int profToAdd = -1, promoToAdd = -1;
    
    //On va devoir placer (nombre promo * nombre de cours sur la semaine) cours
    for(i = 0 ; i < nb_course_tot ; i++) {
        profToAdd = -1;
        promoToAdd = -1;
        //Sélection du couple promo prof qui a le moins de créneaux similaire commun sur la semaine i.
        best_connection(prog_week, list_id_prof, list_id_promo, num_week, profToAdd, promoToAdd);
        //On place le cours sur le meilleur créneau, si on en a trouvé un
        if(profToAdd != -1 && promoToAdd != -1) {
            addCourse(prog_week, profToAdd, promoToAdd, num_week);
        }
        
        else {
            cout << "Pas de prof ou promo pour ajouter un cours" << endl;
            exit(EXIT_FAILURE);
        }
    }
}


//Donne le couple prof-classe qui a LE MOINS de disponibilités en commun sur une semaine donnée
void School::best_connection(list<progSemester> prog_week, list<int> id_profs, list<int> id_promos, int num_week, int &prof_index, int &promo_index) {
    
    int buf=23;
    int nbConnection;
    int i;
    
    
    //Pour tous les profs sur la semaine
    for(list<int>::iterator it_prof=id_profs.begin() ; it_prof!=id_profs.end() ; it_prof++) {
        //Pour toutes les promos concernées
        for(list<int>::iterator it_promo=id_promos.begin() ; it_promo!=id_promos.end() ; it_promo++) {
            //On vérifie que : le prof a encore au moins un cours à donner et que ses disponibilités sont les plus faibles
            nbConnection = nb_connections(*it_prof, *it_promo, num_week, prog_week);
            if(nbConnection > 0 && nbConnection < buf) {
                buf = nbConnection;
                prof_index = *it_prof;
                promo_index = *it_promo;
            }
        }
    }
}

//Retourne le nombre de disponibilités communes entre un prof et une classe sur une semaine donnée
int School::nb_connections(int id_prof, int id_promo, int num_week, list<progSemester> prog_week) {
    
    int i,j=0,nb=0;
    
    //On regarde si les cours du profs ont déjà été donnés, ou si ils ne correspondent pas à la classe
    for(i=0 ; i<_profs[id_prof].nb_courses() ; i++) {
        //Si le cours n'est pas dans le programme de la semaine
      if(!courseIsInWeek(prog_week, _profs[id_prof].get_id_course(i))) {
            j++;
        }
        else if(!_promos[id_promo].has_course(_profs[id_prof].get_id_course(i))||_promos[id_promo].has_course_received(_profs[id_prof].get_id_course(i), num_week))
            j++;     
    }
    
    //Le prof n'a plus aucun cours à donner à cette classe
    if(j==i)
        return -1;
    
    //Le prof a encore des cours à donner, on compte ses disponibilités communes à la classe
    for(i=0 ; i<22 ; i++) {
        if(_profs[id_prof].is_available(num_week, i) && _promos[id_promo].is_available(num_week, i))
            nb++;
    }
    
    return nb;
    
}

//Fonction pour ajouter UN cours à une promo
void School::addCourse(list<progSemester> prog_week, int id_prof, int id_promo, int num_week) {
    
    int i;
    int nb_course = _profs[id_prof].nb_courses();
    bool course_add = false;
    
    //Choix du cours que l'on va ajouter
    for(i=0 ; i<nb_course ; i++) {
        //On regarde dans la liste des cours du profs si il y en a qui ont déja été donnée et si il se trouve dans le programme de la semaine
        if(!_promos[id_promo].has_course_received(_profs[id_prof].get_id_course(i), num_week) && courseIsInWeek(prog_week, _profs[id_prof].get_id_course(i))) {
            //On crée le cours du prof dans la promo à la semaine num_week
            grantLecture(id_prof, id_promo, _profs[id_prof].get_id_course(i), num_week);
            course_add = true;
            break;
        }                
    }
    //Si on a pas réussi à ajouter un cours
    if(!course_add) {
        cout <<"Tous les cours du profs ont déja été donnée" << endl;
        exit(EXIT_FAILURE);
    }
}

//Méthode pour savoir si un cours est dans la semaine ou non
bool School::courseIsInWeek(list<progSemester> prog_week, int id_course) {
    for(list<progSemester>::iterator it=prog_week.begin() ; it!=prog_week.end() ; it++) {
        if ((*it)._id_course == id_course)
            return true;
    }
    return false;
}


void School::grantLecture(int id_prof, int id_promo, int id_course, int num_week) {
    
    int i;
    int nb_hour_course = _courses[id_course].get_lecture_size();
    
    //Si le cours est sur 4H on doit le faire commencer par un créneau pair
    if (nb_hour_course==4) {
        for(i=0 ; i<22 ; i++) {
            //Si on est sur un créneau pair
            if(i%2 == 0) {
                //Si la classe et la promo sont libre sur les 2 créneaux qui s'enchaine
                if((_profs[id_prof].is_available(num_week, i)) && (_profs[id_prof].is_available(num_week, i+1)) &&
                        (_promos[id_promo].is_available(num_week, i)) &&  (_promos[id_promo].is_available(num_week, i+1))) {
                    _profs[id_prof].grant_lecture(_courses[id_course], _promos[id_promo].get_week(num_week), i);
                    _profs[id_prof].grant_lecture(_courses[id_course], _promos[id_promo].get_week(num_week), i+1);
                    break;
                }
            }
        }
    }
    
    else {
        for(i=0 ; i<22 ; i++) {
            if((_profs[id_prof].is_available(num_week, i)) && (_promos[id_promo].is_available(num_week, i))) {
                _profs[id_prof].grant_lecture(_courses[id_course], _promos[id_promo].get_week(num_week), i);
                break;
            }
        }
    }
}

//Fonction permettant de dupliquer les cours de la semaine précédente
void School::previousWeek(Promo &p, list<progSemester> prog_week, int num_week) {
    
    if(num_week>0) {
        for(list<progSemester>::iterator it = prog_week.begin() ; it!=prog_week.end() ; it++) {
            if(p.has_course_received((*it)._id_course, num_week-1) && num_week < (*it)._start_week + (*it)._nb_weeks) {
                int id_prof = p.get_id_prof((*it)._id_course, num_week-1);
                int index = p.get_course_index((*it)._id_course, num_week-1);
                
                _profs[id_prof].grant_lecture(_courses[(*it)._id_course], p.get_week(num_week), index);
            }
        }
    }
}
