#ifndef GESTIONUSER_H
#define GESTIONUSER_H

#include "User.h"
#include <vector>
#include <string>
#include <sstream>

#include <iostream>
#include <fstream>

using namespace std;

//Classe qui poss�de un singleton
//Classe qui s'occupe de la persistance des donn�es


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

        //M�thode qui permet la lecture du fichier contenant les users "User.txt" -> Utilisation d'un "ifstream"
        void readFromFile(string fileName);
        //M�thode qui permet l'�criture des utilisateurs dans le fichier "USer.txt" -> Utilisation d'un "ofStream"
        void writeFromFile(string fileName);

        //M�thode qui permet la r�cup�ration de l'instance hors de la classe
        static GestionUser* getInstance();


    protected:

    private:
        //Constructeur priv� en raison du singleton
        GestionUser(){}
        GestionUser(const GestionUser& other);

        vector<User*> users;
        //Instance
        static GestionUser* gestion ;



};

#endif // GESTIONUSER_H
