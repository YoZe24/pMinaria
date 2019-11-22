#ifndef GESTIONUSER_H
#define GESTIONUSER_H

#include "User.h"
#include <vector>
#include <string>
#include <sstream>

#include <iostream>
#include <fstream>

using namespace std;

//Classe qui possède un singleton
//Classe qui s'occupe de la persistance des données


class GestionUser
{
    public:
        virtual ~GestionUser();

        GestionUser& operator=(const GestionUser& other);
        string str()const ;
        void addUser(const User*);
        bool contains(const User*);
        void removeUser(User& u);

        vector<User*> getUsers();

        //Méthode qui permet la lecture du fichier contenant les users "User.txt" -> Utilisation d'un "ifstream"
        void readFromFile(string fileName);
        //Méthode qui permet l'écriture des utilisateurs dans le fichier "USer.txt" -> Utilisation d'un "ofStream"
        void writeFromFile(string fileName);

        //Méthode qui permet la récupération de l'instance hors de la classe
        static GestionUser* getInstance();


    protected:

    private:
        //Constructeur privé en raison du singleton
        GestionUser(){}
        GestionUser(const GestionUser& other);

        vector<User*> users;
        //Instance
        static GestionUser* gestion ;



};

#endif // GESTIONUSER_H
