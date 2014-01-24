/* 
 * File:   routine.h
 * Author: elysiunk
 *
 * Created on 14 janvier 2014, 15:54
 */

#ifndef ROUTINE_H
#define	ROUTINE_H

#include "course.h"
#include "lecture.h"
#include "prof.h"
#include "promo.h"
#include "week.h"

bool sort_by_availability(Prof a, Prof b);
void rout2(std::map<int, Prof> &profs, std::map<int, Promo> &promos, std::map<int, Course> courses);
int cmpt_avail_prof(Prof &p, int nb_dispo_prof, int num_week, int index);
int cmpt_avail_promo (Promo &p, int nb_dispo_promo, int num_week, int index);
void grant_lectures(Prof &p, Promo &c, std::map<int, Course> courses);
int get_match_prof_promo(Prof &p, Promo &c, int nb_hours);
int get_match_prof_promo2(Prof &p, Promo &c, int nb_hours);
void display_weeks(Promo p);

//void best_connection(std::list<prof> profs, std::list<promo> promos, int num_week, int &prof_index, int &promo_index);
//int nb_connections(prof p, promo c, int num_week);
//void rout3(std::list<prof> &profs, std::list<promo> &promos);


#endif	/* ROUTINE_H */

