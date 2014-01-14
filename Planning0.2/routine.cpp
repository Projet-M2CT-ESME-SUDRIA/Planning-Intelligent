#include <iostream>
#include "routine.h"

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

void rout1(vector<prof> &profs, vector<promo> &promos) {
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
                    //On essaye de placer le cours (Savoir si la promo à déja un cours ou non)
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

//Amélioration, ajoute les cours sur plusieurs semaines
void rout2(vector<prof> &profs, vector<promo> &promos) {
    
    //On trie les profs par dispo
    sort(profs.begin(), profs.end(), sort_by_availability);
    
    //Pour chaque profs
    for (int i = 0; i < profs.size(); i++) {
        grant_lectures(profs.at(i), promos.at(0));
    }
    
    display_weeks(promos.at(0));
}

void grant_lectures(prof &p, promo &c) {
    
    int nb_hours;
    int index;
    
    for (int j = 0; j < p.get_given_courses().size() ; j++) {
        nb_hours = p.get_given_courses().at(j).get_nb_hours();
        
        index = get_match_prof_promo(p, c, nb_hours);
        if(index != -1) {
            for (int l = 0; l < nb_hours/2; l++) {
                p.grant_lecture(p.get_given_courses().at(j), c.get_week(l), index);
            }
        }
    }
}

int get_match_prof_promo(prof &p, promo &c, int nb_hours) {
    int nb_avail_prof;
    int nb_avail_promo;
    
    //Pour tous les créneaux
    for (int k = 0; k < 22; k++) {
        nb_avail_prof = 0;
        nb_avail_promo = 0;
        //Si le prof est dispo la première semaine sur le créneaux k
        if (p.is_available(0,k)){
            nb_avail_prof ++;
            //on regarde si la classe est dispo la première semaine au créneau k
            nb_avail_promo = cmpt_avail_promo(c, nb_avail_promo, 0, k);

            //On regarde si ils sont dispo pour toutes les autres semaines.
            for (int l = 1; l < nb_hours/2; l++) {
                nb_avail_prof = cmpt_avail_prof(p, nb_avail_prof, l, k);
                nb_avail_promo = cmpt_avail_promo(c, nb_avail_promo, l, k);
            }
            if (nb_avail_prof == nb_hours/2 &&  nb_avail_promo == nb_hours/2) {
                return k;
            } 
        }
    } 
    return -1;
}
    

int cmpt_avail_prof(prof &p, int nb_dispo_prof, int week, int index) {
    if(p.is_available(week,index)) {
        nb_dispo_prof ++;
    }
    return nb_dispo_prof;
}

int cmpt_avail_promo (promo &p, int nb_dispo_promo, int week, int index) {
    if(p.is_available(week,index)) {
        nb_dispo_promo ++;
    }
    return nb_dispo_promo;
}

void display_weeks(promo p) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 22; j++) {
            cout << p.get_week(i).get_lecture(j).get_id_course();
        }
        cout << endl;
    }
}


int link_prof_promo(prof p, promo c) {
    
    int i,j;
    
    for (i=0 ; i<p.nb_courses() ; i++) {
        if(p.get_course(i).get_id_promo() == c.get_id_promo())
            return 1;
    }
    
    return 0;
}

void best_connection(vector<prof> profs, vector<promo> promos, int num_week, int &prof_index, int &promo_index) {
    
    int i,j,buf=23;
    
    for(i=0 ; i<profs.size() ; i++) {
        for(j=0 ; j<promos.size() ; j++) {
            if(nb_connections(profs[i], promos[j], num_week) < buf) {
                buf = nb_connections(profs[i], promos[j], num_week);
                prof_index = i;
                promo_index = j;
            }
        }
    }
}

int nb_connections(prof p, promo c, int num_week) {
    
    int i,j,nb;
    
    for(i=0 ; i<22 ; i++) {
        if(p.is_available(num_week, i) && c.is_available(num_week, i))
            nb++;
    }
    
    return nb;
}