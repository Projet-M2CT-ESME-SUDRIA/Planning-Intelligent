/* 
 * File:   lecture.h
 * Author: Corentin
 *
 * Created on 4 décembre 2013, 16:00
 */

#ifndef LECTURE_H
#define	LECTURE_H

#include <vector>
#include <map>
#include <algorithm>

class lecture {
    
    int _id_course;
    int _id_prof;
    int _id_week;

public:
        
    static int _id;
    lecture();
    lecture(int id_course, int id_prof, int id_week);
    int get_id_course();
    
};


#endif	/* LECTURE_H */

