/* 
 * File:   classes.h
 * Author: djamalmohia
 *
 * Created on 26 novembre 2013, 14:12
 */

#ifndef CLASSES_H
#define    CLASSES_H

#include <vector>
#include <list>
#include <string>
#include <cassert>

using namespace std;

class lecture {
    
    int _id_course;
    int _id_prof;
    int _id_week;
    

public:
        
    static int _id;
    lecture():_id_course(-1),_id_prof(-1){
        _id++;
    }
    
    lecture(int id_course, int id_prof, int id_week):_id_course(id_course),_id_prof(id_prof), _id_week(id_week){
        _id++;
    }  


};

class week {
    int _id;
    int _id_prom;

    vector<lecture> _lectures;

public:

    week() : _id(0), _id_prom(0) {
        _lectures.resize(22);

    }

    week(int id, int id_prom):_id(id),_id_prom(id_prom){

        _lectures.resize(22);
    }
    
    int get_id(){
        return _id;
    }
    
    void add_lecture(int index, lecture l){
        this->_lectures.insert(_lectures.begin()+index,l);
    }


};

class course {
    int _id;
    std::string _name;
    int _nb_lectures;
    
public:
    
    course():_id(-1), _name("unknown"), _nb_lectures(-1){
    }
    
    course(int id, string name, int nb_lectures):_id(id), _name(name), _nb_lectures(nb_lectures){
    }
    
    int get_id(){
        return _id;
    }

};

class prof{
    int _id;
    std::string _name;
    vector<int> _availabiliy;
    vector<int> _given_courses;
    
    prof():_id(-1), _name("unknown"){
        assert(_availabiliy.size()==22);
    }
    
    prof(int id, string name, vector<int> availability, vector<int> given_courses):
    _id(id),_name(name), _availabiliy(availability), _given_courses(given_courses){
        assert(_availabiliy.size()==22);
        sort(_given_courses.begin(),_given_courses.end());
    }
    
    void grant_lecture(course c, week &w, int index){
        
        assert(_availabiliy.at(index));
        this->_availabiliy.at(index)=0;
        
        lecture l(c.get_id(), this->_id, w.get_id());
        w.add_lecture(index,l);
    }
            

};

class promo{
    int _id;
    int _nb_students;
    string _name;
    vector<int> _courses_id;
    vector<int> _weeks_id;
    
    promo():_id(-1), _name("unkonwn"), _nb_students(-1) {
    }
    
    promo(int id, string name, int nb_students, vector<int> courses_id, vector<int> weeks_id):
    _id(id), _name(name), _nb_students(nb_students), _courses_id(courses_id), _weeks_id(weeks_id){
        sort(_courses_id.begin(),_courses_id.end());
        sort(_weeks_id.begin(),_weeks_id.end());
    }
};






#endif    /* CLASSES_H */