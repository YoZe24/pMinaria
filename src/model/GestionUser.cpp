#include "GestionUser.h"
#include <string.h>

/*GestionUser::GestionUser()
{
    //ctor
}*/

//Initialisation de l'instace � z�ro
GestionUser* GestionUser::gestion = 0;

GestionUser::~GestionUser()
{
    for(User* user : users){
        delete user;
    }

}
//A chaque appel, nous v�rifions si une instance existe d�ja, dans le cas contraire nous la cr�ons
GestionUser* GestionUser::getInstance(){
    if(gestion == 0){
        gestion = new GestionUser();
    }
    return gestion;
}

GestionUser::GestionUser(const GestionUser& other)
{
    this->users = other.users;
}

GestionUser& GestionUser::operator=(const GestionUser& rhs)
{
    if(&rhs != this){
        users = rhs.users;
    }
    return *this;
}

//Vecteur de pointeurs -> Agr�gation interne + Polymorphisme
void GestionUser::addUser(const User* u){
    if(contains(u)) return;
    users.push_back(u->clone());
}

bool GestionUser::contains(const User* u){
    for(User* user : users){
        if(*user == *u){
            return true;
        }
    }
    return false;
}

//N�cessit� de lib�rer l'emplacement m�moire correspondant
void GestionUser::removeUser (User& u){
    for(int i=0; i<users.size(); i++){
        if(*users[i] == u){
            User* tmp = *(users.begin()+i);
            users.erase(users.begin()+i);
            users.clear();
            delete tmp;
            free(tmp);
            return;
        }
    }
}

vector<User*> GestionUser::getUsers(){
    return users;
}
string GestionUser::str() const {
    stringstream st;
    for(User* user: users){
        st<<user->str()<<endl;
    }
    return st.str();
}

void GestionUser::readFromFile(string fileName){
    ifstream myfile(fileName);
    string name;
    string sep;
    //Teste l'ouverture du fichier
    if(!myfile)
    {
        cout << "While opening a file an error is encountered" << endl;
    }
    else
    {
        cout << "File is successfully opened" << endl;
        //Tant que le fichier n'est pas finis
        while(!myfile.eof())
        {
            std::getline(myfile,name,'\n');
            //Cract�re de fin de fichier (Retour � la ligne automatique en cas de sauvegarde du fichier)
            while(name.compare("")!=0){
                User* user;
                int nbScores = 0;
                vector<int> scores;
                int score = 0;
                int state = 0;
                myfile>>state;
                myfile>>nbScores;
                if(nbScores > 0){
                    for(int i=0;i<nbScores;i++){
                        myfile>>score;
                        scores.push_back(score);
                        score=0;
                    }
                }
                myfile>>sep;
                if(state == 0 ){
                    user = new User(name,EnumStatus::user,scores);

                } else if( state == 1){
                    user = new User(name,EnumStatus::admin,scores);
                }
                std::getline(myfile,name,'\n');
                //Ajout � l'instance
                gestion->addUser(user);
            }
        }
        myfile.close();
    }
}

void GestionUser::writeFromFile(string fileName){
    ofstream myfile (fileName);
    //Clean le gichier avant la r��criture de l'instance
    myfile.clear();
    if (myfile.is_open())
    {
        myfile<<gestion->str();
        myfile.close();
    }
}
