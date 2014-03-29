#include "school.h"
#include <iostream>

using namespace std;

void School::moveCourse() {
    int id_promo = -1;
    
    cout << "Déplacement de cours : " << endl;
    do {
        id_promo = selectionClasse();
        //Si on veut placer des cours non placé
        if(id_promo == _promos.size()) {
            moveForAddCourse();
        }
        //Si on veut déplacer des cours dans une promo
        else if(id_promo != -1) {
            moveACourse(id_promo);
        }
    }while (id_promo != -1);
}

void School::moveACourse(int id_promo) {
    int num_week_start = -1, num_slot_start = -1;
    int id_prof, id_course;
    int newSlot;
    list<possibleSlots> listNewSlots;
    
    display_schedule_one_promo(id_promo);
    selectionCourseToMove(num_week_start, num_slot_start);

    //Si on a bien sélectionner un cours
    if(courseInSelection(id_promo, num_week_start, num_slot_start)) {
        //Récupération des identifiants prof et cours
        id_prof = _promos[id_promo].get_week(num_week_start).get_lecture(num_slot_start).get_id_prof();
        id_course = _promos[id_promo].get_week(num_week_start).get_lecture(num_slot_start).get_id_course();

        //liste de tous les emplacements possible
        getPossibleSlots(listNewSlots, id_promo, id_prof);
        //choix du nouveau créneau
        newSlot = selectNewSlot(listNewSlots);

        if(newSlot >= 0) {
            courseNewPlace(id_promo, id_prof, id_course, listNewSlots, newSlot);
             _profs[id_prof].putAvailable(num_week_start, num_slot_start);
            _promos[id_promo].get_week(num_week_start).reinitialise_lecture(num_slot_start);
            display_schedule_one_promo(id_promo);
        }

        //Si il n'y pas de créneaux
        else
            cout << "Pas d'autre créneaux possible" << endl;
         }
    //Si il n'y a pas de cours sur la sélection
    else
        cout << "Mauvaise sélection de cours" << endl;
}

void School::moveForAddCourse() {
    int newSlot1, newSlot2;
    int new_course;
    int id_promo, id_course, id_prof;
    list<possibleSlots> listNewSlots;
    
    new_course = selectCourseToAdd();
    getIdProfPromoNewCours(new_course, id_promo, id_prof, id_course);
    getPossibleSlots(listNewSlots, id_promo, id_prof);
    //Si il s'agit d'un cours de 4, il faut impérativement placer dessuite les 4h
    if(_courses[id_course].get_lecture_size() == 4) {
        cout << "Sélectionner 2 créneaux pour le nouveau cours de 4h : " << endl;
        newSlot1 = selectNewSlot(listNewSlots);
        newSlot2 = selectNewSlot(listNewSlots);
        //Il faut que les deux créneaux choisi soit différent
        if(newSlot1 >= 0 && newSlot2 >=0 && (newSlot1 != newSlot2)) {
            courseNewPlace(id_promo, id_prof, id_course, listNewSlots, newSlot1);
            courseNewPlace(id_promo, id_prof, id_course, listNewSlots, newSlot2);
            removeCourseFromListe(new_course);
            display_schedule_one_promo(id_promo);
        }
        else
            cout << "Erreur dans les créneaux choisient" << endl;
    }
    //Si c'est un cours de 2h
    else {
        cout << "Sélection 1 créneaux pour le nouveau cours de 2h : " << endl;
        newSlot1 = selectNewSlot(listNewSlots);
        if(newSlot1 >= 0) {
            courseNewPlace(id_promo, id_prof, id_course, listNewSlots, newSlot1);
            removeCourseFromListe(new_course);
            display_schedule_one_promo(id_promo);
        }
        cout << "Erreur dans le créneau choisi" << endl;
    }
}

//Méthode pour sélectionner la classe 
int School::selectionClasse() {
    int i;
    int choice = -1;
    int nb_classe = _promos.size();
    
    cout << "Choisir la classe : " << endl;
    for(i = 0 ; i < nb_classe ; i++) {
        cout << "\t-" << _promos[i].get_name() << " : " << _promos[i].get_id() << endl;
    }
    cout << "\t-Placer les cours non placés : " << nb_classe << endl;;
    cout << "\t-Exit : -1" << endl;
    cin >> choice;
    
    if(choice >= 0 && choice <= nb_classe) {
        return choice;
    }
    
    return -1;
}

