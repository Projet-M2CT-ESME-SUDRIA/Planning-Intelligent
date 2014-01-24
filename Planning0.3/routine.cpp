#include <iostream>
#include "routine.h"
#include "parseFile.h"

using namespace std;
bool compare(Prof &a, Prof &b, int num_week){
    return a.get_nb_availability(num_week)>b.get_nb_availability(num_week);
}

bool sort_by_availability(Prof a, Prof b) {
    int cmpt_a = 0;
    int cmpt_b = 0;
    list<int> availability_a = a.get_availability(0);
    list<int> availability_b = b.get_availability(0);
    
    for (int i = 0; i < 22; i++) {
        if (at(availability_a,i) == 1)
            cmpt_a ++;
    }
    
    for (int i = 0; i < 22; i++) {
        if (at(availability_b,i) == 1)
            cmpt_b ++;
    }

    return cmpt_a < cmpt_b;    
}

//Amélioration, ajoute les cours sur plusieurs semaines
void rout2(map<int, Prof> &profs, map<int, Promo> &promos, map<int, Course> courses) {
    
    //On trie les profs par dispo
//    sort(profs.begin(), profs.end(), sort_by_availability);
    
    //Pour chaque profs
    for (map<int, Prof>::iterator it=profs.begin(); it!=profs.end(); it++) {
        grant_lectures((*it).second, promos.at(0), courses);  
    }
    display_weeks(promos.at(0));
}

void grant_lectures(Prof &p, Promo &c, map<int, Course> courses) {
    
    int nb_hours;
    int index;
    
    
    int nb_given_course =  p.get_given_courses().size();
    list<int> given_courses = p.get_given_courses();
    list<int>::iterator it;
    
    for (int j = 0; j < nb_given_course ; j++) {
        
        nb_hours = courses.at(p.get_id_course(j)).get_nb_hours();
        it = given_courses.begin();
        advance(it, j);
        
        //Si le nombre de cours de 2h est plus grand que le nombre de semaine
        //on va placer des cours de 4h
        if (nb_hours > 14*2) {
            index = get_match_prof_promo2(p, c, nb_hours);
            
            if(index != -1) {
                for (int l = 0; l < nb_hours/4; l++) {
                    p.grant_lecture(courses.at(*it), c.get_week(l), index);
                    p.grant_lecture(courses.at(*it), c.get_week(l), index+1);
                }
                if (nb_hours%4 != 0) {

                    p.grant_lecture(courses.at(*it), c.get_week((nb_hours/4)), index);
                    
                }
            }
        }
        else {
            index = get_match_prof_promo(p, c, nb_hours);
        
            if(index != -1) {
                for (int l = 0; l < nb_hours/2; l++) {
                    p.grant_lecture(courses.at(*it), c.get_week(l), index);                 
                }
            }
        }
    }
}

int get_match_prof_promo(Prof &p, Promo &c, int nb_hours) {
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

int get_match_prof_promo2(Prof &p, Promo &c, int nb_hours) {
    int nb_avail_prof;
    int nb_avail_promo;
    
    for (int k = 0; k < 22; k++) {
        nb_avail_prof = 0;
        nb_avail_promo = 0;
        
        //Si le prof est dispo la première semaine sur le créneaux k
        if (p.is_available(0,k) && p.is_available(0,k+1)){
            nb_avail_prof = 2;
            
            nb_avail_promo = cmpt_avail_promo(c, nb_avail_promo, 0, k);
            nb_avail_promo = cmpt_avail_promo(c, nb_avail_promo, 0, k+1);
            
            for (int l = 1; l < nb_hours/4; l++) {
                nb_avail_prof = cmpt_avail_prof(p, nb_avail_prof, l, k);
                nb_avail_prof = cmpt_avail_prof(p, nb_avail_prof, l, k+1);
                nb_avail_promo = cmpt_avail_promo(c, nb_avail_promo, l, k);
                nb_avail_promo = cmpt_avail_promo(c, nb_avail_promo, l, k+1);
            }
            if(nb_hours%4 != 0) {
                nb_avail_prof = cmpt_avail_prof(p, nb_avail_prof, (nb_hours/4), k);
                nb_avail_promo = cmpt_avail_promo(c, nb_avail_promo, (nb_hours/4), k);
            }
            
            
            if (nb_avail_prof == nb_hours/2 &&  nb_avail_promo == nb_hours/2) {
                return k;
            } 
        }
        k++;
    }
    return -1;
}
    
int cmpt_avail_prof(Prof &p, int nb_dispo_prof, int week, int index) {
    if(p.is_available(week,index)) {
        nb_dispo_prof ++;
    }
    return nb_dispo_prof;
}

int cmpt_avail_promo (Promo &p, int nb_dispo_promo, int week, int index) {
    if(p.is_available(week,index)) {
        nb_dispo_promo ++;
    }
    return nb_dispo_promo;
}

void display_weeks(Promo p) {
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 22; j++) {
            cout << p.get_week(i).get_lecture(j).get_id_course() << " ";
        }
        cout << endl;
    }
}

