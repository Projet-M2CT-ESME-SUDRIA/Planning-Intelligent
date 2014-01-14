/* 
 * File:   main.cpp
 * Author: elysiunk
 *
 * Created on 28 novembre 2013, 17:04
 */

#include <cstdlib>
#include <iostream>
#include "parseFile.h"


using namespace std;

bool sort_by_availability(prof a, prof b) {
    int cmpt_a = 0;
    int cmpt_b = 0;
    vector<int> availability_a = a.get_availability(0);
    vector<int> availability_b = b.get_availability(0);
    
    for (int i = 0; i < 22; i++) {
        if (availability_a.at(i) == 1)
            cmpt_a ++;
    }
    
    for (int i = 0; i < 22; i++) {
        if (availability_b.at(i) == 1)
            cmpt_b ++;
    }

    return cmpt_a < cmpt_b;    
}

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
    string name, nb_student, courses, nb_weeks;
    
    cout << "Nom de la classe" << endl;
    cin >> name;
    cout << "Nombre d'élève dans la classe" << endl;
    cin >> nb_student;
    cout << "Liste des cours suivis par la classe" << endl;
    cin >> courses;
    cout << "Nombre de semaine de cours" << endl;
    cin >> nb_weeks;
    
    add_promo_to_db(name, nb_student, courses, nb_weeks);
}

void get_profs(vector<prof> &profs, vector<course> courses) {
    
    parse_profs(profs, courses);
    
    for(int i=0 ; i<profs.size() ; i++) {
        profs[i].list_profs();
    }
}

void get_courses(vector<course> &courses) {
    
    parse_courses(courses);
    
    for(int i=0 ; i<courses.size() ; i++) {
        courses[i].list_courses();
    }
}

void get_promos(vector<promo> &promos, vector<course> &courses) {
    parse_promo(promos, courses);
    
    for(int i=0 ; i<promos.size() ; i++) {
        promos[i].list_promos();
    }  
}

void test2() {
    
    bool exit=false;
    int choice=0;
    vector<course> courses;
    vector<prof> profs;
    
    while(!exit) {
        
        cout << "1. ajouter un cours" << endl;
        cout << "2. ajouter un prof" << endl;
        cout << "3. recuperer la liste des matieres" << endl;
        cout << "4. recuperer la liste des profs" << endl;
        cout << "0. quitter" << endl;
        cin >> choice;
        
        switch(choice) {
            case 1:
                add_course();
                break;
                
            case 2:
                add_prof();
                break;
                
            case 3:
                get_courses(courses);
                break;
                
            case 4:
                get_profs(profs, courses);
                break;
                
            case 0:
                exit = true;
                break;
                
            default:
                exit=true;
                break;
        }
    }
    
    return;
}

void change_dispo(prof &profs) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 22; j++) {
            cout << profs.get_availability(i).at(j);
        }
        cout << endl;

    }
    cout << endl << endl;
    profs.set_availability(0,1);

    cout << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 22; j++) {
            cout << profs.get_availability(i).at(j);
        }
        cout << endl;

    }
                
}

void myRout(vector<course> &courses, vector<prof> &profs, vector<promo> &promos) {
    std::vector<course> testCourse;
    //Pour chaque profs
    for (int i = 0; i < profs.size(); i++) {
        for (int j = 0; j < 22; j++) {
            cout << profs.at(i).get_availability(0).at(j);
        }
        cout << endl;
        
        //Pour l'ensemble des cours qu'il donne
        for (int j = 0; j < profs.at(i).get_given_courses().size(); j++) {
            //Pour toutes ces disponnibilité
            for (int k = 0; k < 22; k++) {
                //Si le prof est libre sur le créneau on ajoute le cours
                if (profs.at(i).is_available(0,k)) {
                    cout << "Le prof est libre au créneau : " << k << endl;
                    if (profs.at(i).grant_lecture(profs.at(i).get_given_courses().at(j), promos.at(0).get_week(0), k)) {
                        break;
                    }    
                }
            }
        }
        for (int j = 0; j < 22; j++) {
            cout << profs.at(i).get_availability(0).at(j);
        }
        cout << endl;
    }
    
    for (int j = 0; j < 22; j++) {
        cout << promos.at(0).get_week(0).get_lecture(j).get_id_course() << endl;
    }
}

void test3() {
    
    bool exit=false;
    int choice=0;
    int i = 0;
    vector<course> courses;
    vector<prof> profs;
    vector<promo> promos;
    
    while(!exit) {
        
        cout << "1. ajouter un cours" << endl;
        cout << "2. ajouter un prof" << endl;
        cout << "3. ajouter une promo" << endl;
        cout << "4. recuperer la liste des matieres" << endl;
        cout << "5. recuperer la liste des profs" << endl;
        cout << "6. recuperer la liste des classes" << endl;
        cout << "7. test modifications dispo" << endl;
        cout << "8. test routine" << endl;
        cout << "0. quitter" << endl;
        cin >> choice;
        
        switch(choice) {
            case 1:
                add_course();
                break;
                
            case 2:
                add_prof();
                break;
                
            case 3:
                add_promo();
                break;
                
            case 4:
                get_courses(courses);
                break;
                
            case 5:
                get_profs(profs, courses);
                break;
                
            case 6:
                get_promos(promos, courses);
                break;
                
            case 7:
                change_dispo(profs.at(0));
                break;
                
            case 8:
                myRout(courses,profs,promos);
                break;
                
            case 0:
                exit = true;
                break;
                
            default:
                exit=true;
                break;
        }
    }
    
    return;
                
}

int main(int argc, char* argv[]) {
   test3(); 
   
   return 0;
}