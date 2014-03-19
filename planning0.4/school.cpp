/* 
 * File:   school.cpp
 * Author: Corentin
 *
 * Created on 22 janvier 2014, 13:16
 */

#include "school.h"
#include "parseFile.h"
#include <iostream>
#include <fstream>

#define MAX_ITERATION 100

using namespace std;


School::School(int nb_week){
    
    _nb_week=nb_week;
    
    parse_courses();
    parse_profs();
    parse_promos();
    fill_list_promo();
    
    int size = _courses.size();
    
    //On détermine si le cours est sur 4h ou 2h en fonction du nombre de semaine du semestre
    for(int i=0 ; i<size ; i++) {
        _courses[i].setLectureSize(_nb_week);
    }
}

//Va récupérer ligne par ligne les données contenues dans le fichier et appelle la fonction qui créé les profs
void School::parse_profs() {
    
    list<string> line;
    
    line = read_file("profs.txt");
    for(list<string>::iterator it=line.begin() ; it!=line.end() ; it++){
        new_prof(*it);
    }  
}

//Création d'un prof à partir d'une ligne du fichier de données
void School::new_prof(string line) {
    
    //Sépare les différents paramètres d'une ligne de données et les stock dans une liste de mots
    list<string> words = parse_line(line, '|');
    
    string availabilities = at(words,1);
    
    //On vérifie que les dispo du prof sont bien conformes
    if(!check_availability(availabilities)) {
        cout << "probleme de disponibilites prof" << endl;
        exit(EXIT_FAILURE);
    }
    
    map<int,list<int> > availability;
    list<int> given_courses;
    
    //Création de l'ensemble des disponibilités du profs
    list<int> temp = fill_v_availability(availabilities);
      
    //On initialise toutes les disponibilités du prof sur l'ensemble du semestre
    for (int i=0 ; i<_nb_week ; i++) {
        availability.insert(pair<int, list<int> > (i, temp));
    }

    string line_courses = at(words,2);
    list<string> name = parse_line(line_courses, ',');
    given_courses = retrieve_courses(name);

    Prof p(at(words,0),availability, given_courses);

    _profs.insert(pair<int, Prof> (p.get_id(), p));
}

//Va récupérer ligne par ligne les données contenues dans le fichier et appelle la fonction qui créé les cours
void School::parse_courses() {
    
    list<string> line;
    
    line = read_file("courses.txt");
    for(list<string>::iterator it=line.begin() ; it!=line.end() ; it++) {
        new_course(*it, _nb_week);
    }
}

//Création d'une matière à partir d'une ligne du fichier de données
void School::new_course(string line, int nb_week) {
    
    //Sépare les différents paramètres d'une ligne de données et les stock dans une liste de mots
    list<string> words;
    words = parse_line(line, '|');
    
    int nb_hours = string_to_int(at(words,2));
    
    //On vérifie que le cours n'a pas un nombre d'heures supérieur à l'équivalent d'un cours de 4h chaque semaine du semestre
    if(nb_hours > 4*nb_week) {
        cout << "trop d'heures pour le cours : " << at(words,1) << endl;
        exit(EXIT_FAILURE);
    }
    
    Course c(string_to_int(at(words,0)), at(words,1), nb_hours);
    c.initializeList(_nb_week);
    int i = c.get_id();
    _courses.insert(pair<int, Course> (c.get_id(), c));
}

//Va récupérer ligne par ligne les données contenues dans le fichier et appelle la fonction qui créé les promos
void School::parse_promos() {
    
    list<string> line;
    
    line = read_file("promos.txt");
    
    for(list<string>::iterator it=line.begin(); it!=line.end() ; it++) {
        new_promo(*it);
    }   
}

