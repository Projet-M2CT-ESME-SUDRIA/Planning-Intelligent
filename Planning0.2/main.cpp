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

void test(){
    vector<prof> vector_prof;
    
    // List of all courses for the first semester for M1
    /*course c_elec_puissance("Terminologie, fonctions et composants d'electronique de puissance ", 16);
    course c_conversion_nrj("Conversion de l'énergie", 38);
    course c_auto_lineaire("Automatique linéaire", 32);
    course c_elec_telecom("Electronique pour les telecoms", 26);
    course c_tns("Traitement numerique du signal", 36);
    course c_comm_num("Communication numerque", 36);
    course c_reseaux("Les reseaux", 24);
    course c_prog_evol("Programmation evoluee et langages", 32);
    course c_unix("Unix", 20);
    course c_microsys("Microsystemes", 34);
    course c_concept_circuit_num("Conception circuits numeriques", 32);
    course c_outil_dev_microsys("Outil developpement microsysteme", 12);
    course c_anglais("Anglais", 26);
    course c_mineur("Mineure manageriale", 44);
    course c_suivi_proj("Plannification et suivi de projets", 20);
    
    //Creation of a vector for the availabilities of prof
    int t1[] = {0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0};
    vector<int> v1 (t1, t1 + sizeof(t1) / sizeof(int));
    
    //Availabilities for intern prof
    int t2[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    vector<int> intern_available (t2, t2 + sizeof(t2) / sizeof(int));
    
    //Availabilities for mineur classe:
    int t3[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1};
    vector<int> mineur_available (t3, t3 + sizeof(t3) / sizeof(int));
    
    //List of all prof of first semester of M1
    prof p_ledoux("Ledoux");
    prof p_ait("Ait");
    prof p_gadot("Gadot");
    prof p_maizy("Maizy");
    prof p_bassi("Bassi");
    prof p_bourbon("Bourbon");
    prof p_chenoune("Chenoune");
    prof p_herry("Herry");
    prof p_touseau("Touseau");
    prof p_gemal("Gemal");
    prof p_eden("Eden");
    prof p_mineur("profMineur");
    prof p_vedel("Vedel");
    
    //Add availability for all prof
    p_ledoux.add_availability(14, v1);
    p_ait.add_availability(14, intern_available);
    p_gadot.add_availability(14, v1);
    p_maizy.add_availability(14, intern_available);
    p_bassi.add_availability(14, intern_available);
    p_bourbon.add_availability(14, v1);
    p_chenoune.add_availability(14, intern_available);
    p_herry.add_availability(14, intern_available);
    p_touseau.add_availability(14, intern_available);
    p_gemal.add_availability(14, intern_available);
    p_eden.add_availability(14, intern_available);
    p_mineur.add_availability(14, mineur_available);
    p_vedel.add_availability(14, v1);
    
    //Add given course for all prof
    p_ledoux.add_given_course(c_elec_puissance);
    p_ledoux.add_given_course(c_conversion_nrj);
    p_ait.add_given_course(c_auto_lineaire);
    p_gadot.add_given_course(c_elec_telecom);
    p_maizy.add_given_course(c_tns);
    p_bassi.add_given_course(c_comm_num);
    p_bourbon.add_given_course(c_reseaux);
    p_chenoune.add_given_course(c_prog_evol);
    p_herry.add_given_course(c_unix);
    p_touseau.add_given_course(c_microsys);
    p_touseau.add_given_course(c_concept_circuit_num);
    p_touseau.add_given_course(c_outil_dev_microsys);
    p_gemal.add_given_course(c_microsys);
    p_eden.add_given_course(c_anglais);
    p_mineur.add_given_course(c_mineur);
    p_vedel.add_given_course(c_suivi_proj);
    
    //Add all prof in the vector
    vector_prof.push_back(p_ledoux);
    vector_prof.push_back(p_ait);
    vector_prof.push_back(p_gadot);
    vector_prof.push_back(p_maizy);
    vector_prof.push_back(p_bassi);
    vector_prof.push_back(p_bourbon);
    vector_prof.push_back(p_chenoune);
    vector_prof.push_back(p_herry);
    vector_prof.push_back(p_touseau);
    vector_prof.push_back(p_gemal);
    vector_prof.push_back(p_eden);
    vector_prof.push_back(p_mineur);
    vector_prof.push_back(p_vedel);
    
    //prof test;
    sort(vector_prof.begin(), vector_prof.end(), sort_by_availability);
    for (int i = 0; i < 13; i++) {

        cout << vector_prof.at(i).get_name() << endl;

    }
    
    //Creation of one promo M1
    promo m1("M1A", 70);
    
    //Add course for M1A
    m1.add_course(c_elec_puissance);
    m1.add_course(c_conversion_nrj);
    m1.add_course(c_auto_lineaire);
    m1.add_course(c_elec_telecom);
    m1.add_course(c_tns);
    m1.add_course(c_comm_num);
    m1.add_course(c_reseaux);
    m1.add_course(c_prog_evol);
    m1.add_course(c_unix);
    m1.add_course(c_microsys);
    m1.add_course(c_concept_circuit_num);
    m1.add_course(c_outil_dev_microsys);
    m1.add_course(c_anglais);
    m1.add_course(c_mineur);
    m1.add_course(c_suivi_proj);
    
    //Create all week for M1A
    week w1(m1.get_id(), 1);
    week w2(m1.get_id(), 2);
    week w3(m1.get_id(), 3);
    week w4(m1.get_id(), 4);
    week w5(m1.get_id(), 5);
    week w6(m1.get_id(), 6);
    week w7(m1.get_id(), 7);
    week w8(m1.get_id(), 8);
    week w9(m1.get_id(), 9);
    week w10(m1.get_id(), 10);
    week w11(m1.get_id(), 11);
    week w12(m1.get_id(), 12);
    week w13(m1.get_id(), 13);
    week w14(m1.get_id(), 14);
    
    //Add week to M1A
    m1.add_week(w1);
    m1.add_week(w2);
    m1.add_week(w3);
    m1.add_week(w4);
    m1.add_week(w5);
    m1.add_week(w6);
    m1.add_week(w7);
    m1.add_week(w8);
    m1.add_week(w9);
    m1.add_week(w10);
    m1.add_week(w11);
    m1.add_week(w12);
    m1.add_week(w13);
    m1.add_week(w14);
    
    p_ledoux.grant_lecture(c_elec_puissance, w1, 3);
    p_ledoux.grant_lecture(c_elec_puissance, w2, 3);*/
}

void add_prof() {
    
    string name, availability, given_courses;
    
    cout << "Nom du prof" << endl;
    cin >> name;
    cout << "Disponibilites" << endl;
    cin >> availability;
    cout << "Cours donnes par le prof" << endl;
    cin >> given_courses;
    
    add_prof_to_db(name, availability, given_courses);
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