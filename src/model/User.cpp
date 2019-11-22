#include "User.h";
#include <sstream>
#include <iostream>
#include <string>

using std::ostream;
using namespace std;

User::User(){
}

User::User(string login,EnumStatus status)
{
    this->login = login;
    this->status = status;
}
User::User(string login,EnumStatus status, vector<int>scores)
{
    this->login = login;
    this->status = status;
    this->scores = scores;
}

User::~User()
{
    //dtor
}

User::User(const User& other)
{
    this->login = other.login;
    this->status = other.status;
    this->scores = other.scores;
}

User& User::operator=(const User& rhs)
{
    if (this != &rhs) {
        this->login = rhs.login;
        this->status = rhs.status;
        this->scores = rhs.scores;
    }
    return *this;
}

bool User::operator==(const User& other){
    string str1 = this->login;
    string str2 = other.login;

    return str1.compare(str2)==0;
}

string User::getLogin(){
    return login;
}
EnumStatus User::getStatus(){
    return status;
}
string User::str(){
    stringstream sstr;
    sstr<<login<<endl<<status<<endl<<scores.size()<<endl;
    for(int score : scores){
        sstr<<score<<endl;
    }
    sstr<<"**";
    return sstr.str();
}
void User::addScores(int score){
    scores.push_back(score);
}
vector<int> User::getScores(){
    return scores;
}

User* User::clone() const{
    return new User(*this);
}