//Permet de savoir si un prof et une classe ont AU MOINS un cours en commun
int link_prof_promo(map<int, Course> courses, Prof p, Promo c) {
    
    int i;
    int nb_courses = p.nb_courses();
    for (i=0 ; i<nb_courses ; i++) {
        if(courses.at(p.get_id_course(i)).get_id_promo() == c.get_id_promo())
            return 1;
    }
    
    return 0;
}

//Donne le couple prof-classe qui a LE MOINS de disponibilités en commun sur une semaine donnée
//void best_connection(list<prof> profs, list<promo> promos, int num_week, int &prof_index, int &promo_index) {
//    
//    int i,j,buf=23;
//    
//    for(i=0 ; i<profs.size() ; i++) {
//        for(j=0 ; j<promos.size() ; j++) {
//            
//            //On vérifie que : le prof a encore au moins un cours à donner et que ses disponibilités sont les plus faibles
//            if(nb_connections(profs[i], promos[j], num_week) > 0 && nb_connections(profs[i], promos[j], num_week) < buf) {
//                buf = nb_connections(profs[i], promos[j], num_week);
//                prof_index = i;
//                promo_index = j;
//            }
//        }
//    }
//}

//Retourne le nombre de disponibilités communes entre un prof et une classe sur une semaine donnée
//int nb_connections(prof p, promo c, int num_week) {
//    
//    int i,j=0,nb;
//    
//    //On regarde si les cours du profs ont déjà été donnés, ou si ils ne correspondent pas à la classe
//    for(i=0 ; i<p.nb_courses() ; i++) {
//        if(!c.has_course(p.get_course(i)) || c.has_course_received(p.get_course(i), num_week))
//            j++;
//    }
//    
//    //Le prof n'a plus aucun cours à donner à cette classe
//    if(j==i)
//        return -1;
//    
//    //Le prof a encore des cours à donner, on compte ses disponibilités communes à la classe
//    for(i=0 ; i<22 ; i++) {
//        if(p.is_available(num_week, i) && c.is_available(num_week, i))
//            nb++;
//    }
//    
//    return nb;
//}


//void rout3 (list<prof> &profs, list<promo> &promos) {
//    
//    int num_week=0, prof_index, promo_index,course_index,a,hour, nb_hours;
//    int i=0;
//    while(i < 14) {
//        i++;
//        //On choisit le prof et la promo qui ont le moins de dispo communes
//        best_connection(profs, promos, num_week, prof_index, promo_index);
//
//        //On boucle sur les matières données par le prof
//        for(course_index=0 ; course_index< profs[prof_index].nb_courses() ; course_index++) {
//            nb_hours=profs[prof_index].get_course(course_index).get_nb_hours();
//            //On vérifie que la promo doit bien recevoir cette matière
//            a=promos[promo_index].has_course(profs[prof_index].get_course(course_index));
//
//            //On vérifie que le prof et la promo ont suffisamment de semaines
//            hour=get_match_prof_promo(profs[prof_index], promos[promo_index], nb_hours);
//
//            if(a && hour !=-1) {
//                profs[prof_index].grant(promos[promo_index], num_week, course_index, hour);
//            }
//        }
//    }
//    
//    display_weeks(promos.at(0));
//}