int School::selectCourseToAdd() {
    int nb_courses = _course_not_schedule.size();
    int cmpt = 0;
    int choice;
    
    do {
        cmpt = 0;
        cout << "Sélectionner le cours à ajouter : " << endl;
        for(list<courseNotSchedule>::iterator it=_course_not_schedule.begin() ; it!=_course_not_schedule.end() ; it++) {
            cout << cmpt << " : cours " << (*it)._id_course << " promo " << (*it)._id_promo << endl;
            cmpt ++;
        }

        cin >> choice;
    }while(choice < 0 && choice > nb_courses);
    
    return choice;
}

void School::getIdProfPromoNewCours(int new_course, int &id_promo, int &id_prof, int &id_course) {
    list<courseNotSchedule>::iterator it = _course_not_schedule.begin();
    advance(it, new_course);
    
    id_promo = (*it)._id_promo;
    id_prof = (*it)._id_prof;
    id_course = (*it)._id_course;
}

void School::removeCourseFromListe(int new_course) {
    list<courseNotSchedule>::iterator it = _course_not_schedule.begin();
    advance(it, new_course);
    _course_not_schedule.erase(it);
}

//Méthode pour sélectionner le cours que l'on veut déplacer et la nouvelle position qu'on veut lui donner
void School::selectionCourseToMove(int &num_week_start, int &num_slot_start) {
    
    do {
        cout << "Sélectionner le cours à changer" << endl;
        cout << "Semaine : ";
        cin >> num_week_start;
        cout << "Créneau : ";
        cin >> num_slot_start;
        cout << "Test : " << num_week_start << " , " << num_slot_start << endl;
    }while((num_week_start<0 && num_week_start>=_nb_week) && (num_slot_start<0 && num_slot_start>=22));
    
}

//Méthode pour vérifier que la semaine et le créneaux choisi a bien un cours
bool School::courseInSelection(int id_promo, int num_week_start, int num_slot_start) {
    if(_promos[id_promo].get_week(num_week_start).get_lecture(num_slot_start).get_id_course() != -1)
        return true;
    return false;
}

//Méthode pour vérifier qu'il est possible de placer le cours dans la position que l'on a choisi
void School::courseNewPlace(int id_promo, int id_prof, int id_course, list<possibleSlots> listNewSlots, int newSlot) {
    
    list<possibleSlots>::iterator it=listNewSlots.begin();
    advance(it, newSlot);
    //Création du cours
    _profs[id_prof].grant_lecture(_courses[id_course], _promos[id_promo].get_week((*it).num_week), (*it).slot);
}

//Méthode pour liste l'ensemble des créneaux possible pour placer le cours.
void School::getPossibleSlots(list<possibleSlots> &listNewSlots, int id_promo, int id_prof) {
    int i, j;
    possibleSlots tmp;
    
    //On parcourt toutes les semaines
    for(i = 0 ; i < _nb_week ; i++) {
        //On parcours tous les créneaux de la semaine
        for(j = 0 ; j < 22 ; j++) {
            if(_promos[id_promo].is_available(i,j) && _profs[id_prof].is_available(i,j)) {
                tmp.num_week = i;
                tmp.slot = j;
                listNewSlots.push_back(tmp);
            }
        }
    }
}

int School::selectNewSlot(list<possibleSlots>listNewSlots) {
    int cmpt = 0, choice = -1;
    int nbNewSlot = listNewSlots.size();
    
    if(nbNewSlot > 0) {
        cout << "Sélectionner le nouveau créneau : " << endl;
        for(list<possibleSlots>::iterator it=listNewSlots.begin() ; it !=listNewSlots.end() ; it++) {
            cout << "\t" << cmpt << " : semaine " << (*it).num_week << " creneau " << (*it).slot << endl;
            cmpt++;
        }
        cin >> choice;
        return choice;
    }
    
    cout << "Pas d'autre créneau possible" << endl;
    return -1;
}
