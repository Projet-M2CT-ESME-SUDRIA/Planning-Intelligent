/* 
 * File:   dataInitialisation.h
 * Author: elysiunk
 *
 * Created on 14 janvier 2014, 14:33
 */

#ifndef DATAINITIALISATION_H
#define	DATAINITIALISATION_H

#include "course.h"
#include "lecture.h"
#include "prof.h"
#include "promo.h"
#include "week.h"

void add_prof();
void add_course();
void add_promo();
void get_profs(std::map<int, Prof> &profs, std::map<int, Course> courses);
void get_courses(std::map<int, Course> &courses);
void get_promos(std::map<int, Promo> &promos, std::map<int, Course> &courses);


#endif	/* DATAINITIALISATION_H */

