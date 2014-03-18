#include "school.h"
#include <iostream>

using namespace std;

void School::moveCourse() {
    int id_promo = -1;
    int num_week_start = -1, num_slot_start = -1;
    int num_week_end = -1, num_slot_end = -1;
    int id_prof, id_course;
    
    cout << "Déplacement de cours : " << endl;
    do {
        id_promo = selectionClasse();
        //Si on a bien choisi une promo
        if(id_promo != -1) {
            display_schedule_one_promo(id_promo);
            selectionCourseToMove(num_week_start, num_slot_start, num_week_end, num_slot_end);
            
            //Si on a bien sélectionner un cours
            if(courseInSelection(id_promo, num_week_start, num_slot_start)) {
                id_prof = _promos[id_promo].get_week(num_week_start).get_lecture(num_slot_start).get_id_prof();
                id_course = _promos[id_promo].get_week(num_week_start).get_lecture(num_slot_start).get_id_course();
                
                //Si on arrive à placer le cours
                if(courseNewPlaceCheck(id_promo, id_prof, id_course, num_week_end, num_slot_end)){
                    //Suppression de l'ancien cours
                    for (int j = 0; j < 14; j++) {
                        for (int k = 0; k < 22; k++) {
                            cout << _profs[id_prof].is_available(j,k);
                        }
                        cout <<endl;
                    }
                    cout << endl << endl;
                    
                    _profs[id_prof].putAvailable(num_week_start, num_slot_start);
                    cout << "test " << _promos[id_promo].get_week(num_week_start).get_lecture(num_slot_start).get_id_course() << endl;
                    _promos[id_promo].get_week(num_week_start).reinitialise_lecture(num_slot_start);
                    cout << "test " << _promos[id_promo].get_week(num_week_start).get_lecture(num_slot_start).get_id_course() << endl;
                    display_schedule_one_promo(id_promo);
                    
                    for (int j = 0; j < 14; j++) {
                        for (int k = 0; k < 22; k++) {
                            cout << _profs[id_prof].is_available(j,k);
                        }
                        cout <<endl;
                    }
                    cout << endl << endl;
                    
                }
                //Si on ne peut pas placer le cours 
                else
                    cout << "Implossible de placer le cours" << endl;
                    
            }
            //Si il n'y a pas de cours sur la sélection
            else
                cout << "Mauvaise sélection de cours" << endl;
        }
    }while (id_promo != -1);
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
    cout << "\t-Exit : -1" << endl;
    cin >> choice;
    
    if(choice >= 0 && choice < nb_classe) {
        return choice;
    }
    
    return -1;
}

//Méthode pour sélectionner le cours que l'on veut déplacer et la nouvelle position qu'on veut lui donner
void School::selectionCourseToMove(int &num_week_start, int &num_slot_start, int &num_week_end, int &num_slot_end) {
    
    do {
        cout << "Sélectionner le cours à changer" << endl;
        cout << "Semaine : ";
        cin >> num_week_start;
        cout << "Créneau : ";
        cin >> num_slot_start;
        cout << "Test : " << num_week_start << " , " << num_slot_start << endl;
    }while((num_week_start<0 && num_week_start>=_nb_week) && (num_slot_start<0 && num_slot_start>=22));
    
    do {
        cout << "Nouvelle position du cours" << endl;
        cout << "Semaine : ";
        cin >> num_week_end;
        cout << "Créneau : ";
        cin >> num_slot_end;
    }while((num_week_end<0 && num_week_end>=_nb_week) && (num_slot_end<0 && num_slot_end>=22));
}

//Méthode pour vérifier que la semaine et le créneaux choisi a bien un cours
bool School::courseInSelection(int id_promo, int num_week_start, int num_slot_start) {
    if(_promos[id_promo].get_week(num_week_start).get_lecture(num_slot_start).get_id_course() != -1)
        return true;
    return false;
}

//Méthode pour vérifier qu'il est possible de placer le cours dans la position que l'on a choisi
bool School::courseNewPlaceCheck(int id_promo, int id_prof, int id_course, int num_week_end, int num_slot_end) {
    
    //Si un cours est déja placer à la position choisi -> return false
    if (_promos[id_promo].get_week(num_week_end).get_lecture(num_slot_end).get_id_course() != -1)
        return false;
    //Si le prof n'est pas disponnible -> return false
    if(!_profs[id_prof].is_available(num_week_end, num_slot_end))
        return false;
    
    //Si tout c'est bien passé on change le cours et les dispo pour effectuer le changement de cours
    //Création du cours
    _profs[id_prof].grant_lecture(_courses[id_course], _promos[id_promo].get_week(num_week_end), num_slot_end);
    return true;
}
