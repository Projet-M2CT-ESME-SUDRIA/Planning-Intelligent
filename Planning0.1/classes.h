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
    //One week per promo and per week in the year
    int _id;
    int _id_promo;

    vector<lecture> _lectures;

public:

    week() : _id(0), _id_promo(0) {
        _lectures.resize(22);

    }

    week(int id, int id_promo):_id(id),_id_promo(id_promo){

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
    string _name;
    int _nb_lectures;
    
public:
    
    course():_id(-1), _name("unknown"), _nb_lectures(-1){
    }
    
    course(int id, string name, int nb_lectures):_id(id), _name(name), _nb_lectures(nb_lectures){
    }
    
    int get_id(){
        return _id;
    }
    
    string get_name(){
        return _name;
    }

};

class prof{
    int _id;
    std::string _name;
    vector<int> _availabiliy;
    map<int, course> _given_courses;
  
public:
    prof():_id(-1), _name("unknown"){
        assert(_availabiliy.size()==22);
    }
    
    prof(int id, string name, vector<int> availability):
    _id(id),_name(name), _availabiliy(availability){
        assert(_availabiliy.size()==22);
    }
    
    //index = cr�neaux
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
    std::map<int, course> _courses;
    std::map<int, week> _weeks;
   
public:
    promo():_id(-1), _name("unkonwn"), _nb_students(-1) {
    }
    
    promo(int id, string name, int nb_students):
    _id(id), _name(name), _nb_students(nb_students){
    }
    
    void add_course(course c){
        _courses[c.get_id()] = c;
    }
    
    course get_course(int id){
        return _courses[id];
    }
    
    
};


#endif	/* CLASSES_H */

