#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include "parseFile.h"

using namespace std;


/*************/
/*  GENERAL  */
/*************/

//Lit le fichier ligne par ligne
list<string> read_file(string filename) {
    
    list<string> line;
    
    ifstream myStream(filename.c_str());
    string s;
    
    if (myStream) {
        while(getline(myStream, s)) {
            line.push_back(s);
        }
    }
    
    return line;
}

//Reçoit les lignes et en sépare les mots.
list<string> parse_line(string line, char c) {
    
    list<string> words;
    
    size_t begin = 0;
    size_t pos=0;
    string s;
    
    while(pos != std::string::npos) {
        pos=line.find(c);
        s=line.substr(begin, pos);
        words.push_back(s);
        line.erase(0,pos+1);  
    }
    
    return words;
}

//Convertit un string en int
int string_to_int(string s) {
    int number=0;

    //On compare au code ascii pour vérifier qu'il s'agit bien d'un chiffre
    for(string::iterator it=s.begin() ; it!=s.end() ; it++) {
        if((int)s[0]>57 || ((int)s[0]<48)) {
            exit(EXIT_FAILURE);
        }
    }

    stringstream convertToInt(s);
    convertToInt >> number;
    
    if (number < 0)
        exit(EXIT_FAILURE);
    
    return number;
}

//Vérifie l'existence d'une line dans un fichier
bool check_unicity(string filename, string line) {
    
    ifstream myStream(filename.c_str());
    string l;
    
    if(myStream) {
        while(getline(myStream,l)) {
            if(line == l)
                return false;
        }
    }
    else
        cout << "Impossible d'ouvrir le fichier de donnees";
    
    return true;
}

/************/
/*  PROFS   */
/************/

//Vérifie si availability est bien conforme
// /!\ modifier la donnée si le prof existe
bool check_availability(string s_availability) {
    
    bool a = true;
    
    //Availability doit faire 11 caractères
    if(s_availability.size() != 22)
    {
        cout << "taille  " << s_availability.size() << endl;
        a = false;
    }
    
    //Availability n'est composée que de 0 ou de 1 
    if (a)
          for(string::iterator it=s_availability.begin() ; it!=s_availability.end() ; it++)
                if(*it != '0' && *it != '1')
                {
                        a = false;
                        break;
                }
     
    return a;
}

//Construit la liste availability
list<int> fill_v_availability(string s_availability) {
    
    list<int> v_availability;
    
    if(!check_availability(s_availability))
    {
        cout << "erreur" << endl;
        v_availability.clear();
    }
    else
    {
        for(string::iterator it=s_availability.begin() ; it!=s_availability.end()  ; it++)
            if(*it == '0')
                v_availability.push_back(0);
            else
                v_availability.push_back(1);
    }
    
    return v_availability;
}


//Fonctions pour parcourir les listes
int at(list<int> l, int index) {
    list<int>::iterator it = l.begin();
    advance(it, index);
    return *it;
}

string at(list<string> l, int index) {
    list<string>::iterator it = l.begin();
    advance(it, index);
    return *it;
}

progSemester at(list<progSemester> l , int index) {
    list<progSemester>::iterator it = l.begin();
    advance(it, index);
    return *it;
}

void editList(list<int> &l, int index, int value) {
    
    list<int>::iterator it = l.begin();
    
    advance(it,index);
    
    *it = value;
}

void editList(list<progSemester> &l, int index, int id, int nb_weeks, int start_week) {
    
    list<progSemester>::iterator it = l.begin();
    
    advance(it,index);
    
    (*it)._id_course = id;
    (*it)._nb_weeks = nb_weeks;
    (*it)._next = NULL;
    (*it)._start_week = start_week;
}

//Vérifie si un nombre existe déjà dans une liste
int existing_value(list<int> l, int value){
    
    for(list<int>::iterator it = l.begin() ; it!=l.end() ; it++){
        if(*it == value)
            return 1;
    }
    
    return 0;
}