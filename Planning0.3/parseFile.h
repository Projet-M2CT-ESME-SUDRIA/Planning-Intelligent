/* 
 * File:   parseFile.h
 * Author: Corentin
 *
 * Created on 3 décembre 2013, 15:06
 */

#ifndef PARSEFILE_H
#define	PARSEFILE_H


#include "course.h"
#include "lecture.h"
#include "prof.h"
#include "promo.h"
#include "week.h"
#include "school.h"

//General
std::list<std::string> read_file(std::string filename);
std::list<std::string> parse_line(std::string line, char c);
int string_to_int(std::string s);
bool check_unicity(std::string filename, std::string line);

//Profs
bool check_availability(std::string s_availability);
std::list<int> fill_v_availability(std::string s_availability);
std::map<int, std::list<int> > fill_m_availability(int week, std::list<int> v_availability);


int at(std::list<int> l, int index);
std::string at(std::list<std::string> l, int index);
progSemester at(std::list<progSemester> l , int index);
void editList(std::list<int> &l, int position, int value);
void editList(std::list<progSemester> &l, int index, int id, int nb_weeks, int start_week);
int existing_value(std::list<int> l, int value);

#endif	/* PARSEFILE_H */

