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

#endif	/* ROUTINE_H */

