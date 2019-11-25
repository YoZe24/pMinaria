#include "model/GestionUser.h"
#include <string>


/**
*   Initialisation singleton's instance to 0
*/
GestionUser* GestionUser::gestion = 0;

/**
*   Destructor
*   Vector of pointers -> agregation intern pointer
*   Need to liberate the vector
*/
GestionUser::~GestionUser()
{
    for(User* user : users){
        delete user;
    }

}
/**
*   function to recup the instance of singleton
*   Constructor is private, it's the only to have acces instance
*   if instance = 0 -> creation of new instance
*   if instance != 0 -> return the current instance
*/
GestionUser* GestionUser::getInstance(){
    if(gestion == 0){
        gestion = new GestionUser();
    }
    return gestion;
}

User* GestionUser::getUserCurrent(){
    return userCurrent;
}
void GestionUser::setUserCurrent(User* u){
    this->userCurrent = u;
}


/**
*   Default copy constructor
*   Parameter passing by reference
*   recuperation the vector from "other" object
*   @param other : reference constant of a GestionUser object
*/
GestionUser::GestionUser(const GestionUser& other)
{
    this->users = other.users;
}

/**
*   Default operator= overloading
*   Parameter passing by reference
*   if the obejct current and rhs object is not equals -> affectation of vector users
*   if the both objects are equals -> return a pointer of current object
*   @param rhs : reference constant of a GestionUser object
*/
GestionUser& GestionUser::operator=(const GestionUser& rhs)
{
    if(&rhs != this){
        users = rhs.users;
    }
    return *this;
}

/**
*   Function to add a user in instance
*   Parameter passing by pointer
*   Check if the user parameter is already present in instance
*   If not, add to instance with clone() (Polymorphism)
*   @param u : Pointer constant of a User object
*/
void GestionUser::addUser(const User* u){
    if(contains(u)) return;
    users.push_back(u->clone());
}
void GestionUser::addScoreCurrentUser(int score){
    for (int i = 0; i<users.size();i++){
        if(users[i]==this->getUserCurrent()){
            cout<<2;
            users[i]->addScores(score);
        }
    }
}

/**
*   Function to check if a user is already present in instance
*   Parameter passing by pointer
*   Check all users contains in instance, if is already present return true, if not return false
*   @param u : Pointer constant of a User object
*/
bool GestionUser::contains(const User* u){
    for(User* user : users){
        if(*user == *u){
            return true;
        }
    }
    return false;
}

/**
*   Function to remove a user of instance
*   Parameter passing by reference
*   Check all users of instance, if user is present :
*   recup the adress of user, remove user of instance and liberate memory of the adress
*   @param : reference of a User object
*/
void GestionUser::removeUser (User& u){
    for(int i=0; i<=users.size(); i++){
        if(*users[i] == u){
            cout<<2;
            User* tmp = *(users.begin()+i);
            users.erase(users.begin()+i);
            delete tmp;
            //free(tmp);
            return;
        }
    }
}
/**
*   Function to recup the vector users
*   return a vector of user's pointer
*/
vector<User*> GestionUser::getUsers(){
    return users;
}
/**
*   Function to print the instance
*   Utilisation of a stringstream variable, injection of function str() for each user of instance
*   Return a string
*/
string GestionUser::str() const {
    stringstream st;
    for(User* user: users){
        st<<user->str()<<endl;
    }
    return st.str();
}

/**
*   Function to read a file -> Persitence/Serialisation
*   "User.txt" contains all users of instance and all scores of each user
*   Using of an "ifstream"
*   First, test opening of file
*   Second, reading(extraction) of file while the file is not finish
*   Third, reading(extraction) of each line -> recuperation of variable
*   Fourth, creation of a user with recup variable
*   Finally, adding the user created to instance
*   @param fileName : a string who represent the file name
*/
void GestionUser::readFromFile(string fileName){
    ifstream myfile(fileName);
    string name;
    string sep;
    if(!myfile)
    {
        cout << "While opening a file an error is encountered" << endl;
    }
    else
    {
        cout << "File is successfully opened" << endl;
        while(!myfile.eof())
        {
            std::getline(myfile,name,'\n');
            while(name.compare("")!=0){
                User* user;
                int nbScores = 0;
                vector<int> scores;
                int score = 0;
                myfile>>nbScores;
                if(nbScores > 0){
                    for(int i=0;i<nbScores;i++){
                        myfile>>score;
                        scores.push_back(score);
                        score=0;
                    }
                }
                myfile>>sep;
                user = new User(name,scores);
                std::getline(myfile,name,'\n');
                //Ajout à l'instance
                gestion->addUser(user);
            }
        }
        myfile.close();
    }
}
/**
*   Function to write a file -> Persistence/Serialisation
*   Using an "ofstream"
*   Clean the file before to write the instance
*   Condition if the is open -> write the instance with str() function
*   Closing file
*   @param fileName : a string who represent the fileName
*/
void GestionUser::writeFromFile(string fileName){
    ofstream myfile (fileName);
    myfile.clear();
    if (myfile.is_open())
    {
        myfile<<gestion->str();
        myfile.close();
    }
}
