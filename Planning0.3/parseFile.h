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

//General
std::vector<std::string> read_file(std::string filename);
std::vector<std::string> parse_line(std::string line, char c);
int string_to_int(std::string s);
bool check_unicity(std::string filename, std::string line);

//Profs
void add_prof_to_db(std::string name, std::string s_availability, std::string courses, std::string nb_weeks);
void parse_profs(std::map<int,Prof> &profs, std::map<int,Course> courses);
void new_prof(std::string line, std::map<int,Prof> &profs, std::map<int, Course> &courses);
bool check_availability(std::string s_availability);
std::vector<int> fill_v_availability(std::string s_availability);
std::map<int, std::vector<int> > fill_m_availability(int week, std::vector<int> v_availability);

//Matières
void add_course_to_db(std::string name, std::string nb_courses, std::string id_promo);
void parse_courses(std::map<int, Course> &courses);
void new_course(std::string line, std::map<int, Course> &courses);
std::vector<int> retrieve_courses (std::vector<std::string> name, std::map<int, Course> &courses);

//Promo
void add_promo_to_db(std::string id_promo, std::string name, std::string nb_students, std::string courses, std::string nb_weeks);
void parse_promo(std::map<int,Promo> &promo, std::map<int,Course> &courses);
void new_promo(std::string line, std::map<int,Promo> &promo, std::map<int, Course> &courses);

void add_prof_to_course(Prof p, std::map<int,Course> &c);


#endif	/* PARSEFILE_H */

