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
    prof p_ledoux(1, "Ledoux");
    prof p_ait(2, "Ait");
    prof p_gadot(3, "Gadot");
    prof p_maizy(4, "Maizy");
    prof p_bassi(5, "Bassi");
    prof p_bourbon(5, "Bourbon");
    prof p_chenoune(6, "Chenoune");
    prof p_herry(7, "Herry");
    prof p_touseau(8, "Touseau");
    prof p_gemal(9, "Gemal");
    prof p_eden(10, "Eden");
    prof p_mineur(11, "profMineur");
    prof p_vedel(12, "Vedel");
    
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
    
    //Creation of one promo M1
    promo m1(1, "M1A", 70);
    
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
    week w1(1, 1, 1);
    week w2(2, 1, 2);
    week w3(3, 1, 3);
    week w4(4, 1, 4);
    week w5(5, 1, 5);
    week w6(6, 1, 6);
    week w7(7, 1, 7);
    week w8(8, 1, 8);
    week w9(9, 1, 9);
    week w10(10, 1, 10);
    week w11(11, 1, 11);
    week w12(12, 1, 12);
    week w13(13, 1, 13);
    week w14(14, 1, 14);
    
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
    p_ledoux.grant_lecture(c_elec_puissance, w2, 3);
   
    return 0;
}

