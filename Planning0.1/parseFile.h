/* 
 * File:   parseFile.h
 * Author: Corentin
 *
 * Created on 3 décembre 2013, 15:06
 */

#ifndef PARSEFILE_H
#define	PARSEFILE_H

#include <vector>
#include "classes.h"

//General
void read_file(std::string filename, std::vector<std::string> &line);
void parse_line(std::string line, std::vector<std::string> &words);
int string_to_int(std::string s);

//Profs
void add_prof_to_db(std::string name, std::string s_availability, std::string courses);
void parse_prof(std::vector<prof> &profs);
prof new_prof(std::string line);
bool check_availability(std::string s_availability);
std::vector<int> fill_v_availability(std::string s_availability);
std::map<int, std::vector<int> > fill_m_availability(int week, std::vector<int> v_availability);

//Matières
void add_courses_to_db(std::string name, std::string nb_courses, std::string id_promo);
void parse_courses(std::vector<course> &courses);
course new_course(std::string line);

#endif	/* PARSEFILE_H */

