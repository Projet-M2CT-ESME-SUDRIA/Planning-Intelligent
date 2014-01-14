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
    
    int nb_hours;
    
    //On trie les profs par dispo
    sort(profs.begin(), profs.end(), sort_by_availability);
    //Pour chaque profs
    for (int i = 0; i < profs.size(); i++) {
        //Pour chaque cours
        for (int j = 0; j < profs.at(i).get_given_courses().size() ; j++) {
            nb_hours = profs.at(i).get_given_courses().at(j).get_nb_hours();
        }
    }
}
