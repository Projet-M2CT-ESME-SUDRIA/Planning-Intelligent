/* 
 * File:   lecture.h
 * Author: Corentin
 *
 * Created on 4 décembre 2013, 16:00
 */

#ifndef LECTURE_H
#define	LECTURE_H

#include <list>
#include <map>
#include <algorithm>

class Lecture {
    
    int _id;
    int _id_course;
    int _id_prof;
    int _id_week;

public:
        
    //Initialisation
    static int _static_id;
    Lecture();
    Lecture(int id_course, int id_prof, int id_week);
    
    //Getter
    int get_id_course();
    int get_id_prof();
    
};


#endif	/* LECTURE_H */

