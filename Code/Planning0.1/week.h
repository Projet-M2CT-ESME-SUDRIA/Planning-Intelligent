/* 
 * File:   week.h
 * Author: Corentin
 *
 * Created on 4 décembre 2013, 16:01
 */

#ifndef WEEK_H
#define	WEEK_H


#include <vector>
#include <map>
#include <algorithm>
#include "lecture.h"

class week {
    
    //One week per promo and per week in the year
    int _id;
    int _id_promo;
    int _num_week;
    std::vector<lecture> _lectures;

public:

    static int _static_id;
    week();
    week(int id_promo, int num_week);
    int get_id();
    int get_num_week();
    void add_lecture(int index, lecture l);
    bool checkAvailability(int index);
    
};


#endif	/* WEEK_H */

