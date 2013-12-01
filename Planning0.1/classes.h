/* 
 * File:   classes.h
 * Author: elysiunk
 *
 * Created on 28 novembre 2013, 17:04
 */

#ifndef CLASSES_H
#define	CLASSES_H

#include <vector>
#include <list>
#include <string>
#include <cassert>
#include <map>



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

class week {
    
    //One week per promo and per week in the year
    int _id;
    int _id_promo;
    int _num_week;
    std::vector<lecture> _lectures;

public:

    week();
    week(int id, int id_promo, int num_week);
    int get_id();
    int get_num_week();
    void add_lecture(int index, lecture l);
    bool checkAvailability(int index);
    
};

class course {
    
    int _id;
    std::string _name;
    int _nb_lectures;
    
public:
    
    course();
    course(int id, std::string name, int nb_lectures);
    int get_id();
    std::string get_name();

};

class prof{
    
    int _id;
    std::string _name;
    std::map<int, std::vector<int> > _availabiliy;
    std::map<int, course> _given_courses;
  
public:
    
    prof();
    prof(int id, std::string name);
    void add_availability(int nb_weeks, std::vector <int> availability);
    std::vector<int> get_availability(int num_week);
    void set_availability(int num_week, int index);
    void add_given_course(course c);
    //index = creneaux
    void grant_lecture(course c, week &w, int index);

};

class promo{
    
    int _id;
    int _nb_students;
    std::string _name;
    std::map<int, course> _courses;
    std::map<int, week> _weeks;
   
public:
    
    promo();
    promo(int id, std::string name, int nb_students);
    void add_course(course c);
    void add_week(week w);
    course get_course(int id);
    
};

#endif	/* CLASSES_H */
