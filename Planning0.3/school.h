/* 
 * File:   school.h
 * Author: Corentin
 *
 * Created on 22 janvier 2014, 13:15
 */

#ifndef SCHOOL_H
#define	SCHOOL_H

#include "course.h"
#include "prof.h"
#include "promo.h"
#include "routine.h"

typedef struct s_progSemester progSemester;
struct s_progSemester{
    
    int _id_course;
    int _start_week;
    int _nb_weeks;
    progSemester *_next;
    
};

void initProg(std::list<progSemester> &l);

class School {
    
private:
    std::map<int, Course> _courses;
    std::map<int, Prof> _profs;
    std::map<int, Promo> _promos;
    std::list<int> _list_promos;
    int _nb_week;
    
public:
    School(int nb_week);
    
    //Initialisation de la classe School
    void parse_profs();
    void new_prof(std::string line);
    void parse_courses();
    void new_course(std::string line, int nb_week);
    void parse_promos();
    void new_promo(std::string line);
    void fill_list_promo();
    
    //Affichage
    void display();
    
    //Méthodes relatives au prétraitement
    int nb_class_promo(int id_promo);
    int nb_availabilities_course(int id_course);
    void divideCourses();
    
    //Fonctions de vérifications
    int nb_prof_ok();
    int nb_lectures_ok();
    bool checkProgSemester(std::list<progSemester> l);
    
    //Routine 1 : répartition des cours sur le semestre
    void split_course_2_4(std::list<int>id_course, std::list<int> &id_courses_2, std::list<int> &id_courses_4);
    void merge_course_2_4(std::list<int> &id_courses, std::list<int> id_courses_2, std::list<int> id_courses_4);
    std::list<progSemester> splitCourses(std::list<int> id_courses);
    void checkNextCourse(progSemester &currentCourse, std::list<progSemester> &prog, int index, int id_newCourse);
    void setProg(progSemester &buf, Course c, int start_week);
    std::list<int> merge_sort(std::list<int> &l);
    std::list<int> merge(std::list<int> &left, std::list<int> &right);
    std::list<int> retrieve_courses (std::list<std::string> name);
    void give_courses_semester(std::list<int> &id_courses, std::list<progSemester> &prog);
    
    //Routine 2 : répartitions des cours dans les semaines
    void give_courses_promo(int id_year, std::list<progSemester> prog);
    std::list<int> getClassPromo(int id_year);
    std::list<progSemester> getProgWeek(std::list<progSemester> prog, int num_week);
    std::list<int> getProfWeek(std::list<progSemester> prog_week);
    bool prof_in_list(std::list<int>list_id_prof_week, int id_prof);
    void addCoursePromo(std::list<int> list_id_promo, std::list<progSemester> prog_week, std::list<int> list_id_prof, int num_week);
    void best_connection(std::list<progSemester> prog_week, std::list<int> id_profs, std::list<int> id_promos, int num_week, int &prof_index, int &promo_index);
    int nb_connections(int id_prof, int id_promo, int num_week, std::list<progSemester> prog_week);
    void addCourse(std::list<progSemester> prog_week, int id_prof, int id_promo, int num_week);
    bool courseIsInWeek(std::list<progSemester> prog_week, int id_course);
    void grantLecture(int id_prof, int id_promo, int id_course, int num_week);
    void previousWeek(Promo &p, std::list<progSemester> prog_week, int num_week);
};

#endif	/* SCHOOL_H */

