#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "parseFile.h"
#include "classes.h"

using namespace std;


/*************/
/*  GENERAL  */
/*************/

//Lit le fichier ligne par ligne
void read_file(string filename, vector<string> &line) {
    
    ifstream myStream(filename.c_str());
    string s;
    
    if (myStream) {
        while(getline(myStream, s)) {
            line.push_back(s);
        }
    }
}

//Reçoit les lignes et en sépare les mots.
void parse_line(string line, vector<string> &words) {
    
    size_t begin = 0;
    size_t pos=0;
    string s;
    
    while(pos != std::string::npos) {
        pos=line.find('|');
        s=line.substr(begin, pos);
        words.push_back(s);
        line.erase(0,pos+1);  
    }
}

int string_to_int(string s) {
    int number=0;

    //On compare au code ascii pour vérifier qu'il s'agit bien d'un chiffre
    for(int i=0 ; i<s.size() ; i++) {
        if((int)s[0]>57 || ((int)s[0]<48)) {
            assert("ERROR");
        }
    }

    stringstream convertToInt(s);
    convertToInt >> number;
    
    if (number < 0)
        assert("ERROR");
    
    return number;
}



/************/
/*  PROFS   */
/************/

//Fonction pour remplir le fichier de données des profs
void add_prof_to_db(string name, string s_availability, string given_courses) {
    
    ofstream myStream ("prof.txt", ios::app);
    
    if(myStream) {
        myStream << name << "|" << s_availability << "|" << given_courses << endl;
        myStream << name << "|" << s_availability << "|" << given_courses << endl;
    }
    
    else
        cout << "Impossible d'ouvrir le fichier de données" << endl;
}

//Récupère les données sur les profs
void parse_prof(vector<prof> &profs) {
    
    vector<string> line;
    
    read_file("profs.txt", line);
    
    for(int i=0 ; i<line.size() ; i++) {
        profs.push_back(new_prof(line[i]));
    }
    
}

//Création d'un prof à partir d'une ligne du fichier de données
prof new_prof(string line) {
    
    vector<string> words;
    
    parse_line(line, words);
    
    if(!check_availability(words[1]))
        assert("ERROR");
    
    map<int, vector<int> > m_availability;
    
    m_availability[0] = fill_v_availability(words[1]);
    
    prof p;
    
    return p;
}

//Vérifie si availability est bien conforme
bool check_availability(string s_availability) {
    
    //Availability doit faire 11 caractères
    if(s_availability.size() != 11)
        return false;
    
    //Availability n'est composée que de 0 ou de 1 
    for(int i=0 ; i<s_availability.size() ; i++) {
        if(s_availability.at(i) != 0 && s_availability.at(i) != 1)
            return false;
    }
    
    return true;
}

//Construit le vector availability
vector<int> fill_v_availability(string s_availability) {
    
    vector<int> v_availability;;
    
    for(int i=0 ; i<s_availability.size() ; i++){
        if(s_availability.at(i) == 0)
            v_availability.push_back(0);
        else
            v_availability.push_back(1);
    }
    
    return v_availability;
}


/**************/
/*  COURSES   */
/**************/

//Fonction pour remplir le fichier de données des matières
void add_courses_to_db(string name, string nb_courses, string id_promo) {
    
    ofstream myStream ("courses.txt");
    
    if(myStream) {
        myStream << name << "|" << nb_courses << "|" << id_promo << endl;
    }
    
    else
        cout << "Impossible d'ouvrir le fichier de données" << endl;
}

//Récupère les données sur les matières
void parse_courses(vector<course> &courses) {
    
    vector<string> line;
    
    read_file("courses.txt", line);
    
    for(int i=0 ; i<line.size() ; i++) {
        courses.push_back(new_course(line[i]));
    }
    
}

//Création d'une matière à partir d'une ligne du fichier de données
course new_course(string line) {
    
    vector<string> words;
    
    parse_line(line, words);
    
    course c(string_to_int(words[0]), words[1], string_to_int(words[2]));
    
    return c;
}
