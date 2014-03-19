
/* 
 * File:   course.h
 * Author: Corentin
 *
 * Created on 4 décembre 2013, 15:57
 */

#ifndef COURSE_H
#define COURSE_H

#include <list>
#include <map>
#include <algorithm>
#include <string>

class Course {
    
private:
    
    int _id;
    int _id_promo;
    std::string _name;
    int _nb_hours;
    int _lecture_size;
    int _id_previous_course;
    std::list<int> _prog_semester;
    
public:
    
    //Initialisation
    static int _static_id;
    Course();
    Course(int id_promo, std::string name, int nb_hours);
    void initializeList(int nb_week);
    
    //Getter
    int get_id();
    int get_id_promo();
    std::string get_name();
    int get_nb_hours();
    int get_nb_weeks();
    int get_lecture_size();
    
    void setLectureSize(int nb_weeks);
    
    //Affichage
    void list_courses();

};


#endif  /* COURSE_H */

