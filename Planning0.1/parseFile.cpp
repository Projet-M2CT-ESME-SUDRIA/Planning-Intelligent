#include <iostream>
#include <fstream>
#include <string>
#include "parseFile.h"
#include "classes.h"

using namespace std;



void get_line(string line, vector<string> &words) {
    
    size_t begin = 0;
    size_t pos=0;
    
    while(line.find('|')) {
        pos=std::string::npos;
        words.push_back(line.substr(begin, pos));
        line[pos]=' ';
        begin+=pos+1;   
    }
    
    for(int i=0 ; i< words.size() ; i++) {
        
        cout << words[i] << endl;
    }
}


/************/
/*  PROFS   */
/************/

void add_prof_to_db(string name, string availability, string given_courses) {
    
    ofstream myStream ("prof.txt");
    
    if(myStream) {
        myStream << name << "|" << availability << "|" << given_courses << endl;
    }
    
    else
        cout << "Impossible d'ouvrir le fichier de données" << endl;
}


void parse_prof(vector<prof> profs) {
    
    ifstream myStream("profs.txt");
    string line;
    
    if (myStream) {
        while(getline(myStream, line)) {
            
        }
    }
    
    
}

/**************/
/*  COURSES   */
/**************/

void add_courses_to_db(string name, string nb_courses, string id_promo) {
    
    ofstream myStream ("courses.txt");
    
    if(myStream) {
        myStream << name << "|" << nb_courses << "|" << id_promo << endl;
    }
    
    else
        cout << "Impossible d'ouvrir le fichier de données" << endl;
}


