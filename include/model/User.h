#ifndef USER_H
#define USER_H

#include <string>
#include <ostream>
#include <vector>

//Serialisation
#include <iostream>
#include <fstream>

using namespace std;

enum EnumStatus {
    user,
    admin
};

class User
{
    private:
        string login;
        EnumStatus status;
        vector<int> scores;

    public:
        User(string login,EnumStatus status);
        User(string login,EnumStatus status, vector<int>scores);
        User();
        virtual ~User();
        User(const User& other);
        User& operator=(const User& other);
        string getLogin();
        EnumStatus getStatus();
        void addScores(int scrore);
        vector<int> getScores();

        string str();
        bool operator==(const User& other);

        User* clone() const;

    protected:


};

#endif // USER_H
