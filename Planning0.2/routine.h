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

bool sort_by_availability(prof a, prof b);
void rout1(std::vector<prof> &profs, std::vector<promo> &promos);
void rout2(std::vector<prof> &profs, std::vector<promo> &promos);
int cmpt_avail_prof(prof &p, int nb_dispo_prof, int week, int index);
int cmpt_avail_promo (promo &p, int nb_dispo_promo, int week, int index);
void grant_lectures(prof &p, promo &c);
int get_match_prof_promo(prof &p, promo &c, int nb_hours);
void display_weeks(promo p);


#endif	/* ROUTINE_H */