//Création d'une matière à partir d'une ligne du fichier de données
void School::new_promo(string line) {
    
    //Sépare les différents paramètres d'une ligne de données et les stock dans une liste de mots
    list<string> words;
    
    list<int> course_followed;
    int id_promo = -1;
    int i;
    
    words = parse_line(line, '|');
    
    //Méthode pour pouvoir récupérer les cours suivis
    string s = at(words,3);
    list<string> name = parse_line(s, ',');
    course_followed = retrieve_courses(name);
    
    Promo p(string_to_int(at(words,0)), at(words,1), string_to_int(at(words,2)), course_followed);
    
    //Méthode pour créer les semaines de la promo
    id_promo = p.get_id();
    for(i = 0 ; i < _nb_week ; i++) {
        Week w(id_promo, i);
        p.add_week(w);
    }
    
    _promos.insert(pair<int, Promo>(p.get_id(), p));
}

//Récupère les id des promotions de l'école et les trie par ordre croissant
void School::fill_list_promo(){
    
    for(map<int, Course>::iterator it = _courses.begin() ; it != _courses.end() ; it++) {
        if(!existing_value(_list_promos, (*it).second.get_id_promo()))
            _list_promos.push_back((*it).second.get_id_promo());
    }
    
    _list_promos.sort();
}

void School::reInitialize() {
    
    _profs.clear();
    Prof::_static_id=0;
    parse_profs();

    _promos.clear();
    Promo::_static_id=0;
    parse_promos();

    _course_not_schedule.clear();
}

//Affichage du contenu des map
void School::display(){
    
    for(map<int, Prof>::iterator it=_profs.begin() ; it!=_profs.end() ; it++) {
        (*it).second.list_profs();
    }
    
    for(map<int, Course>::iterator it=_courses.begin() ; it!=_courses.end() ; it++) {
        (*it).second.list_courses();
    }
    
    for(map<int, Promo>::iterator it=_promos.begin() ; it!=_promos.end() ; it++) {
        (*it).second.list_promos();
    }
}

