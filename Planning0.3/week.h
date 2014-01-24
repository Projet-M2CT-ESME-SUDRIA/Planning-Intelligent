/* 
 * File:   week.h
 * Author: Corentin
 *
 * Created on 4 décembre 2013, 16:01
 */

#ifndef WEEK_H
#define	WEEK_H


#include <list>
#include <map>
#include <algorithm>
#include "lecture.h"

class Week {
    
    //One week per promo and per week in the year
    int _id;
    int _id_promo;
    int _num_week;
    std::list<Lecture> _lectures;

public:

    //Initialisation
    static int _static_id;
    Week();
    Week(int id_promo, int num_week);
    
    //Getter
    int get_id();
    int get_num_week();
    bool checkAvailability(int index);
    Lecture get_lecture(int index);
    bool has_lecture(int id_course);
    
    //Setter
    void add_lecture(int index, Lecture l);

};


#endif	/* WEEK_H */

