/* 
 * File:   parseFile.h
 * Author: Corentin
 *
 * Created on 3 décembre 2013, 15:06
 */

#ifndef PARSEFILE_H
#define	PARSEFILE_H

#include <vector>

void get_line(std::string line, std::vector<std::string> &words);

void add_prof_to_db(std::string name, std::string availability, std::string courses);
void add_courses_to_db(std::string name, std::string nb_courses, std::string id_promo);

#endif	/* PARSEFILE_H */

