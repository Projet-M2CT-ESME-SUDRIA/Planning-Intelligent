#include "school.h"
#include "parseFile.h"
#include <iostream>

using namespace std;

//Merge par rapport au nombre de semaines
std::list<int> merge_int(std::list<int>& left, std::list<int>& right) {
    
    list<int> result;
    int left_size = left.size();
    int right_size = right.size();
    int left_index = 0, right_index = 0;
    
    while (left_index < left_size && right_index < right_size) {
        if (at(left,left_index) > at(right, right_index)) {
            result.push_back(at(left,left_index));
            left_index++;
        }
        
        else {
            result.push_back(at(right, right_index));
            right_index++;
        }
    }
    
    if (left_index == left_size) {
        while (right_index < right_size) {
            result.push_back(at(right, right_index));
            right_index++;
	}
    } 
    
    else {
	while (left_index < left_size) {
	    result.push_back(at(left,left_index));
	    left_index++;
	}
    }
    
    return result;
}

//Tri par fusion
list<int> merge_sort_int(list<int> &l) {
    
    list<int> left;
    list<int> right;
    list<int> result;
    int size_list = l.size();
    int i;
    
    if (size_list <= 1) {
        return l;
    }
    
    int middle = (size_list / 2);
    
    for (i = 0; i < middle; i++) {        
        left.push_back(at(l,i));
    }
    
    for (i = middle; i < size_list; i++) {
        right.push_back(at(l,i));
    }
    
    left = merge_sort_int(left);
    right = merge_sort_int(right);
    result = merge_int(left, right);
    
    return result;   
}


//Fonction qui parcourt la liste de classes d'une promo et appelle la fonction de répartition des cours dans la semaine
void School::give_courses_promo(int id_year, list<progSemester> prog) {
    
    list<int> id_promo = getClassPromo(id_year);
    list<progSemester> prog_week;
    list<int> prof_week;
    int num_week;
    
    //Pour toutes les semaines du semestre
    for (num_week=0; num_week<_nb_week ; num_week++) {
        //on récupère le programme de la semaine et les profs qui vont pouvoir donner ces cours.
        prog_week = getProgWeek(prog, num_week);
        previousWeek(prog_week, id_promo, num_week);
        
        //Si il reste des cours à placer après l'appel de previous week
        if(prog_week.size() != 0) {
            prof_week = getProfWeek(prog_week);
            addCoursePromo(id_promo, prog_week, prof_week, num_week);
        }
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

void School::addCoursePromo(list<int> list_id_promo, list<progSemester> &prog_week, list<int> list_id_prof, int num_week) {
    int i;
    int nb_course_tot = (list_id_promo.size() * prog_week.size());
    //Id des profs et de la promo que l'on va ajouter, ayant le moins de créneaux en commun
    int profToAdd = -1, promoToAdd = -1;
    
    cout << "TEST : " << prog_week.size() << endl;
    
    nb_course_tot = nb_courses_to_schedule(prog_week, list_id_promo, num_week, nb_course_tot);
    
    cout << "TEST nb course to schedule : " << nb_course_tot << endl;
    
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
            display_schedule_promos();
            cout << "Course week : " << endl;
            for(list<progSemester>::iterator it=prog_week.begin() ; it!=prog_week.end() ; it++) {
                cout << "\t" << (*it)._id_course << endl;
            }
            cout << "ERREUR : " << endl;
            cout << "Semaine : " << num_week << endl;
            cout << i  << " sur " << nb_course_tot << endl;
            cout << "Pas de prof ou promo pour ajouter un cours" << endl;
            exit(EXIT_FAILURE);
        }
    }
}

//Fonction permettant de calculer le nombre de cours à placé en fonction des cours qui n'ont pas pu être
//la semaine précédente
int School::nb_courses_to_schedule(list<progSemester> prog_week, list<int> list_id_promo, int num_week, int nb_course_tot) {
    int nb_course_already_schedule = 0;
    int cmpt = 0;
//    //On regarde combien de cours n'ont pas pu être donnée la semaine d'avant pour les promos concernées
//    for(list<courseNotSchedule>::iterator it=_course_not_schedule.begin() ; it!=_course_not_schedule.end() ; it++) {
//        for(list<int>::iterator it_p=list_id_promo.begin() ; it_p!=list_id_promo.end() ; it_p++) {
//            if ((*it)._id_promo == _promos[*it_p].get_id() && (*it)._num_week == num_week-1 && courseIsInWeek(prog_week, (*it)._id_course))
//                nb_course_not_schedule++;
//        }
//    }
    for(list<progSemester>::iterator it=prog_week.begin() ; it!=prog_week.end() ; it++)
        for(list<int>::iterator it_p=list_id_promo.begin() ; it_p!=list_id_promo.end() ; it_p++) {
            //Compte le nombre de cours non placés
            if(_promos[*it_p].has_course_received((*it)._id_course, num_week)) {
                nb_course_already_schedule++;
        }
    }
    //Si il y a eu un cours qui n'a pas pu être placé, on refait le calcul du nombre de cours à 
    //essayer d'ajouter cette semaine
//    if(nb_course_already_schedule_schedule > 0) {
//        nb_course_tot = nb_course_tot - nb_course_already_schedule;
//    }
    
    return nb_course_tot - nb_course_already_schedule;
}


