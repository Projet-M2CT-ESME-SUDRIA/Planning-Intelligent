/* 
 * File:   main.cpp
 * Author: elysiunk
 *
 * Created on 28 novembre 2013, 17:04
 */

#include <cstdlib>
#include <iostream>
#include "parseFile.h"
#include "dataInitialisation.h"
#include "routine.h"


using namespace std;

void test3() {
    
    bool exit=false;
    int choice=0;
    vector<course> courses;
    vector<prof> profs;
    vector<promo> promos;
    
    while(!exit) {
        
        cout << "1. ajouter un cours" << endl;
        cout << "2. ajouter un prof" << endl;
        cout << "3. ajouter une promo" << endl;
        cout << "4. recuperer la liste des matieres" << endl;
        cout << "5. recuperer la liste des profs" << endl;
        cout << "6. recuperer la liste des classes" << endl;
        cout << "7. test routine" << endl;
        cout << "0. quitter" << endl;
        cin >> choice;
        
        switch(choice) {
            case 1:
                add_course();
                break;
                
            case 2:
                add_prof();
                break;
                
            case 3:
                add_promo();
                break;
                
            case 4:
                get_courses(courses);
                break;
                
            case 5:
                get_profs(profs, courses);
                break;
                
            case 6:
                get_promos(promos, courses);
                break;
                
            case 7:
                rout3(profs,promos);
                break;
                
            case 0:
                exit = true;
                break;
                
            default:
                exit=true;
                break;
        }
    }
    
    return;
                
}

int main(int argc, char* argv[]) {
   test3(); 
   
   return 0;
}