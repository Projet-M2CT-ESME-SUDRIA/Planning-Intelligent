#include "school.h"
#include "parseFile.h"
#include <iostream>

using namespace std;

//Fonction permettant trier une liste d'id_courses en fonction de la taille du créneau, et du nombre de semaine
void School::give_courses_semester(list<int> &id_courses, list<progSemester> &prog) {
    
    list<int> id_courses_2;
    list<int> id_courses_4;
    
    split_course_2_4(id_courses, id_courses_2, id_courses_4);
    id_courses_2 = merge_sort(id_courses_2);
    id_courses_4 = merge_sort(id_courses_4);
    id_courses.clear();
    merge_course_2_4(id_courses, id_courses_2, id_courses_4);

    //Répartir les cours sur le semestre
    prog = splitCourses(id_courses);

    //Vérification créneau
    if(!checkProgSemester(prog)) {
        cout << "Prog semestre pas bon" << endl;
        exit(EXIT_FAILURE);
    }
    //else
      //  cout << "Prog semestre OK" << endl;
}

//Fonction permettant de séparer les cours de 2h et de 4h
void School::split_course_2_4(list<int> id_course, list<int> &id_courses_2, list<int> &id_courses_4) {
    for(list<int>::iterator it=id_course.begin() ; it!=id_course.end() ; it++) {
        if (_courses[(*it)].get_lecture_size() == 4)
            id_courses_4.push_back(*it);
        else
            id_courses_2.push_back(*it);
    }
}

//Fonction permettant de regrouper les cours de 2h et de 4h une fois triés
void School::merge_course_2_4(list<int> &id_courses, list<int> id_courses_2, list<int> id_courses_4) {
    for(list<int>::iterator it=id_courses_4.begin() ; it!=id_courses_4.end() ; it++)
        id_courses.push_back(*it);
    for(list<int>::iterator it=id_courses_2.begin() ; it!=id_courses_2.end() ; it++)
        id_courses.push_back(*it);
}

//Fonction pour répartir les cours sur les semaines d'un semestre
list<progSemester> School::splitCourses(list<int> id_courses) {
    
    list<progSemester> prog;
    bool put=false;
    int cmpt = 0;
    
    //On doit initialiser la liste pour des raisons d'accès mémoire
    prog.resize(id_courses.size());
    initProg(prog);
    
    //On parcourt la liste contenant les id des cours du programme
    for(list<int>::iterator it = id_courses.begin() ; it != id_courses.end() ; it++) {
        put = false;
       
        //On parcourt la liste des cours déjà placé pour éventuellement placer le cours à la suite d'un autre
        for (list<progSemester>::iterator it_prog = prog.begin() ; it_prog != prog.end() ; it_prog++) {

            //Si on a déjà placé un cours, son id est différent de -1
            if((*it_prog)._id_course != -1) {
               
                //On regarde si on peut placer le nouveau cours derrière un cours déjà placé
                checkNextCourse((*it_prog), prog, cmpt, (*it));

                //Si on a ajouté le nouveau cours
                if(at(prog, cmpt)._id_course != -1) {
                    put = true;
                    cmpt ++;
                    break;
                }
            }          
        }
        
        //Si on n'a pas pu placer le cours à la suite d'un cours déjà existant, on le place en début de semestre
        if(!put) {
            editList(prog, cmpt, _courses[*it].get_id(), _courses[*it].get_nb_weeks(), 0);
            cmpt ++;
        }
    }
    
    //Affichage (test)
    /*for(list<progSemester>::iterator it = prog.begin() ; it != prog.end() ; it++) {
        cout << (*it)._id_course << "|" << (*it)._nb_weeks << "|" << (*it)._start_week << endl;
    }*/
    
    return prog;
}

//Fonction récursive qui permet de vérifier si on peut placer un cours à la suite d'un ou plusieurs autres cours.
void School::checkNextCourse(progSemester &currentCourse, list<progSemester> &prog, int index, int id_newCourse) {
    
    //Si le cours actuel a un successeur, on rappelle la fonction pour traiter le successeur
    if(currentCourse._next != NULL) {
        checkNextCourse(*(currentCourse._next), prog, index, id_newCourse);
    }
    
    //Si le cours actuel n'a pas de successeur, on regarde si on peut placer le nouveau cours derrière lui
    else if(currentCourse._start_week + currentCourse._nb_weeks + _courses[id_newCourse].get_nb_weeks() <= _nb_week) {
        editList(prog, index, _courses[id_newCourse].get_id(), _courses[id_newCourse].get_nb_weeks(), currentCourse._start_week + currentCourse._nb_weeks);
        
        list<progSemester>::iterator it = prog.begin();
        advance(it, index);
        if(&currentCourse != &(*it))
           currentCourse._next = &(*it);
    }   
}

//Tri par fusion
list<int> School::merge_sort(list<int> &l) {
    
    list<int> left;
    list<int> right;
    list<int> result;
    int size_list = l.size();
    int i;
    
    if (size_list <= 1) {
        return l;
    }
    
    int middle = (size_list / 2);
    
    for (i = 0; i < middle; i++) {        
        left.push_back(at(l,i));
    }
    
    for (i = middle; i < size_list; i++) {
        right.push_back(at(l,i));
    }
    
    left = merge_sort(left);
    right = merge_sort(right);
    result = merge(left, right);
    
    return result;   
}

//Merge par rapport au nombre de semaines
std::list<int> School::merge(std::list<int>& left, std::list<int>& right) {
    
    list<int> result;
    int left_size = left.size();
    int right_size = right.size();
    int left_index = 0, right_index = 0;
    
    while (left_index < left_size && right_index < right_size) {
        if (_courses[at(left,left_index)].get_nb_weeks() > _courses[at(right, right_index)].get_nb_weeks()) {
            result.push_back(at(left,left_index));
            left_index++;
        }
        else if (_courses[at(left,left_index)].get_nb_weeks() == _courses[at(right, right_index)].get_nb_weeks()) {
            if(_courses[at(left,left_index)].get_lecture_size() > _courses[at(right,right_index)].get_lecture_size()) {
                result.push_back(at(left,left_index));
                left_index++;
            }
            else {
                result.push_back(at(right, right_index));
                right_index++;
            }
        }
        else {
            result.push_back(at(right, right_index));
            right_index++;
        }
    }
    
    if (left_index == left_size) {
        while (right_index < right_size) {
            result.push_back(at(right, right_index));
            right_index++;
	}
    } 
    
    else {
	while (left_index < left_size) {
	    result.push_back(at(left,left_index));
	    left_index++;
	}
    }
    
    return result;
}

//"constructeur" de notre structure
void School::setProg(progSemester &buf, Course c, int start_week){
    
    buf._id_course = c.get_id();
    buf._nb_weeks = c.get_nb_weeks();
    buf._start_week = start_week;
    buf._next = NULL;
}

//Initialisation aux valeurs par défaut
void initProg(list<progSemester> &l) {
    int size = l.size();
    int index;
    
    for (index = 0; index < size; index++) {
        editList(l, index, -1, 0, 0);
    }
}