//Donne le couple prof-classe qui a LE MOINS de disponibilités en commun sur une semaine donnée
void School::best_connection(list<progSemester> &prog_week, list<int> id_profs, list<int> id_promos, int num_week, int &prof_index, int &promo_index) {
    
    int buf=23;
    int nbConnection;
    int i;
    
    //Pour tous les profs sur la semaine
    for(list<int>::iterator it_prof=id_profs.begin() ; it_prof!=id_profs.end() ; it_prof++) {
        //Pour toutes les promos concernées
        for(list<int>::iterator it_promo=id_promos.begin() ; it_promo!=id_promos.end() ; it_promo++) {
            //On vérifie que : le prof a encore au moins un cours à donner et que ses disponibilités sont les plus faibles
            nbConnection = nb_connections(*it_prof, *it_promo, num_week, prog_week);            
            if(nbConnection > 0 && nbConnection < buf && !isInCourseNotSchedule(*it_prof, *it_promo, num_week)) {
                buf = nbConnection;
                prof_index = *it_prof;
                promo_index = *it_promo;
            }
        }
    }
}

bool School::isInCourseNotSchedule(int id_prof, int id_promo, int num_week) {
    for(list<courseNotSchedule>::iterator it=_course_not_schedule.begin() ; it!=_course_not_schedule.end() ; it++) {
        if ((*it)._id_prof == id_prof && (*it)._id_promo == id_promo && (*it)._num_week == num_week)
            return true;
    }
    return false;
}


//Retourne le nombre de disponibilités communes entre un prof et une classe sur une semaine donnée
int School::nb_connections(int id_prof, int id_promo, int num_week, list<progSemester> &prog_week) {
    
    int i,j=0,nb=0;
    int nbCourseProf = _profs[id_prof].nb_courses();
    bool coursePossible = false;
    
    //On regarde tous les cours que peut donner un professeur
    for(i=0 ; i<nbCourseProf ; i++) {
        //Si le cours est dans le programme de la semaine et que la promotion n'a pas eu le cours encore
        if(!_promos[id_promo].has_course_received(_profs[id_prof].get_id_course(i), num_week) && courseIsInWeek(prog_week, _profs[id_prof].get_id_course(i))) {
            //On va pouvoir donc placer ce cours. On va aller calculer le nombre de créneau en commum entre le prof et la promo
            coursePossible = true;
            break;
        }      
        else
            coursePossible = false;
    }
        
    //Si le cours doit être donné, on calcul le nombre de créneau en commum
    if (coursePossible) {
        for(i=0 ; i<22 ; i++) {
            if(_profs[id_prof].is_available(num_week, i) && _promos[id_promo].is_available(num_week, i))
                nb++;
        }
    }
    else
        nb = -1;
    
    return nb;
    
}