//Affichage de l'emploi du temps de toutes les classes
void School::display_schedule_promos() {
    
    int i, j;
    
    if(_course_not_schedule.size() > 0) {
        cout << endl << "LES COURS NON PLACÉES" << endl;
        for(list<courseNotSchedule>::iterator it=_course_not_schedule.begin() ; it!=_course_not_schedule.end() ; it++) {
            cout << "Cours : " << (*it)._id_course << " Prof : " << (*it)._id_prof;
            cout << " Promo : " << (*it)._id_promo << " Week : " << (*it)._num_week << endl;
        }
    }
    cout << endl;
    
    for(map<int, Promo>::iterator it=_promos.begin() ; it!=_promos.end() ; it++) {
        cout << "Emploi du temps  : " << (*it).second.get_name() << endl;
                
        for(i=0 ; i<14 ; i++) {
            for(int j=0 ; j<22 ; j++) {
                cout << (*it).second.get_week(i).get_lecture(j).get_id_prof() << "  ";
            }
            cout << endl;
        }
        cout << endl;
        
        for(i=0 ; i<14 ; i++) {
            for(int j=0 ; j<22 ; j++) {
                cout << (*it).second.get_week(i).get_lecture(j).get_id_course() << "  ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    for(int p= 0 ; p!=_profs.size() ; p++){
        cout <<"Prof " << _profs[p].get_id() << " : " << endl;
        for (int j = 0; j < 14; j++) {
            for (int k = 0; k < 22; k++) {
                cout << _profs[p].is_available(j,k);
            }
            cout <<endl;
        }
        cout << endl << endl;
    }
    
}

//Affichage de l'emploi du temps d'une promotion
void School::display_schedule_one_promo(int id_promo) {
    int i,j;
    cout << endl << "Emploi du temps de la " << _promos[id_promo].get_name() << endl;
    for(i=0 ; i<14 ; i++) {
        for(int j=0 ; j<22 ; j++) {
            cout << _promos[id_promo].get_week(i).get_lecture(j).get_id_course() << "  ";
        }
        cout << endl;
    }
}

//Affichage de l'emploi du temps de toutes les classes dans des fichiers
void School::write_schedule_file() {
    
    int i, j;
    string filename;

    for(map<int, Promo>::iterator it=_promos.begin() ; it!=_promos.end() ; it++) {
        filename = "EDT/" + (*it).second.get_name() + ".txt";
        
        ofstream newFile(filename.c_str());
        
        if(newFile) {
        
            for(i=0 ; i<14 ; i++) {
                for(int j=0 ; j<22 ; j++) {
                    newFile << (*it).second.get_week(i).get_lecture(j).get_id_prof() << ",";
                    newFile << (*it).second.get_week(i).get_lecture(j).get_id_course();
                    if(j<21)
                        newFile << "|";
                }
                if(i<13)
                    newFile << endl;
            }
        }
        
        else
            cout << "Probleme dans la creation du fichier" << endl;
    }
}

//Retourne le nombre de classe dans une promo à partir de son id
int School::nb_class_promo(int id_promo){
    
    int nb=0;
    
    for (map<int, Promo>::iterator it =_promos.begin() ; it != _promos.end() ; it++){
        if((*it).second.get_id_promo() == id_promo)
            nb++;
    }
    
    return nb;
}

//Retourne le nombre de dispo des profs pour un cours donné
int School::nb_availabilities_course(int id_course){
    
    int nb=0;
    
    for(map<int, Prof>::iterator it = _profs.begin() ; it != _profs.end() ; it++) {
        if((*it).second.has_course(id_course))
            nb+= (*it).second.get_nb_availability(0);
    }
    
    return nb;
}

//Construit la map de matières d'un prof
list<int> School::retrieve_courses (list<string> name) {
    
    list<int> given_courses;
    
    for(list<string>::iterator it_name=name.begin(); it_name!=name.end() ; it_name++) {
        for(map<int, Course>::iterator it_course=_courses.begin(); it_course!=_courses.end() ; it_course++) {
            if((*it_name).compare((*it_course).second.get_name()) == 0) {
                given_courses.push_back((*it_course).second.get_id());
                break;
            }
        }
    }
    
    if(given_courses.size() != name.size()) {
        
        cout << "le nombre de cours ne correspond pas" << endl;
        exit(EXIT_FAILURE);
    }
    
    return given_courses;
}

//Fonction principale de la routine permettant de répartir les cours sur l'ensemble du semestre
void School::divideCourses(){
    
    list<int> id_courses;
    list<progSemester> prog;
    int nbFail=2000;
    int nbIterations=0;
    int course_add;

    do {
        reInitialize();
        nbIterations++;

        cout << "Iteration " << nbIterations << " | ";

        //Parcourt la liste des promotions (B1,B2...) de l'école, pour récupérer le programme de l'année. 
        for(list<int>::iterator it_list = _list_promos.begin() ; it_list!=_list_promos.end() ; it_list++){
            for(map<int, Promo>::iterator it_promo = _promos.begin() ; it_promo != _promos.end() ; it_promo++){
                if(*it_list == (*it_promo).second.get_id_promo()) {
                    id_courses = (*it_promo).second.get_id_courses();
                    break;
                }
            }
        
            //Routine 1 : répartition des cours d'une promotion sur le semestre
            give_courses_semester(id_courses, prog);
        
            //Routine 2 : répartition des cours de l'ensemble des classes d'une promotion, semaine par semaine
            course_add = give_courses_promo(*it_list, prog);

        }

        if(_course_not_schedule.size() < nbFail)
            nbFail = _course_not_schedule.size();
        
        cout << _course_not_schedule.size() << " erreurs" << endl;
    } while(_course_not_schedule.size() != 0 && nbIterations < MAX_ITERATION);

    cout << "Meilleur : " << nbFail << " erreurs, en " << nbIterations << " iterations" << endl;
}