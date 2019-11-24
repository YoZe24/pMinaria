#ifndef USER_H
#define USER_H

#include <string>
#include <ostream>
#include <vector>

//Serialisation
#include <iostream>
#include <fstream>

using namespace std;

class User
{
    private:
        string login;
        vector<int> scores;

    public:
        User(string login);
        User(string login, vector<int>scores);
        User();
        virtual ~User();
        User(const User& other);
        User& operator=(const User& other);
        string getLogin();
        void addScores(int scrore);
        vector<int> getScores();

        string str();
        bool operator==(const User& other);

        User* clone() const;

    protected:


};

#endif // USER_H