//Fonction pour ajouter UN cours à une promo
void School::addCourse(list<progSemester> &prog_week, int id_prof, int id_promo, int num_week) {
    
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
bool School::courseIsInWeek(list<progSemester> &prog_week, int id_course) {
    for(list<progSemester>::iterator it=prog_week.begin() ; it!=prog_week.end() ; it++) {
        if ((*it)._id_course == id_course)
            return true;
    }
    return false;
}


//bool School::grantLecture(int id_prof, int id_promo, int id_course, int num_week) {
//    
//    int i;
//    int nb_hour_course = _courses[id_course].get_lecture_size();
//    bool course_add = false;
//    
//    //Si le cours n'a pas pu être programmé la semaine précédente déja
//    if(isInCourseNotSchedule(id_prof, id_promo, num_week-1)) {
//        addCourseNotSchedule(id_course, id_prof, id_promo, num_week);
//        course_add = false;
//    }
//    
//    //Si le cours est sur 4H on doit le faire commencer par un créneau pair
//    else if (nb_hour_course==4) {
//        for(i=0 ; i<22 ; i++) {
//            //Si on est sur un créneau pair
//            if(i%2 == 0) {
//                //Si la classe et la promo sont libre sur les 2 créneaux qui s'enchaine
//                if((_profs[id_prof].is_available(num_week, i)) && (_profs[id_prof].is_available(num_week, i+1)) &&
//                        (_promos[id_promo].is_available(num_week, i)) &&  (_promos[id_promo].is_available(num_week, i+1))) {
//                    _profs[id_prof].grant_lecture(_courses[id_course], _promos[id_promo].get_week(num_week), i);
//                    _profs[id_prof].grant_lecture(_courses[id_course], _promos[id_promo].get_week(num_week), i+1);
//                    course_add = true;
//                    break;
//                }
//            }
//        }
//        //Si le cours de 4h n'a pas pu être créé
//        if (!course_add) {
//            //On ajoute le cours dans la liste des cours non placé
//            addCourseNotSchedule(id_course, id_prof, id_promo, num_week);
//            course_add = false;
//        }
//    }
//    else {
//        for(i=0 ; i<22 ; i++) {
//            if((_profs[id_prof].is_available(num_week, i)) && (_promos[id_promo].is_available(num_week, i))) {
//                _profs[id_prof].grant_lecture(_courses[id_course], _promos[id_promo].get_week(num_week), i);
//                course_add = true;
//                break;
//            }
//        }
//    }
//    
//    return course_add;
//}
bool School::grantLecture(int id_prof, int id_promo, int id_course, int num_week) {
    
    int i;
    int nb_hour_course = _courses[id_course].get_lecture_size();
    bool course_add = false;

    list<int> commonSlots;

    //Si le cours n'a pas pu être programmé la semaine précédente déja
    if(isInCourseNotSchedule(id_prof, id_promo, num_week-1)) {
        addCourseNotSchedule(id_course, id_prof, id_promo, num_week);
        course_add = false;
    }
    
    //Si le cours est sur 4H on doit le faire commencer par un créneau pair
    else if (nb_hour_course==4) {
        for(i=0 ; i<22 ; i++) {
            //Si on est sur un créneau pair
            if(i%2 == 0) {
                //Si la classe et la promo sont libres sur les 2 créneaux qui s'enchainent
                if((_profs[id_prof].is_available(num_week, i)) && (_profs[id_prof].is_available(num_week, i+1)) &&
                (_promos[id_promo].is_available(num_week, i)) &&  (_promos[id_promo].is_available(num_week, i+1))) {

                    commonSlots.push_back(i);
                }
            }
        }

        int randSlot, s;

        if(!commonSlots.empty()) {
            s=commonSlots.size();
            randSlot = at(commonSlots, rand()%s);

            _profs[id_prof].grant_lecture(_courses[id_course], _promos[id_promo].get_week(num_week), randSlot);
            _profs[id_prof].grant_lecture(_courses[id_course], _promos[id_promo].get_week(num_week), randSlot+1);
            course_add = true;
        }

        else
            course_add=false;

        //Si le cours de 4h n'a pas pu être créé
        if (!course_add) {
            //On ajoute le cours dans la liste des cours non placé
            addCourseNotSchedule(id_course, id_prof, id_promo, num_week);
        }
    }
    else {
        for(i=0 ; i<22 ; i++) {
            if((_profs[id_prof].is_available(num_week, i)) && (_promos[id_promo].is_available(num_week, i))) {
                
                commonSlots.push_back(i);
            }
        }

        int randSlot, s;

        if(!commonSlots.empty()) {
            s=commonSlots.size();
            randSlot = at(commonSlots, rand()%s);

            _profs[id_prof].grant_lecture(_courses[id_course], _promos[id_promo].get_week(num_week), randSlot);
            course_add = true;
        }
    }
    
    return course_add;
}

//Méthode pour ajouter un cours non placé dans la liste de courseNotSchedule
void School::addCourseNotSchedule(int id_course, int id_prof, int id_promo, int num_week) {
    cout << "Pas de créneau de 4h disponnible pour le cours " << id_course ;
    cout << " avec le prof " << id_prof << " pour la promo " << id_promo << endl;
    //On ajoute le cours avec le prof promo semaine dans la liste des cours qui n'ont pas pu être placé.
    courseNotSchedule c;
    c._id_course = id_course;
    c._id_prof = id_prof;
    c._id_promo = id_promo;
    c._num_week = num_week;
    _course_not_schedule.push_back(c);   
}

//Fonction permettant de dupliquer les cours de la semaine précédente
void School::previousWeek(list<progSemester> &prog_week, list<int> id_promo, int num_week) {
    
    int cmpt_course_add_promo = 0;
    int nb_promo = id_promo.size();
    bool new_course_week = false;
    list<int> course_to_erase;
    int position = 0;
    //Si on a déja placé les cours sur la première semaine
    if(num_week>0) {
        //On parcourt tous les cours de la semaine que l'on doit placé
        for(list<progSemester>::iterator it_prog = prog_week.begin() ; it_prog!=prog_week.end() ; it_prog++) {
            promoAsCourseBefore((*it_prog), id_promo, num_week, cmpt_course_add_promo, new_course_week);
            
            //Si le cours a pu être ajouté pour toutes les promos
            if(cmpt_course_add_promo == nb_promo) {
                //On enlève le cours du programme de la semaine car il a déja été fait
                course_to_erase.push_back((position));
            }
            //Si le cours n'a pas été donné la semaine d'avant (nouveau cours pour la promo débutant au milieu du semestre)
            else if (new_course_week){
                new_course_week = false;
            }
            else {
                cout << "ECHEC : ";
                cout << (*it_prog)._id_course << " le prof ou la promo n'est pas libre entre les 2 semaines" << endl;
                cout << "Ou ce cours n'étais pas donné la semaine d'avant" << endl;
            }
            cmpt_course_add_promo = 0;
            position++;
        }
        
        course_to_erase = merge_sort_int(course_to_erase);
        list<progSemester>::iterator it_p; 
        for(list<int>::iterator it_id=course_to_erase.begin() ; it_id!=course_to_erase.end() ; it_id++) {
            it_p= prog_week.begin();
            advance(it_p,(*it_id));
            prog_week.erase(it_p);
        }
        
    }
}

//Méthode pour savoir si la promotion à déja eu le cours la semaine d'avant avant de l'ajouter avec previous week
void School::promoAsCourseBefore(progSemester it_prog, list<int> id_promo, int num_week, int &cmpt_course_add_promo, bool &new_course_week) {
    
    int nb_course_add = 0;
    //Pour toutes les promos avec lesquelles on travaille
    for(list<int>::iterator it_promo=id_promo.begin() ; it_promo!=id_promo.end() ; it_promo++) {
        //Si la classe à déjà eu le cours la semaine précédente
        if(_promos[*it_promo].has_course_received(it_prog._id_course, num_week-1)) {
            addCourseWithPreviousWeek((*it_promo), it_prog, num_week, cmpt_course_add_promo);
            nb_course_add++;
        }
    }
    //Si le cours a pu être donné à toutes les promos alors il ne s'agit pas d'un nouveau cours
    if (nb_course_add == id_promo.size()) {
        new_course_week = false;
    }
    //Sinon il s'agit d'un cours qui n'a jamais été donné encore ou d'un cours qui n'a pas pu être placé pour toutes les promos la 
    //semaine précédente
    else {
        new_course_week = true;
    }
}

//Méthode pour ajouter les cours avec les cours de la semaine d'avant
void School::addCourseWithPreviousWeek(int it_promo, progSemester it_prog, int num_week, int &cmpt_course_add_promo) {
    int id_prof = _promos[it_promo].get_id_prof_of_course(it_prog._id_course, num_week-1);
    int index = _promos[it_promo].get_course_index(it_prog._id_course, num_week-1);

    //Si le cours est de 4h on l'ajoute à l'index et index+1
    if(_courses[it_prog._id_course].get_lecture_size() == 4) {
        //On vérifie que le prof et la promo sont libres sur les créneaux
        if(_promos[it_promo].is_available(num_week, index) && _profs[id_prof].is_available(num_week, index) &&
                _promos[it_promo].is_available(num_week, index+1) && _profs[id_prof].is_available(num_week, index+1)) {

            _profs[id_prof].grant_lecture(_courses[it_prog._id_course], _promos[it_promo].get_week(num_week), index);
            _profs[id_prof].grant_lecture(_courses[it_prog._id_course], _promos[it_promo].get_week(num_week), index+1);

            cmpt_course_add_promo ++;
        }
        //Si un des deux n'est pas libre
        else {
            cout << "Prof ou promo non dispo pour cours 4h entre les deux semaines" << endl;
        }
    }
    //Si c'est un cours de 2H
    else {
        //On vérifie que le prof et la promo sont libre sur le créneau
        if(_promos[it_promo].is_available(num_week, index) && _profs[id_prof].is_available(num_week, index)) {
            _profs[id_prof].grant_lecture(_courses[it_prog._id_course], _promos[it_promo].get_week(num_week), index);
            cmpt_course_add_promo ++;
        }
        else {
            cout << "Prof ou promo non dispo pour cours 2h entre les deux semaines" << endl;
        }
    }
}
