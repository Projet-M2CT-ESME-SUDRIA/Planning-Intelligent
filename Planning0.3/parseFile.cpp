#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "parseFile.h"
#include "dataInitialisation.h"

using namespace std;


/*************/
/*  GENERAL  */
/*************/

//Lit le fichier ligne par ligne
vector<string> read_file(string filename) {
    
    vector<string> line;
    
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
vector<string> parse_line(string line, char c) {
    
    vector<string> words;
    
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
    for(int i=0 ; i<s.size() ; i++) {
        if((int)s[0]>57 || ((int)s[0]<48)) {
            assert("failure");
        }
    }

    stringstream convertToInt(s);
    convertToInt >> number;
    
    if (number < 0)
        assert("failure");
    
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

//Fonction pour remplir le fichier de données des profs
void add_prof_to_db(string name, string s_availability, string given_courses, string nb_weeks) {
    
    string line = name + "|" + s_availability + "|" + given_courses;
    
    if(!check_unicity("prof.txt", line))
        return;
    
    ofstream myStream ("profs.txt", ios::app);
    
    if(myStream) {
        myStream << line << endl;
    }
    else
        cout << "Impossible d'ouvrir le fichier de données" << endl;
}

//Récupère les données sur les profs
void parse_profs(map<int, Prof> &profs, map<int, Course> courses) {
    
    vector<string> line;
    
    line = read_file("profs.txt");
    
    for(int i=0 ; i<line.size() ; i++)
    {
        new_prof(line[i], profs, courses);
    }
    
}

//Création d'un prof à partir d'une ligne du fichier de données
void new_prof(string line, map<int, Prof> &profs, map<int, Course> &courses) {
    
    vector<string> words = parse_line(line, '|');
    
    if(check_availability(words[1]))
        assert("error");
    
    map<int,vector<int> > m_availability;
    vector<int> given_courses;
    
    //Création de l'ensemble des disponibilités du profs
    vector<int> temp = fill_v_availability(words[1]);
    if (!temp.empty())
    {
        for (int i = 0; i < string_to_int(words[3]) ; i++) {
            m_availability[i] = temp;
        }
        
    
        string s = words[2];
        vector<string> name = parse_line(s, ',');
        given_courses = retrieve_courses(name, courses);
    
        Prof p(words[0],m_availability, given_courses);
        
        profs.insert(pair<int, Prof>(p.get_id(), p));
        
    }
    
}

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
         for(int i=0 ; i<s_availability.size() ; i++)
                if(s_availability.at(i) != '0' && s_availability.at(i) != '1')
                {
                        a = false;
                        break;
                }
     
    return a;
}

//Construit le vector availability
vector<int> fill_v_availability(string s_availability) {
    
    vector<int> v_availability;
    
    if(!check_availability(s_availability))
    {
        cout << "erreur" << endl;
        v_availability.clear();
    }
    else
    {
        for(int i=0 ; i<s_availability.size() ; i++)
            if(s_availability.at(i) == '0')
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
void add_course_to_db(string name, string nb_courses, string id_promo) {
    
    string line = name + "|" + nb_courses + "|" + id_promo;
    
    if(!check_unicity("courses.txt", line))
        return;
    
    ofstream myStream ("courses.txt", ios::app);
    
    if(myStream)
        myStream << line << endl;
    else
        cout << "Impossible d'ouvrir le fichier de données" << endl;
}

//Récupère les données sur les matières
void parse_courses(map<int, Course> &courses) {
    
    vector<string> line;
    
    line = read_file("courses.txt");
    for(int i=0 ; i<line.size() ; i++) {
        new_course(line[i], courses);
    }
    
}

//Création d'une matière à partir d'une ligne du fichier de données
void new_course(string line, map<int, Course> &courses) {
    
    vector<string> words;
    words = parse_line(line, '|');
    Course c(string_to_int(words[0]), words[1], string_to_int(words[2]));
    courses.insert(pair<int, Course>(c.get_id(), c));
}

//Construit la map de matières d'un prof
vector<int> retrieve_courses (vector<string> name, map<int, Course> &courses) {
    
    int i,j;
    vector<int> given_courses;
    
    for(i=0 ; i<name.size() ; i++) {
        for(j=0 ; j<courses.size() ; j++) {
            if(name[i].compare(courses[j].get_name()) == 0) {
                given_courses.push_back(courses[j].get_id());
            }
        }
    }
    
    if(given_courses.size() != name.size())
        assert("failure");
    
    return given_courses;
}

/**********/
/* Classe */
/**********/

//Fonction pour remplir le fichier de données des promotions
void add_promo_to_db(string id_promo, string name, string nb_students, string courses, string nb_weeks) {
    
    string line = id_promo + "|" + name + "|" + nb_students + "|" + courses + "|" + nb_weeks;
    
    if(!check_unicity("promos.txt", line))
        return;
    
    ofstream myStream ("promos.txt", ios::app);
    
    if(myStream)
        myStream << line << endl;
    else
        cout << "Impossible d'ouvrir le fichier de données" << endl;
}

//Récupère les données sur les promos
void parse_promo(map<int, Promo> &promos, map<int, Course> &courses) {
    
    vector<string> line;
    
    line = read_file("promos.txt");
    
    for(int i=0 ; i<line.size() ; i++) {
        //promo.push_back(new_promo(line[i], courses));
        new_promo(line[i], promos, courses);
    }
    
}

//Création d'une matière à partir d'une ligne du fichier de données
void new_promo(string line, map<int, Promo> &promos, map<int, Course> &courses) {
    
    vector<string> words;
    vector<int> course_followed;
    int nb_weeks = 0;
    int id_promo = -1;
    int i;
    
    words = parse_line(line, '|');
    
    //Méthode pour pouvoir récupérer les cours suivis
    string s = words[3];
    vector<string> name = parse_line(s, ',');
    course_followed = retrieve_courses(name, courses);
    
    Promo p(string_to_int(words[0]), words[1], string_to_int(words[2]), course_followed);
    
    //Méthode pour créer les semaines de la promo
    nb_weeks = string_to_int(words[4]);
    id_promo = p.get_id();
    for(i = 0 ; i < nb_weeks ; i++) {
        Week w(id_promo, i);
        p.add_week(w);
    }
    
    promos.insert(pair<int, Promo>(p.get_id(), p));
}

void add_prof_to_course(Prof p, map<int,Course> &c){
    
    int s=p.get_given_courses().size();
    int id_c = 0;
    
    for(int i=0 ; i<s ; i++) {
        id_c = p.get_id_course(i);
        c.at(id_c).add_prof(p.get_id());
    }
}