/* 
 * File:   main.cpp
 * Author: elysiunk
 *
 * Created on 28 novembre 2013, 17:04
 */

#include <cstdlib>
#include <iostream>
#include "classes.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    // List of all courses for the first semester for M1
    course c_elec_puissance(1, "Terminologie, fonctions et composants d'electronique de puissance ", 16);
    course c_conversion_nrj(2, "Conversion de l'énergie", 38);
    course c_auto_lineaire(3, "Automatique linéaire", 32);
    course c_elec_telecom(4, "Electronique pour les telecoms", 26);
    course c_tns(5, "Traitement numerique du signal", 36);
    course c_comm_num(6, "Communication numerque", 36);
    course c_reseaux(7, "Les reseaux", 24);
    course c_prog_evol(8, "Programmation evoluee et langages", 32);
    course c_unix(9, "Unix", 20);
    course c_microsys(10, "Microsystemes", 34);
    course c_concept_circuit_num(11, "Conception circuits numeriques", 32);
    course c_outil_dev_microsys(12, "Outil developpement microsysteme", 12);
    course c_anglais(13, "Anglais", 26);
    course c_mineur(14, "Mineure manageriale", 44);
    course c_suivi_proj(15, "Plannification et suivi de projets", 20);
    
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
    prof ledoux(1, "Ledoux", v1);
    prof p_ait(2, "Ait", intern_available);
    prof p_gadot(3, "Gadot", v1);
    prof p_maizy(4, "Maizy", intern_available);
    prof p_bassi(5, "Bassi", intern_available);
    prof p_bourbon(5, "Bourbon", v1);
    prof p_chenoune(6, "Chenoune", intern_available);
    prof p_herry(7, "Herry", intern_available);
    prof p_touseau(8, "Touseau", intern_available);
    prof p_gemal(9, "Gemal", intern_available);
    prof p_eden(10, "Eden", intern_available);
    prof p_mineur(11, "profMineur", mineur_available);
    prof p_vedel(12, "Vedel", v1);
    
    p_herry.displayAvail();
    p_vedel.displayAvail();
    p_mineur.displayAvail();
    
    return 0;
}

