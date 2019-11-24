#include "User.h";
#include <sstream>
#include <iostream>
#include <string>

using std::ostream;
using namespace std;

/**
*   Default constructor
*/
User::User(){
}
/**
*   Constructor
*   @param login : a string who represent the login of user
*/
User::User(string login)
{
    this->login = login;
}
/**
*   Constructor overloading
*   @param login : a string who represent the login of user
*   @param scores : a vector of int who represent all scores of user
*/
User::User(string login, vector<int>scores)
{
    this->login = login;
    this->scores = scores;
}
/**
*   Destructor
*   Not implemented
*/
User::~User()
{
    //dtor
}
/**
*   Default copy constructor
*   Parameter passing by reference
*   recuperation the login from "other" object
*   recuperation the vector scores from "other" object
*   @param other : reference constant of a GestionUser object
*/
User::User(const User& other)
{
    this->login = other.login;
    this->scores = other.scores;
}
/**
*   Default operator= overloading
*   Parameter passing by reference
*   if current object is different of parameter
*   affection to current object of the login from "other" object
*   affection to current object of the vector scores from "other" object
*   @param rhs : reference constant of a GestionUser object
*/
User& User::operator=(const User& rhs)
{
    if (this != &rhs) {
        this->login = rhs.login;
        this->scores = rhs.scores;
    }
    return *this;
}
/**
*   Default operator== overloading
*   Parameter passing by reference
*   if current object is different of parameter
*   recuperation login of the both user
*   Compare the both, if same return true, if not return false
*   @param other: reference constant of a GestionUser object
*/
bool User::operator==(const User& other){
    string str1 = this->login;
    string str2 = other.login;

    return str1.compare(str2)==0;
}
/**
*   Function who return the login of a user
*/
string User::getLogin(){
    return login;
}
/**
*   Function to print the user
*   Utilisation of a stringstream variable, recuperation(injection) of login and each scores
*   Return a string
*/
string User::str(){
    stringstream sstr;
    sstr<<login<<endl<<scores.size()<<endl;
    for(int score : scores){
        sstr<<score<<endl;
    }
    sstr<<"**";
    return sstr.str();
}
/**
*   Function to add a score(int) to vector scores of user
*   @param score : an integer who represent a score of game
*/
void User::addScores(int score){
    scores.push_back(score);
}
/**
*   Function who return the login of a user
*/
vector<int> User::getScores(){
    return scores;
}
/**
*   Function to return a new pointer of user (Polymorphism)
*/
User* User::clone() const{
    return new User(*this);
}
