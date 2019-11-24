#ifndef GESTIONUSER_H
#define GESTIONUSER_H

#include "User.h"
#include <vector>
#include <string>
#include <sstream>

#include <iostream>
#include <fstream>

using namespace std;

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

        void readFromFile(string fileName);
        void writeFromFile(string fileName);

        static GestionUser* getInstance();


    protected:

    private:
        GestionUser(){}
        GestionUser(const GestionUser& other);

        vector<User*> users;
        //Instance
        static GestionUser* gestion ;



};

#endif // GESTIONUSER_H
